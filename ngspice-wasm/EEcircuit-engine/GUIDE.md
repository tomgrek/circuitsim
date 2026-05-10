# Ngspice WebAssembly Compilation Guide

This document captures the key findings, architectural quirks, and compilation details uncovered during the process of building a custom Ngspice WebAssembly (WASM) engine for the `EEcircuit-engine` frontend.

## The Emscripten Stdin Polyfill Issue (Node.js vs Browser)

### The Problem
During local testing of the compiled `eecircuit-engine` in a Node.js headless environment (`test_dynamic.js`), the simulation consistently hung and pegged the CPU at 100%. However, the exact same WASM binary worked perfectly when loaded in the frontend React web application.

### The Mechanism
The original `EEcircuit-engine` developers used a clever but environment-specific hack to feed SPICE commands into the C-based Ngspice engine asynchronously:
1. **Ngspice Input**: Ngspice runs a command loop (`cp_evloop`) that reads input line-by-line using `fgetc(stdin)` or similar C standard library input functions.
2. **Emscripten's Browser Fallback**: When Emscripten compiles C code for a web browser (`ENVIRONMENT="web,worker"`), it realizes there is no physical terminal attached to `stdin`. To polyfill this, Emscripten hooks `stdin` reads to the JavaScript `window.prompt()` function.
3. **The Hijack**: The `EEcircuit-engine` overrides `window.prompt()` globally in `pre.js`. When the C code attempts to read `stdin`, Emscripten calls `window.prompt()`, which then calls into the engine's internal `getInput()` queue, cleanly passing "source /test.cir", "run", "write", etc., into the C event loop.

### Why it Broke in Node.js
When running the same WASM module in Node.js, Emscripten automatically binds the C `stdin` to the real `process.stdin`. Because our background test script wasn't piping anything into `stdin`, `fgetc` blocked synchronously, causing a complete deadlock. **The engine is architecturally bound to the browser's `window.prompt` polyfill and cannot be run headless in Node.js without a custom stdin injection pipeline.**

## The Asyncify Concurrency Clash

While debugging the hanging issue, an attempt was made to "fix" the asynchronous C-to-JS bridge (`eesim_sleep_hack` in `control.c`). 

### The Original Architecture
The engine relies on Emscripten's `Asyncify` feature to pause the C simulation loop, yield control to the JavaScript browser thread, and resume the simulation later.
- In `control.c`, an `EM_ASYNC_JS` macro was used to inject an asynchronous sleep function.
- Internally, this macro called `Module["handleThings"]()`.
- `Module["handleThings"]()` then invoked `module.Asyncify.handleAsync()`.

### The Clash
`EM_ASYNC_JS` and `Asyncify.handleAsync` both interact with the internal `Asyncify` stack-saving state machine. 
- I mistakenly added a `return` statement to bridge the JavaScript Promise back to the C `EM_ASYNC_JS` macro.
- This caused `EM_ASYNC_JS` to attempt to restore the C stack upon Promise resolution, while `Asyncify.handleAsync` *also* attempted to restore the C stack upon resolution.
- This double-restore corrupted the stack state, leading to silent crashes or infinite loops.

### The Solution
The original code purposefully did **not** return the Promise back to `EM_ASYNC_JS`. It used the `EM_ASYNC_JS` macro purely as a syntactical trick to force Emscripten's compiler to treat the C function as a suspendable `Asyncify` boundary. The actual stack suspension and resumption was managed entirely by the inner `Asyncify.handleAsync` call. **Reverting the bridging logic back to the original implementation resolved the corruption.**

## Building the Engine

To reliably build the custom ngspice engine, use the following sequence inside the `ngspice-wasm` directory. Make sure you have activated the conda build environment and sourced the Emscripten SDK first.

```bash
cd ngspice-ngspice/release
emmake make -j4

cd ../../EEcircuit-engine
# Copy the compiled WASM artifacts over
cp ../ngspice-ngspice/release/src/spice.mjs src/spice.js
cp ../ngspice-ngspice/release/src/spice.wasm src/spice.wasm

# Install dependencies and build the TypeScript wrapper
npm install
npm run build
```

> [!IMPORTANT]
> The `EEcircuit-engine` TypeScript build (`npm run build`) strictly checks types. If you modify `simulationLink.ts` to access undocumented Emscripten FS bindings (like `module.FS.mkdir`), you must use TypeScript overrides (e.g., `(module.FS as any)`) to prevent the build from silently failing and leaving you with an outdated output bundle.

## The Hanging Promise and Event Handling Cycle

### The Problem
During the fix for the blink simulation, a critical hang was identified where the C code would call `handleThings` but the JavaScript side would never resume execution. This manifested as an infinite loop of "C code called handleThings!" messages in the console without any progress in the simulation.

### The Mechanism
1. **Broken Bridge**: The `EM_ASYNC_JS` bridge in `spice.js` was using a promise that never resolved. Specifically, the bridge used `new Promise(resolve => { Module.handleThings(); })` but forgot to actually call `resolve()` inside `handleThings`.
2. **Race Conditions**: The engine was attempting to read simulation results (`out.raw`) as soon as `handleThings` was triggered with `cmd === 0`. However, `cmd === 0` is also sent during the initialization phase before any simulation commands have actually started.

### The Solution
1. **Proper Promise Lifecycle**: The bridge was updated to `await` the result of `handleThings`. In `simulationLink.ts`, `handleThings` was made an `async` function. The build script (`Docker/run.sh`) was updated to inject a bridge that correctly `await`s this handler, ensuring the C stack is only resumed after JS has finished its work.
2. **State Gating**: A `hasStartedCommands` flag was introduced in `simulationLink.ts`. This flag is only set to `true` after the initial setup commands (like `source /test.cir`) have been sent. This prevents the engine from prematurely entering the result-reading logic during the startup yields.
3. **Cycle Exhaustion Check**: Added a check for `this.cmd === 0` combined with `this.initialized` and `this.hasStartedCommands` to accurately detect when a simulation run has truly finished and is ready for result parsing.

## Lessons for Future Debugging

1. **Check the Bridge**: If the simulation hangs with high CPU but no output, verify that the `EM_ASYNC_JS` bridge is correctly resolving its promises.
2. **Monitor the Command Loop**: Use detailed logging for `this.cmd`, `this.initialized`, and `this.hasStartedCommands` to track where the state machine is stuck.
3. **Vite Cache**: When working with `file:` linked dependencies, Vite's cache (`node_modules/.vite`) is extremely aggressive. If code changes in the engine aren't showing up in the browser, delete the cache directory.

## Custom Modifications vs. Open Source Baseline

While this project is based on the open-source Ngspice and its initial WASM ports, we have implemented several critical enhancements to make it reliable for interactive web applications.

### 1. Synchronized Async Bridge
*   **Original**: Uses a basic `Asyncify` yield that can hang if the browser's event loop doesn't resume the WASM stack correctly.
*   **Our Modification**: In `Docker/run.sh`, we inject an `await` into the `EM_ASYNC_JS` macro. This forces the C engine to wait for the JavaScript `handleThings` handler to resolve before attempting to resume the C stack, eliminating the infinite "C code called handleThings!" hang.

### 2. State-Gated Event Handling
*   **Original**: Typically treats every yield from C as a generic simulation step.
*   **Our Modification**: Introduced the `hasStartedCommands` flag in `simulationLink.ts`. This allows the engine to distinguish between the **initialization phase** (sending netlists, sourcing files) and the **active simulation phase**. This prevents the engine from prematurely attempting to read result files (`out.raw`) before they are written.

### 3. Real-Time Console Piping
*   **Original**: Ngspice stdout is often discarded or stored in a difficult-to-access internal buffer.
*   **Our Modification**: We redirected the WASM module's `print` and `printErr` functions directly to `console.log` and `console.error`. This provides developers with full visibility into the numerical engine's status directly in the browser dev tools.

### 4. Interactive Simulation State Management
*   **Original**: Logic usually resets the "Simulating" state as soon as the WASM module returns.
*   **Our Modification**: In `App.tsx`, we decoupled the `isSimulating` state from the mathematical completion of the simulation. This allows the "Stop" button to remain active while components like the **Scope** and **LED** are looping through the animated results, providing a "real-time" user experience.

### 5. Automated Regression Testing
*   **Our Modification**: Added `test/test-async-hang-prevention.ts` which uses a 10-second timeout guard to automatically detect regressions in the asynchronous bridge logic, ensuring that future builds don't re-introduce simulation hangs.
