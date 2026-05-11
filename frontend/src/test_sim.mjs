import { generateSpiceNetlist } from './utils/spice.ts';
import { createNgspiceSpiceEngine } from '@tscircuit/ngspice-spice-engine';

async function run() {
  const nodes = [
    { id: 'mcu-1', type: 'mcu', data: { code: "pinMode('D0', 'OUTPUT');\nwhile(true) {\n  digitalWrite('D0', 1);\n  sleep(500);\n  digitalWrite('D0', 0);\n  sleep(500);\n}" } },
    { id: 'led-1', type: 'led', data: {} },
    { id: 'gnd-1', type: 'ground', data: {} }
  ];
  const edges = [
    { id: 'e1', source: 'mcu-1', target: 'led-1', sourceHandle: 'D0', targetHandle: 'anode' },
    { id: 'e2', source: 'led-1', target: 'gnd-1', sourceHandle: 'cathode', targetHandle: 'in' }
  ];
  
  const { netlist, portToNet } = generateSpiceNetlist(nodes, edges, 1.0, 'normal');
  const engine = await createNgspiceSpiceEngine();
  const res = await engine.simulate(netlist);
  
  const graphs = res.simulationResultCircuitJson.filter(r => r.type === "simulation_transient_voltage_graph");
  const d0_net = portToNet['mcu-1-D0'];
  const graph = graphs.find(g => g.name.toLowerCase() === d0_net.toLowerCase() || g.name.toLowerCase() === `v(${d0_net.toLowerCase()})`);
  
  if (graph) {
    console.log("timestamps_ms first 5:", graph.timestamps_ms.slice(0, 5));
    console.log("timestamps_ms last 5:", graph.timestamps_ms.slice(-5));
  } else {
    console.log("Graph not found");
  }
}
run();
