import { Simulation } from "../src/simulationLink.ts";
import { ensureFileFetch } from "./runSimulationRegressionTest.ts";

/**
 * This test specifically checks for the regression where the simulation 
 * would hang indefinitely due to a broken async bridge or missing resolve() 
 * in the EM_ASYNC_JS callback.
 */
async function testAsyncHang(): Promise<void> {
  ensureFileFetch();
  
  const sim = new Simulation();
  // A simple transient analysis that requires multiple yields back to JS
  const netlist = `* Simple RC circuit for hang test
R1 1 2 1k
C1 2 0 1u
V1 1 0 5
.tran 0.1m 5m
.end
`;

  console.log("Starting simulation with 10s timeout guard...");
  
  const timeoutPromise = new Promise((_, reject) => 
    setTimeout(() => reject(new Error("Simulation timed out! The async bridge might be hanging.")), 10000)
  );

  try {
    await sim.start();
    sim.setNetList(netlist);
    
    const resultPromise = sim.runSim();
    
    const result = await Promise.race([resultPromise, timeoutPromise]) as any;
    
    console.log("Simulation finished successfully!");
    console.log(`Received ${result.numPoints} points.`);
    
    if (result.numPoints > 0) {
      console.log("Test PASSED: Async bridge is working.");
      process.exit(0);
    } else {
      throw new Error("Simulation returned no points.");
    }
  } catch (error: any) {
    console.error("Test FAILED:", error.message);
    process.exit(1);
  }
}

testAsyncHang().catch(e => {
    console.error("Fatal error in test runner:", e);
    process.exit(1);
});
