import { createNgspiceSpiceEngine } from '@tscircuit/ngspice-spice-engine';

async function main() {
  const engine = await createNgspiceSpiceEngine();
  const netlist = `
V_sg1 N0 0 PULSE(-5 5 0 1n 1n 0.5 1)
R_r1 N0 N1 330
R_ammeter N1 int_led 1
D_led1 int_led 0 LED_MODEL
.model LED_MODEL D(IS=1e-22 RS=5 N=1.66666)
.save all
.tran 1m 1s
.end
`;
  console.log("Simulating...");
  const result = await engine.simulate(netlist);
  
  const anode = result.voltageGraphs.find(g => g.name.toLowerCase() === 'n1');
  const intg = result.voltageGraphs.find(g => g.name.toLowerCase() === 'int_led');
  
  if (!anode || !intg) {
     console.log("Nodes not found!", anode, intg);
     return;
  }
  
  console.log("Time points length:", anode.time_points.length);
  let onCount = 0;
  let offCount = 0;
  for (let i = 0; i < anode.time_points.length; i++) {
     const t = anode.time_points[i];
     const vA = anode.voltage_levels[i];
     const vI = intg.voltage_levels[i];
     const current = (vA - vI) / 1.0 * 1000;
     if (current > 0.5) onCount++;
     else offCount++;
     
     if (i % 100 === 0) {
        console.log(`t=${t.toFixed(3)}s, I=${current.toFixed(2)}mA`);
     }
  }
  console.log(`ON states: ${onCount}, OFF states: ${offCount}`);
}

main().catch(console.error);
