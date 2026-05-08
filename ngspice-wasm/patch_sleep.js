const fs = require('fs');
let code = fs.readFileSync('/home/boab/circuit/ngspice-wasm/ngspice-ngspice/src/frontend/control.c', 'utf-8');
code = code.replace(/await new Promise\(\(resolve\) => \{\s*Module\["handleThings"\]\(\);\s*\}\);/g, 'return Module["handleThings"]();');
fs.writeFileSync('/home/boab/circuit/ngspice-wasm/ngspice-ngspice/src/frontend/control.c', code);
