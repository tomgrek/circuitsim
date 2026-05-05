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
  console.log(result);
}

main().catch(console.error);
