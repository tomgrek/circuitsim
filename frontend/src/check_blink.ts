
import { createNgspiceSpiceEngine } from '@tscircuit/ngspice-spice-engine';
import { generateSpiceNetlist } from './utils/spice';

const basicBlink = {
  nodes: [
    { id: 'sg1', type: 'signalgen', data: { label: 'SIGNALGEN', waveform: 'square', frequency: 1, amplitude: 5 } },
    { id: 'r1', type: 'resistor', data: { label: '330Ω', resistance: 330 } },
    { id: 'led1', type: 'led', data: { label: 'LED', color: 'red', v_drop: 2.0, max_current: 20 } },
    { id: 'g1', type: 'ground', data: { label: 'GND' } },
    { id: 'g2', type: 'ground', data: { label: 'GND' } },
  ],
  edges: [
    { source: 'sg1', target: 'r1', sourceHandle: 'out', targetHandle: 'in' },
    { source: 'r1', target: 'led1', sourceHandle: 'out', targetHandle: 'anode' },
    { source: 'led1', target: 'g1', sourceHandle: 'cathode', targetHandle: 'in' },
    { source: 'sg1', target: 'g2', sourceHandle: 'gnd', targetHandle: 'in' },
  ]
};

async function runTest() {
  console.log("Generating netlist...");
  const { netlist, portToNet } = generateSpiceNetlist(basicBlink.nodes as any, basicBlink.edges as any);
  console.log("Netlist generated:");
  console.log(netlist);
  console.log("Port to Net map:", portToNet);

  try {
    console.log("Initializing simulation engine...");
    const engine = await createNgspiceSpiceEngine();
    console.log("Engine initialized. Starting simulation...");
    
    // Set a timeout to avoid hanging forever
    const timeoutPromise = new Promise((_, reject) => 
      setTimeout(() => reject(new Error("Simulation timed out")), 10000)
    );
    
    const simPromise = engine.simulate(netlist);
    
    const result = await Promise.race([simPromise, timeoutPromise]) as any;
    console.log("Simulation completed successfully!");
    
    const graphs = result?.simulationResultCircuitJson?.filter(
      (r: any) => r.type === "simulation_transient_voltage_graph"
    ) || [];
    
    console.log(`Found ${graphs.length} voltage graphs.`);
    graphs.forEach((g: any) => {
      console.log(`Graph: ${g.name}, Points: ${g.voltage_levels.length}`);
    });

    // Check LED specific nodes
    const anodeNet = portToNet['led1-anode'];
    const intNet = 'int_led_led1';
    
    const findGraph = (name: string) => graphs.find((g: any) => {
        const n = g.name.toLowerCase();
        return n === name.toLowerCase() || n === `v(${name.toLowerCase()})`;
    });

    const anodeGraph = findGraph(anodeNet);
    const intGraph = findGraph(intNet);

    if (anodeGraph && intGraph) {
      console.log("LED data found!");
      const max_vA = Math.max(...anodeGraph.voltage_levels);
      const max_vI = Math.max(...intGraph.voltage_levels);
      const max_current = (max_vA - max_vI) * 1000; // R=1
      console.log(`Max LED current: ${max_current.toFixed(2)} mA`);
    } else {
      console.log("LED data NOT found in results.");
      if (!anodeGraph) console.log(`Missing anode graph for net: ${anodeNet}`);
      if (!intGraph) console.log(`Missing internal graph for net: ${intNet}`);
    }

  } catch (error) {
    console.error("Test failed:", error);
  }
}

runTest();
