# Debugging ngspice WASM Simulator

When building or expanding the Circuit Expert Simulator, you'll rely heavily on `@tscircuit/ngspice-spice-engine`. Because it runs inside a WASM container triggered by a complex React frontend, debugging the engine output or generation logic strictly through the UI can be slow and tedious.

Here are key lessons learned when dealing with SPICE netlists and testing browser-based circuit simulation offline.

## Testing Offline using Node and `npx tsx`

Instead of hot-reloading the frontend every time you want to test the simulator's output generation (like verifying the exact PWL arrays), craft standalone `.mjs` files to test your utility functions.

**1. Create an isolated test script (`test_mcu.mjs`)**
Because the project uses TypeScript and ES Modules, testing a local TS file from the command line can be tricky. Use `npx tsx` (TypeScript Execute) to seamlessly execute TypeScript files that use modern ES imports without needing a pre-compilation step.

```javascript
// test_mcu.mjs
import { executeMcuCode } from './utils/mcu.ts';

const code = `
pinMode('D0', 'OUTPUT');
while(true) {
  digitalWrite('D0', 1);
  sleep(500);
  digitalWrite('D0', 0);
  sleep(500);
}
`;

const res = executeMcuCode(code, 1.0, {});
console.log(JSON.stringify(res, null, 2));
```

**2. Run it via command line**
```bash
npx tsx test_mcu.mjs
```
This prints the exact output the simulator would receive, allowing you to instantly catch bugs like duplicated timestamps or incorrect unit generation.

## 1. SPICE Time Units (Milliseconds vs Seconds)
**Gotcha:** SPICE transient analysis (`.tran`) and Piecewise Linear (PWL) voltage sources *always* expect time in seconds.
**Symptom:** If you pass milliseconds (e.g., `500`) into a PWL definition, SPICE interprets it as 500 seconds. If your simulation only runs for `1.0` second, the PWL effectively acts as a flatline interpolating the very beginning of the curve, causing signals to stay "mostly off" or flat.
**Fix:** Always ensure `t` is converted to seconds when generating SPICE netlists:
```typescript
pwlLines += `${(time_ms / 1000).toExponential(6)} ${voltage.toExponential(6)} `;
```

> [!NOTE]
> The engine output `result.simulationResultCircuitJson` transient graphs will label time as `timestamps_ms`, but it is actually the simulation time in **milliseconds**, mapped from the SPICE output!

## 2. Singular Matrix Errors
**Gotcha:** A "Singular Matrix" error typically happens when SPICE encounters a theoretical impossibility or mathematical undefined state.
**Symptom:** Simulation fails with `Warning: singular matrix: check node X`.
**Common Causes:**
1.  **Parallel Ideal Voltage Sources:** Connecting two 5V DC sources directly together. Current is theoretically infinite/undefined.
2.  **Floating Nodes:** A node with no path to ground.

**Fix:** 
- For parallel voltage sources (like an MCU driving an output that might get shorted to VCC or GND), *always* inject a small series resistor (e.g., `1 ohm` for power lines, `20 ohms` for GPIO). 
- For floating nodes (like unconfigured MCU pins), add a very high value pull-down resistor (`100MEG`) to ground.

## 3. Strict Monotonically Increasing PWL Time
**Gotcha:** Piecewise Linear (PWL) inputs (`PWL(t1 v1 t2 v2 ...)`) must strictly increase in time.
**Symptom:** SPICE throws a `Warning : voltage source v1 has non-increasing PWL time points` and ignores the source, or fails silently.
**Fix:** If multiple events happen at the exact same millisecond, overwrite the last value rather than pushing a new time point with the same timestamp.

```javascript
// Example sandbox logic
if (out.length > 0 && out[out.length - 1].t === mcuTimeMs) {
  out[out.length - 1].v = v; // Overwrite
} else {
  // Push new point
}
```
