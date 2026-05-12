import { type Node, type Edge } from '@xyflow/react';

export interface CircuitPreset {
  name: string;
  nodes: Node[];
  edges: Edge[];
}

export const basicBlink: CircuitPreset = {
  name: 'Basic Blink',
  nodes: [
    { id: 'sg1', type: 'signalgen', position: { x: 100, y: 150 }, data: { label: 'SIGNALGEN', waveform: 'square', frequency: 1, amplitude: 5 } },
    { id: 'r1', type: 'resistor', position: { x: 350, y: 150 }, data: { label: '330Ω', resistance: 330 } },
    { id: 'led1', type: 'led', position: { x: 600, y: 150 }, data: { label: 'LED', color: 'red', v_drop: 2.0, max_current: 20 } },
    { id: 'g1', type: 'ground', position: { x: 600, y: 300 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 100, y: 300 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-sg1-r1', source: 'sg1', target: 'r1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-r1-led1', source: 'r1', target: 'led1', sourceHandle: 'out', targetHandle: 'anode', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-led1-g1', source: 'led1', target: 'g1', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-sg1-g2', source: 'sg1', target: 'g2', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const timer555Blink: CircuitPreset = {
  name: '555 Blinker',
  nodes: [
    { id: 'v1', type: 'voltage', position: { x: 100, y: 50 }, data: { label: '5V', voltage: 5 } },
    { id: 't555', type: 'timer555', position: { x: 400, y: 200 }, data: { label: '555 Timer' } },
    { id: 'r1', type: 'resistor', position: { x: 250, y: 50 }, data: { label: '10kΩ', resistance: 10000 } },
    { id: 'r2', type: 'resistor', position: { x: 250, y: 150 }, data: { label: '47kΩ', resistance: 47000 } },
    { id: 'c1', type: 'capacitor', position: { x: 250, y: 250 }, data: { label: '10µF', capacitance: 10e-6 } },
    { id: 'r3', type: 'resistor', position: { x: 600, y: 200 }, data: { label: '330Ω', resistance: 330 } },
    { id: 'led1', type: 'led', position: { x: 800, y: 200 }, data: { label: 'LED', color: 'blue', v_drop: 2.0, max_current: 20 } },
    { id: 'g1', type: 'ground', position: { x: 100, y: 400 }, data: { label: 'GND' } },
  ],
  edges: [
    // Power
    { id: 'e-v1-t8', source: 'v1', target: 't555', sourceHandle: 'pos', targetHandle: '8', type: 'smoothstep' },
    { id: 'e-v1-t4', source: 'v1', target: 't555', sourceHandle: 'pos', targetHandle: '4', type: 'smoothstep' }, // RST to VCC
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g1', source: 'v1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-t1-g1', source: 't555', target: 'g1', sourceHandle: '1', targetHandle: 'in', type: 'smoothstep' },
    
    // Astable network
    { id: 'e-r1-r2', source: 'r1', target: 'r2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r1-t7', source: 'r1', target: 't555', sourceHandle: 'out', targetHandle: '7', type: 'smoothstep' }, // DIS
    { id: 'e-r2-c1', source: 'r2', target: 'c1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-t6', source: 'r2', target: 't555', sourceHandle: 'out', targetHandle: '6', type: 'smoothstep' }, // THR
    { id: 'e-r2-t2', source: 'r2', target: 't555', sourceHandle: 'out', targetHandle: '2', type: 'smoothstep' }, // TRIG
    { id: 'e-c1-g1', source: 'c1', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    
    // Output
    { id: 'e-t3-r3', source: 't555', target: 'r3', sourceHandle: '3', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r3-led1', source: 'r3', target: 'led1', sourceHandle: 'out', targetHandle: 'anode', type: 'smoothstep' },
    { id: 'e-led1-g1', source: 'led1', target: 'g1', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const sineAudio: CircuitPreset = {
  name: 'Sine Wave Audio',
  nodes: [
    { id: 'sg1', type: 'signalgen', position: { x: 100, y: 150 }, data: { label: 'Tone', waveform: 'sine', frequency: 440, amplitude: 2 } },
    { id: 'spk1', type: 'speaker', position: { x: 400, y: 150 }, data: { label: 'Speaker' } },
    { id: 'g1', type: 'ground', position: { x: 400, y: 300 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 100, y: 300 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-sg1-spk1', source: 'sg1', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-sg1-g2', source: 'sg1', target: 'g2', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk1-g1', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const bjtAmp: CircuitPreset = {
  name: 'BJT Audio Amp',
  nodes: [
    { id: 'v1', type: 'voltage', position: { x: 100, y: 50 }, data: { label: '12V VCC', voltage: 12 } },
    { id: 'mic1', type: 'microphone', position: { x: 100, y: 300 }, data: { label: 'Mic', pwlData: [{t:0,v:0}, {t:0.001,v:0.02}, {t:0.002,v:-0.02}, {t:0.003,v:0}] } },
    
    // Input coupling
    { id: 'cin', type: 'capacitor', position: { x: 250, y: 300 }, data: { label: '10µF', capacitance: 10e-6 } },
    
    // Bias
    { id: 'r1', type: 'resistor', position: { x: 400, y: 150 }, data: { label: '47kΩ', resistance: 47000 } },
    { id: 'r2', type: 'resistor', position: { x: 400, y: 400 }, data: { label: '10kΩ', resistance: 10000 } },
    
    // Transistor
    { id: 'q1', type: 'npn', position: { x: 600, y: 300 }, data: { label: '2N3904', bf: 300 } },
    
    // Collector & Emitter resistors
    { id: 'rc', type: 'resistor', position: { x: 600, y: 150 }, data: { label: '2.2kΩ', resistance: 2200 } },
    { id: 're', type: 'resistor', position: { x: 600, y: 450 }, data: { label: '1kΩ', resistance: 1000 } },
    
    // Output coupling & Speaker
    { id: 'cout', type: 'capacitor', position: { x: 800, y: 300 }, data: { label: '470µF', capacitance: 470e-6 } },
    { id: 'spk1', type: 'speaker', position: { x: 1000, y: 300 }, data: { label: 'Speaker', acCouple: true, normalize: true } },
    
    // Grounds
    { id: 'g1', type: 'ground', position: { x: 100, y: 600 }, data: { label: 'GND' } },
  ],
  edges: [
    // Power rails
    { id: 'e-v1-rc', source: 'v1', target: 'rc', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g1', source: 'v1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },
    
    // Mic
    { id: 'e-mic-cin', source: 'mic1', target: 'cin', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-mic-g1', source: 'mic1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    
    // Bias divider & Base
    { id: 'e-r1-b', source: 'r1', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-r2-b', source: 'q1', target: 'r2', sourceHandle: 'b', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-g1', source: 'r2', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cin-b', source: 'cin', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    
    // Collector
    { id: 'e-rc-c', source: 'rc', target: 'q1', sourceHandle: 'out', targetHandle: 'c', type: 'smoothstep' },
    { id: 'e-c-cout', source: 'q1', target: 'cout', sourceHandle: 'c', targetHandle: 'in', type: 'smoothstep' },
    
    // Emitter
    { id: 'e-q1-re', source: 'q1', target: 're', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-re-g1', source: 're', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    
    // Speaker
    { id: 'e-cout-spk', source: 'cout', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-g1', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const micSpeaker: CircuitPreset = {
  name: 'Mic → Speaker',
  nodes: [
    { id: 'mic1', type: 'microphone', position: { x: 100, y: 200 }, data: { label: 'Mic', amplification: 100 } },
    { id: 'spk1', type: 'speaker', position: { x: 400, y: 200 }, data: { label: 'Speaker' } },
    { id: 'g1', type: 'ground', position: { x: 250, y: 400 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-mic-spk', source: 'mic1', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-mic-g1', source: 'mic1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-g1', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const classBamp: CircuitPreset = {
  name: 'Class B Push-Pull',
  nodes: [
    { id: 'v1', type: 'voltage', position: { x: 50, y: 50 }, data: { label: '12V', voltage: 12 } },
    { id: 'mic1', type: 'microphone', position: { x: 50, y: 300 }, data: { label: 'Mic', amplification: 50 } },
    { id: 'cin', type: 'capacitor', position: { x: 250, y: 300 }, data: { label: '10uF', capacitance: 10e-6 } },
    { id: 'r1', type: 'resistor', position: { x: 400, y: 150 }, data: { label: '10k', resistance: 10000 } },
    { id: 'r2', type: 'resistor', position: { x: 400, y: 450 }, data: { label: '10k', resistance: 10000 } },
    { id: 'q1', type: 'npn', position: { x: 600, y: 200 }, data: { label: 'NPN', bf: 200 } },
    { id: 'q2', type: 'pnp', position: { x: 600, y: 400 }, data: { label: 'PNP', bf: 200 } },
    { id: 'cout', type: 'capacitor', position: { x: 800, y: 320 }, data: { label: '470uF', capacitance: 470e-6 } },
    { id: 'spk1', type: 'speaker', position: { x: 1000, y: 320 }, data: { label: 'Speaker', acCouple: true, normalize: true } },
    { id: 'g1', type: 'ground', position: { x: 50, y: 550 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-v1-q1c', source: 'v1', target: 'q1', sourceHandle: 'pos', targetHandle: 'c', type: 'smoothstep' },
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g1', source: 'v1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r1-q1b', source: 'r1', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-r1-q2b', source: 'r1', target: 'q2', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-r1-r2', source: 'r1', target: 'r2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-gnd', source: 'r2', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-mic-cin', source: 'mic1', target: 'cin', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cin-base', source: 'cin', target: 'r1', sourceHandle: 'out', targetHandle: 'out', type: 'smoothstep' },
    { id: 'e-mic-gnd', source: 'mic1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q1e-cout', source: 'q1', target: 'cout', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q2e-cout', source: 'q2', target: 'cout', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q2c-gnd', source: 'q2', target: 'g1', sourceHandle: 'c', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cout-spk', source: 'cout', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-gnd', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

// Class AB: series bias resistor (Rbias=1.1k) between NPN and PNP base taps
// Bias chain: VCC → R1(4.7k) → [NPN.b] → Rbias(1.1k) → [PNP.b] → R2(4.7k) → GND
// Rbias drops ~1.3V at divider current, matching 2×Vbe to eliminate crossover dead zone
export const classABamp: CircuitPreset = {
  name: 'Class AB Push-Pull',
  nodes: [
    { id: 'v1', type: 'voltage', position: { x: 50, y: 50 }, data: { label: '12V', voltage: 12 } },
    { id: 'mic1', type: 'microphone', position: { x: 50, y: 350 }, data: { label: 'Mic', amplification: 50 } },
    { id: 'cin', type: 'capacitor', position: { x: 250, y: 350 }, data: { label: '10uF', capacitance: 10e-6 } },
    { id: 'r1', type: 'resistor', position: { x: 420, y: 100 }, data: { label: '4.7k', resistance: 4700 } },
    { id: 'rbias', type: 'resistor', position: { x: 520, y: 340 }, data: { label: '1.1k', resistance: 1100 } },
    { id: 'r2', type: 'resistor', position: { x: 420, y: 560 }, data: { label: '4.7k', resistance: 4700 } },
    { id: 'q1', type: 'npn', position: { x: 680, y: 220 }, data: { label: 'NPN', bf: 200 } },
    { id: 'q2', type: 'pnp', position: { x: 680, y: 450 }, data: { label: 'PNP', bf: 200 } },
    { id: 're1', type: 'resistor', position: { x: 850, y: 290 }, data: { label: '22', resistance: 22 } },
    { id: 're2', type: 'resistor', position: { x: 850, y: 420 }, data: { label: '22', resistance: 22 } },
    { id: 'cout', type: 'capacitor', position: { x: 1020, y: 350 }, data: { label: '470uF', capacitance: 470e-6 } },
    { id: 'spk1', type: 'speaker', position: { x: 1200, y: 350 }, data: { label: 'Speaker', acCouple: true, normalize: true } },
    { id: 'g1', type: 'ground', position: { x: 50, y: 650 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-v1-q1c', source: 'v1', target: 'q1', sourceHandle: 'pos', targetHandle: 'c', type: 'smoothstep' },
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g1', source: 'v1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },
    // Bias chain: R1.out = NPN.b, then Rbias, then Rbias.out = PNP.b
    { id: 'e-r1-q1b', source: 'r1', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-r1-rbias', source: 'r1', target: 'rbias', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-rbias-q2b', source: 'rbias', target: 'q2', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-rbias-r2', source: 'rbias', target: 'r2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-gnd', source: 'r2', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    // Input coupling: mic → Cin → NPN base node
    { id: 'e-mic-cin', source: 'mic1', target: 'cin', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cin-bias', source: 'cin', target: 'r1', sourceHandle: 'out', targetHandle: 'out', type: 'smoothstep' },
    { id: 'e-mic-gnd', source: 'mic1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    // Emitter resistors → output
    { id: 'e-q1e-re1', source: 'q1', target: 're1', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q2e-re2', source: 'q2', target: 're2', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-re1-cout', source: 're1', target: 'cout', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-re2-cout', source: 're2', target: 'cout', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q2c-gnd', source: 'q2', target: 'g1', sourceHandle: 'c', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cout-spk', source: 'cout', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-gnd', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const bridgeRectifier: CircuitPreset = {
  name: 'Full Bridge Rectifier',
  nodes: [
    { id: 'vac', type: 'acvoltage', position: { x: 50, y: 200 }, data: { label: '10V 60Hz', amplitude: 10, frequency: 60 } },
    
    // Diode bridge
    { id: 'd1', type: 'diode', position: { x: 300, y: 100 }, data: { label: 'D1' } },
    { id: 'd2', type: 'diode', position: { x: 300, y: 300 }, data: { label: 'D2' } },
    { id: 'd3', type: 'diode', position: { x: 500, y: 100 }, data: { label: 'D3' } },
    { id: 'd4', type: 'diode', position: { x: 500, y: 300 }, data: { label: 'D4' } },
    
    // Load & Filter
    { id: 'rload', type: 'resistor', position: { x: 750, y: 200 }, data: { label: '1k', resistance: 1000 } },
    { id: 'cfilter', type: 'capacitor', position: { x: 900, y: 200 }, data: { label: '100u', capacitance: 100e-6 } },
    
    // Scope
    { id: 'scope1', type: 'scope', position: { x: 1100, y: 200 }, data: { label: 'Input vs Output' } },
    
    // GND
    { id: 'gnd1', type: 'ground', position: { x: 600, y: 500 }, data: { label: 'GND' } },
  ],
  edges: [
    // AC Source to bridge
    { id: 'e-vac-pos-d1', source: 'vac', target: 'd1', sourceHandle: 'pos', targetHandle: 'anode', type: 'smoothstep' },
    { id: 'e-vac-pos-d2', source: 'vac', target: 'd2', sourceHandle: 'pos', targetHandle: 'cathode', type: 'smoothstep' },
    { id: 'e-vac-neg-d3', source: 'vac', target: 'd3', sourceHandle: 'neg', targetHandle: 'anode', type: 'smoothstep' },
    { id: 'e-vac-neg-d4', source: 'vac', target: 'd4', sourceHandle: 'neg', targetHandle: 'cathode', type: 'smoothstep' },
    
    // Bridge Positive output
    { id: 'e-d1-pos', source: 'd1', target: 'rload', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-d3-pos', source: 'd3', target: 'rload', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep' },
    
    // Bridge Negative output (GND)
    { id: 'e-d2-neg', source: 'd2', target: 'gnd1', sourceHandle: 'anode', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-d4-neg', source: 'd4', target: 'gnd1', sourceHandle: 'anode', targetHandle: 'in', type: 'smoothstep' },
    
    // Load and Filter connections
    { id: 'e-rl-c', source: 'rload', target: 'cfilter', sourceHandle: 'in', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-rl-gnd', source: 'rload', target: 'gnd1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-c-gnd', source: 'cfilter', target: 'gnd1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    
    // Scope connections
    { id: 'e-scope-ch1', source: 'vac', target: 'scope1', sourceHandle: 'pos', targetHandle: 'ch1', type: 'smoothstep' },
    { id: 'e-scope-ch2', source: 'rload', target: 'scope1', sourceHandle: 'in', targetHandle: 'ch2', type: 'smoothstep' },
    { id: 'e-scope-gnd', source: 'scope1', target: 'gnd1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const mcuBlink: CircuitPreset = {
  name: 'MCU Blink',
  nodes: [
    { id: 'mcu1', type: 'mcu', position: { x: 100, y: 150 }, data: { label: 'Microcontroller', code: "pinMode('D0', 'OUTPUT');\n\nwhile(true) {\n  digitalWrite('D0', 1);\n  sleep(500);\n  digitalWrite('D0', 0);\n  sleep(500);\n}" } },
    { id: 'r1', type: 'resistor', position: { x: 400, y: 180 }, data: { label: '330Ω', resistance: 330 } },
    { id: 'led1', type: 'led', position: { x: 600, y: 180 }, data: { label: 'LED', color: 'blue', v_drop: 2.0, max_current: 20 } },
    { id: 'g1', type: 'ground', position: { x: 600, y: 350 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-mcu-r1', source: 'mcu1', target: 'r1', sourceHandle: 'D0', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-r1-led1', source: 'r1', target: 'led1', sourceHandle: 'out', targetHandle: 'anode', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-led1-g1', source: 'led1', target: 'g1', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const mcuSpeaker: CircuitPreset = {
  name: 'MCU Speaker Tone',
  nodes: [
    { id: 'mcu1', type: 'mcu', position: { x: 100, y: 150 }, data: { label: 'Microcontroller', code: "pinMode('D1', 'OUTPUT');\n\n// Generate 500Hz square wave\nconst halfPeriod = 1;\nwhile(true) {\n  digitalWrite('D1', 1);\n  sleep(halfPeriod);\n  digitalWrite('D1', 0);\n  sleep(halfPeriod);\n}" } },
    { id: 'spk1', type: 'speaker', position: { x: 400, y: 150 }, data: { label: 'Speaker' } },
    { id: 'g1', type: 'ground', position: { x: 400, y: 300 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-mcu-spk1', source: 'mcu1', target: 'spk1', sourceHandle: 'D1', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-spk1-g1', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const mcuAnalogOut: CircuitPreset = {
  name: 'MCU Sine Wave (A0)',
  nodes: [
    { id: 'mcu1', type: 'mcu', position: { x: 100, y: 150 }, data: { label: 'Microcontroller', code: "pinMode('A0', 'OUTPUT');\n\n// Generate ~5Hz sine wave\nconst freq = 5;\nconst points = 20;\nconst dt = 1000 / (freq * points);\n\nwhile(true) {\n  for(let i=0; i<points; i++) {\n    const rad = (i / points) * 2 * Math.PI;\n    const val = (Math.sin(rad) + 1) * 127;\n    analogWrite('A0', val);\n    \n    // Log first period\n    if (millis() < 1000 / freq) {\n      Serial.println(`t=${millis().toFixed(0)} val=${val.toFixed(0)}`);\n    }\n    sleep(dt);\n  }\n}" } },
    { id: 'scope1', type: 'scope', position: { x: 400, y: 150 }, data: { label: 'A0 Output' } },
    { id: 'g1', type: 'ground', position: { x: 400, y: 300 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-mcu-scope', source: 'mcu1', target: 'scope1', sourceHandle: 'A0', targetHandle: 'ch1', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-scope-g1', source: 'scope1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const mcuAnalogIn: CircuitPreset = {
  name: 'MCU Analog Read (A0)',
  nodes: [
    { id: 'vac1', type: 'acvoltage', position: { x: 50, y: 180 }, data: { label: '5V 40Hz', amplitude: 5, frequency: 40 } },
    { id: 'mcu1', type: 'mcu', position: { x: 300, y: 150 }, data: { label: 'Microcontroller', code: "pinMode('A0', 'INPUT');\n\n// Read A0 every 5ms and log it\nwhile(true) {\n  const val = analogRead('A0');\n  Serial.println(`t=${millis()}ms -> A0: ${val}`);\n  sleep(5);\n}" } },
    { id: 'g1', type: 'ground', position: { x: 50, y: 300 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 300, y: 350 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-vac-mcu', source: 'vac1', target: 'mcu1', sourceHandle: 'pos', targetHandle: 'A0', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-vac-gnd', source: 'vac1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-mcu-gnd', source: 'mcu1', target: 'g2', sourceHandle: 'GND', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const mcuPassThrough: CircuitPreset = {
  name: 'MCU Audio Sampler',
  nodes: [
    { id: 'sg1', type: 'signalgen', position: { x: 50, y: 180 }, data: { label: '440Hz Sine', waveform: 'sine', frequency: 440, amplitude: 5 } },
    { id: 'mcu1', type: 'mcu', position: { x: 300, y: 150 }, data: { label: 'Microcontroller', code: "pinMode('A0', 'INPUT');\npinMode('A1', 'OUTPUT');\n\n// Pass-through sampling at 1kHz (1ms)\nwhile(true) {\n  const val = analogRead('A0');\n  // Convert 10-bit ADC to 8-bit DAC\n  analogWrite('A1', val / 4);\n  sleep(1);\n}" } },
    { id: 'spk1', type: 'speaker', position: { x: 600, y: 180 }, data: { label: 'Speaker' } },
    { id: 'g1', type: 'ground', position: { x: 50, y: 300 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 300, y: 350 }, data: { label: 'GND' } },
    { id: 'g3', type: 'ground', position: { x: 600, y: 300 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-sg-mcu', source: 'sg1', target: 'mcu1', sourceHandle: 'out', targetHandle: 'A0', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-sg-gnd', source: 'sg1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-mcu-spk', source: 'mcu1', target: 'spk1', sourceHandle: 'A1', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-spk-gnd', source: 'spk1', target: 'g3', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
    { id: 'e-mcu-gnd', source: 'mcu1', target: 'g2', sourceHandle: 'GND', targetHandle: 'in', type: 'smoothstep', style: { strokeWidth: 2, stroke: '#555' } },
  ]
};

export const mcuCleanAudioSampler: CircuitPreset = {
  name: 'MCU Clean Audio Sampler',
  nodes: [
    // Signal generation (2V amplitude so it swings 0.5V to 4.5V when biased at 2.5V)
    { id: 'sg1', type: 'signalgen', position: { x: 50, y: 300 }, data: { label: '440Hz Sine', waveform: 'sine', frequency: 440, amplitude: 2 } },
    { id: 'cin', type: 'capacitor', position: { x: 200, y: 300 }, data: { label: '10µF AC Couple', capacitance: 10e-6 } },
    
    // DC Bias network
    { id: 'v1', type: 'voltage', position: { x: 350, y: 50 }, data: { label: '5V', voltage: 5 } },
    { id: 'r1', type: 'resistor', position: { x: 350, y: 150 }, data: { label: '10k', resistance: 10000 } },
    { id: 'r2', type: 'resistor', position: { x: 350, y: 400 }, data: { label: '10k', resistance: 10000 } },
    
    // Microcontroller
    { id: 'mcu1', type: 'mcu', position: { x: 550, y: 250 }, data: { label: 'Microcontroller', code: "pinMode('A0', 'INPUT');\npinMode('A1', 'OUTPUT');\n\n// 10kHz sampling for high fidelity\nwhile(true) {\n  const val = analogRead('A0');\n  analogWrite('A1', val / 4);\n  sleep(0.1);\n}" } },
    
    // Reconstruction Low-Pass Filter
    { id: 'rout', type: 'resistor', position: { x: 800, y: 250 }, data: { label: '1k', resistance: 1000 } },
    { id: 'cout', type: 'capacitor', position: { x: 950, y: 400 }, data: { label: '0.1µF LPF', capacitance: 0.1e-6 } },
    
    // Output
    { id: 'spk1', type: 'speaker', position: { x: 1100, y: 250 }, data: { label: 'Speaker' } },
    
    // Grounds
    { id: 'g1', type: 'ground', position: { x: 50, y: 500 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 350, y: 500 }, data: { label: 'GND' } },
    { id: 'g3', type: 'ground', position: { x: 950, y: 500 }, data: { label: 'GND' } },
  ],
  edges: [
    // Signal source
    { id: 'e-sg-cin', source: 'sg1', target: 'cin', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-sg-g1', source: 'sg1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    
    // Bias divider & AC coupling mix
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g2', source: 'v1', target: 'g2', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r1-mix', source: 'r1', target: 'r2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-g2', source: 'r2', target: 'g2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cin-mix', source: 'cin', target: 'r2', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    
    // MCU input
    { id: 'e-mix-mcu', source: 'r2', target: 'mcu1', sourceHandle: 'in', targetHandle: 'A0', type: 'smoothstep' },
    { id: 'e-mcu-g2', source: 'mcu1', target: 'g2', sourceHandle: 'GND', targetHandle: 'in', type: 'smoothstep' },
    
    // MCU output to Filter
    { id: 'e-mcu-rout', source: 'mcu1', target: 'rout', sourceHandle: 'A1', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-rout-cout', source: 'rout', target: 'cout', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cout-g3', source: 'cout', target: 'g3', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    
    // Filter to Speaker
    { id: 'e-filt-spk', source: 'rout', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-g3', source: 'spk1', target: 'g3', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const mixedLogicBlink: CircuitPreset = {
  name: 'Mixed Logic Blink',
  nodes: [
    { id: 'sg1', type: 'signalgen', position: { x: 50, y: 100 }, data: { label: 'Clock 1Hz', waveform: 'square', frequency: 1, amplitude: 5 } },
    { id: 'sg2', type: 'signalgen', position: { x: 50, y: 300 }, data: { label: 'Clock 2Hz', waveform: 'square', frequency: 2, amplitude: 5 } },
    { id: 'and1', type: 'and', position: { x: 300, y: 200 }, data: { label: 'AND Gate' } },
    { id: 'r1', type: 'resistor', position: { x: 500, y: 200 }, data: { label: '330Ω', resistance: 330 } },
    { id: 'led1', type: 'led', position: { x: 700, y: 200 }, data: { label: 'Output', color: 'lime', v_drop: 2.0, max_current: 20 } },
    { id: 'g1', type: 'ground', position: { x: 700, y: 350 }, data: { label: 'GND' } },
    { id: 'g2', type: 'ground', position: { x: 50, y: 200 }, data: { label: 'GND' } },
    { id: 'g3', type: 'ground', position: { x: 50, y: 400 }, data: { label: 'GND' } },
  ],
  edges: [
    { id: 'e-sg1-and', source: 'sg1', target: 'and1', sourceHandle: 'out', targetHandle: 'in1', type: 'smoothstep' },
    { id: 'e-sg2-and', source: 'sg2', target: 'and1', sourceHandle: 'out', targetHandle: 'in2', type: 'smoothstep' },
    { id: 'e-sg1-gnd', source: 'sg1', target: 'g2', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-sg2-gnd', source: 'sg2', target: 'g3', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-and-r1', source: 'and1', target: 'r1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r1-led', source: 'r1', target: 'led1', sourceHandle: 'out', targetHandle: 'anode', type: 'smoothstep' },
    { id: 'e-led-gnd', source: 'led1', target: 'g1', sourceHandle: 'cathode', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const presets: Record<string, CircuitPreset> = {
  basicBlink,
  timer555Blink,
  sineAudio,
  micSpeaker,
  bjtAmp,
  classBamp,
  classABamp,
  bridgeRectifier,
  mcuBlink,
  mcuSpeaker,
  mcuAnalogOut,
  mcuAnalogIn,
  mcuPassThrough,
  mcuCleanAudioSampler,
  mixedLogicBlink
};
