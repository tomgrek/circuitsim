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
  name: 'Class B Push-Pull Amp',
  nodes: [
    // Power supply
    { id: 'v1', type: 'voltage', position: { x: 50, y: 50 }, data: { label: '12V', voltage: 12 } },

    // Input: microphone
    { id: 'mic1', type: 'microphone', position: { x: 50, y: 300 }, data: { label: 'Mic', amplification: 100 } },

    // Input coupling capacitor
    { id: 'cin', type: 'capacitor', position: { x: 250, y: 300 }, data: { label: '10uF', capacitance: 10e-6 } },

    // Bias divider (sets quiescent point at VCC/2 = 6V)
    { id: 'r1', type: 'resistor', position: { x: 400, y: 150 }, data: { label: '10k', resistance: 10000 } },
    { id: 'r2', type: 'resistor', position: { x: 400, y: 450 }, data: { label: '10k', resistance: 10000 } },

    // Complementary push-pull pair
    { id: 'q1', type: 'npn', position: { x: 600, y: 200 }, data: { label: 'NPN', bf: 200 } },
    { id: 'q2', type: 'pnp', position: { x: 600, y: 400 }, data: { label: 'PNP', bf: 200 } },

    // Output coupling capacitor & speaker
    { id: 'cout', type: 'capacitor', position: { x: 800, y: 320 }, data: { label: '470uF', capacitance: 470e-6 } },
    { id: 'spk1', type: 'speaker', position: { x: 1000, y: 320 }, data: { label: 'Speaker', acCouple: true, normalize: true } },

    // Grounds
    { id: 'g1', type: 'ground', position: { x: 50, y: 550 }, data: { label: 'GND' } },
  ],
  edges: [
    // Power: VCC to NPN collector, R1 top
    { id: 'e-v1-q1c', source: 'v1', target: 'q1', sourceHandle: 'pos', targetHandle: 'c', type: 'smoothstep' },
    { id: 'e-v1-r1', source: 'v1', target: 'r1', sourceHandle: 'pos', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-v1-g1', source: 'v1', target: 'g1', sourceHandle: 'neg', targetHandle: 'in', type: 'smoothstep' },

    // Bias divider: R1.out → base node ← R2.in
    { id: 'e-r1-base', source: 'r1', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-base-r2', source: 'q1', target: 'r2', sourceHandle: 'b', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-r2-gnd', source: 'r2', target: 'g1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },

    // PNP base tied to same bias point as NPN base
    { id: 'e-r1-q2b', source: 'r1', target: 'q2', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },

    // Input coupling: mic → Cin → base
    { id: 'e-mic-cin', source: 'mic1', target: 'cin', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-cin-base', source: 'cin', target: 'q1', sourceHandle: 'out', targetHandle: 'b', type: 'smoothstep' },
    { id: 'e-mic-gnd', source: 'mic1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },

    // Push-pull output: NPN emitter + PNP emitter tied together → Cout
    { id: 'e-q1e-cout', source: 'q1', target: 'cout', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-q2e-cout', source: 'q2', target: 'cout', sourceHandle: 'e', targetHandle: 'in', type: 'smoothstep' },

    // PNP collector to ground
    { id: 'e-q2c-gnd', source: 'q2', target: 'g1', sourceHandle: 'c', targetHandle: 'in', type: 'smoothstep' },

    // Output: Cout → Speaker → GND
    { id: 'e-cout-spk', source: 'cout', target: 'spk1', sourceHandle: 'out', targetHandle: 'in', type: 'smoothstep' },
    { id: 'e-spk-gnd', source: 'spk1', target: 'g1', sourceHandle: 'gnd', targetHandle: 'in', type: 'smoothstep' },
  ]
};

export const presets: Record<string, CircuitPreset> = {
  basicBlink,
  timer555Blink,
  sineAudio,
  micSpeaker,
  bjtAmp,
  classBamp
};
