# Circuit Simulator

A high-fidelity, interactive circuit simulator built with React and powered by an optimized Ngspice WebAssembly engine.

## 🚀 Tech Stack

- **Frontend**: [React](https://reactjs.org/) + [React Flow](https://reactflow.dev/) for the visual circuit editor.
- **Styling**: [Tailwind CSS](https://tailwindcss.com/) for a modern, responsive UI.
- **Simulation Engine**: [Ngspice](https://ngspice.sourceforge.io/) (C) compiled to **WebAssembly** via [Emscripten](https://emscripten.org/).
- **Engine Bridge**: `eecircuit-engine` - a TypeScript wrapper that synchronizes JavaScript and the WASM simulation stack.

## 📂 Project Structure

- `frontend/`: The React application containing the UI, component library, and circuit logic.
- `ngspice-wasm/EEcircuit-engine/`: The TypeScript wrapper for the Ngspice WASM module.
- `ngspice-wasm/ngspice-ngspice/`: The original C source code and build infrastructure for Ngspice.

## 🛠️ Getting Started

### Prerequisites
- Node.js (v18+)
- npm

### Installation

1. **Install Engine Dependencies**:
   ```bash
   cd ngspice-wasm/EEcircuit-engine
   npm install
   npm run build
   ```

2. **Install Frontend Dependencies**:
   ```bash
   cd ../../frontend
   npm install
   ```

### Running the Application

Start the development server from the `frontend` directory:
```bash
cd frontend
npm run dev
```
The application will be available at `http://localhost:5173`.

## 🧪 Testing

The simulation engine includes a regression test suite to ensure the WASM bridge remains stable.

```bash
cd ngspice-wasm/EEcircuit-engine
# Run all tests
npm test
# Run specific async-hang prevention test
npm run test:hang
```

## 📘 Documentation

- **[GUIDE.md](ngspice-wasm/EEcircuit-engine/GUIDE.md)**: Technical details on the WASM compilation, Asyncify fixes, and simulation lifecycle.
- **[SKILL.md](ngspice-wasm/EEcircuit-engine/SKILL.md)**: Debugging patterns and maintenance tips for working with the simulation engine.

## 🔧 Custom Modifications

We have heavily modified the original Ngspice-WASM baseline to support:
- **Synchronized Async Bridge**: Eliminated simulation hangs by correctly `await`ing JavaScript handlers in the WASM stack.
- **State-Gated Event Handling**: Optimized initialization vs. simulation phases.
- **Real-time Animation**: Supported looping simulation results in the UI for components like LEDs and Oscilloscopes.
