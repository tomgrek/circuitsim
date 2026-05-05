import { createNgspiceSpiceEngine } from '@tscircuit/ngspice-spice-engine';

async function main() {
  const engine = await createNgspiceSpiceEngine();
  const netlist = `Circuit Simulation
.save all
V_v1 NC_v1_pos NC_v1_neg DC 5
X_t555 NC_t555_1 NC_t555_2 NC_t555_3 NC_t555_4 NC_t555_5 NC_t555_6 NC_t555_7 NC_t555_8 NE555
R_r1 NC_r1_in NC_r1_out 10k
R_r2 NC_r2_in NC_r2_out 47k
C_c1 NC_c1_in NC_c1_out 10u
R_r3 NC_r3_in NC_r3_out 330
R_ammeter_led1 NC_led1_anode int_led_led1 1
D_led1 int_led_led1 NC_led1_cathode LED_MODEL_led1
.model LED_MODEL_led1 D(IS=1e-22 RS=5 N=1.6666666666666667)

.SUBCKT NE555 1 2 3 4 5 6 7 8
R1 8 5 5k
R2 5 61 5k
R3 61 1 5k

E1 th_out 0 VOL={V(6)>V(5) ? 5 : 0}
E2 tr_out 0 VOL={V(2)<V(61) ? 5 : 0}

S_SET 8 state tr_out 0 SMOD_ON
S_RST state 1 th_out 0 SMOD_ON
C1 state 1 100p
R4 state 1 100MEG

E_OUT 3 1 VOL={V(state)>2.5 ? V(8) : 0}
S_DIS 7 1 8 state SMOD_DIS

.MODEL SMOD_ON SW(VT=2.5 RON=1k ROFF=100MEG)
.MODEL SMOD_DIS SW(VT=2.5 RON=10 ROFF=100MEG)
.ENDS NE555

* Connections
V_short1 NC_v1_pos NC_t555_8 DC 0
V_short2 NC_v1_pos NC_t555_4 DC 0
V_short3 NC_v1_pos NC_r1_in DC 0
V_short4 NC_v1_neg NC_t555_1 DC 0
V_short5 NC_v1_neg NC_c1_out DC 0
V_short6 NC_v1_neg NC_led1_cathode DC 0
V_short7 NC_r1_out NC_r2_in DC 0
V_short8 NC_r1_out NC_t555_7 DC 0
V_short9 NC_r2_out NC_c1_in DC 0
V_short10 NC_r2_out NC_t555_6 DC 0
V_short11 NC_r2_out NC_t555_2 DC 0
V_short12 NC_t555_3 NC_r3_in DC 0
V_short13 NC_r3_out NC_led1_anode DC 0
V_ground NC_v1_neg 0 DC 0

.tran 1m 1s uic
.end
`;
  console.log("Simulating...");
  const result = await engine.simulate(netlist);
  console.log("Success!", result.simulationResultCircuitJson.length, "graphs");
}

main().catch(console.error);
