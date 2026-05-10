#!/bin/bash
set -e

# Source EMSDK and Conda
cd /home/boab/circuit/ngspice-wasm/emsdk
source ./emsdk_env.sh
export EMSDK_PYTHON=python3.12

# Source conda
source /home/boab/miniconda3/etc/profile.d/conda.sh
conda activate build_env

# Go to ngspice source
cd /home/boab/circuit/ngspice-wasm/ngspice-ngspice
git checkout .
git clean -fd

# Apply patches (same as in run.sh but for native environment)
echo "Applying patches..."

# Patch control.c (Main loop)
sed -i 's|#include "ngspice/ngspice.h"|#include <emscripten.h>\n\nEM_ASYNC_JS(void, eesim_sleep_hack, (), {\n    if (Module["handleThings"]) {\n        await new Promise((resolve) => {\n            Module["handleThings"]();\n            setTimeout(resolve, 0);\n        });\n    }\n});\n\n#include "ngspice/ngspice.h"|g' ./src/frontend/control.c
sed -i 's|freewl = wlist = getcommand(string);|eesim_sleep_hack();\n\n\t\tfreewl = wlist = getcommand(string);|g' ./src/frontend/control.c

# Patch dctran.c (Transient Analysis)
sed -i 's|#include "ngspice/ngspice.h"|#include <emscripten.h>\nextern void eesim_sleep_hack(void);\n#include "ngspice/ngspice.h"|g' ./src/spicelib/analysis/dctran.c
sed -i 's|ckt->CKTtime += ckt->CKTdelta;|eesim_sleep_hack();\n\t\tckt->CKTtime += ckt->CKTdelta;|g' ./src/spicelib/analysis/dctran.c

# Patch cktop.c (Operating Point)
sed -i 's|#include "ngspice/ngspice.h"|#include <emscripten.h>\nextern void eesim_sleep_hack(void);\n#include "ngspice/ngspice.h"|g' ./src/spicelib/analysis/cktop.c
sed -i 's|while (converged != 0) {|while (converged != 0) {\n\t\teesim_sleep_hack();|g' ./src/spicelib/analysis/cktop.c

# Build cmpp natively FIRST
echo "Building cmpp natively..."
# Clean native build dir
rm -rf native_build
mkdir native_build
cd native_build
../configure --enable-xspice --disable-shared --without-x --with-readline=no
make -C src/xspice/cmpp -j$(nproc)
cd ..

# Copy native cmpp to source tree so it can be used during WASM build
cp native_build/src/xspice/cmpp/cmpp src/xspice/cmpp/cmpp

# Rebuild WASM
echo "Rebuilding WASM..."
# Clean release dir
rm -rf release
mkdir release
mkdir -p release/src/xspice/cmpp
cp native_build/src/xspice/cmpp/cmpp release/src/xspice/cmpp/cmpp

# Run autogen if needed
./autogen.sh

cd release
emconfigure ../configure --disable-debug --disable-openmp --enable-xspice --disable-shared --disable-osdi --without-x --with-readline=no

# Copy .lst files to the build directory so cmpp can find them
echo "Copying .lst files..."
for d in spice2poly digital analog xtradev xtraevt table tlines; do
    mkdir -p src/xspice/icm/$d
    cp ../src/xspice/icm/$d/modpath.lst src/xspice/icm/$d/modpath.lst
    cp ../src/xspice/icm/$d/udnpath.lst src/xspice/icm/$d/udnpath.lst || true
done

# We need to update the Makefile to include ASYNCIFY flags during link
# This time we do it after configure
sed -i 's|$(ngspice_LDADD) $(LIBS)|$(ngspice_LDADD) $(LIBS) -O2 -s ASYNCIFY=1 -s ASYNCIFY_ADVISE=0 -s ASYNCIFY_IGNORE_INDIRECT=0 -s ENVIRONMENT="web,worker" -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS=["FS","Asyncify","callMain"] -o spice.mjs|g' ./src/Makefile

# Patch XSPICE Makefile to cd into the target directory before running cmpp
# This fixes the "Unable to open mod path file modpath.lst" error
sed -i 's|CMPP_IDIR=$(srcdir)/$(@D) CMPP_ODIR=$(@D) $(CMPP) -lst|cd $(@D) \&\& CMPP_IDIR=$(srcdir)/. CMPP_ODIR=. ../$(CMPP) -lst \&\& cd ..|g' ./src/xspice/icm/GNUmakefile
sed -i 's|CMPP_IDIR=$(srcdir)/$(@D) CMPP_ODIR=$(@D) $(CMPP) -ifs|cd $(@D) \&\& CMPP_IDIR=$(srcdir)/. CMPP_ODIR=. ../$(CMPP) -ifs \&\& cd ..|g' ./src/xspice/icm/GNUmakefile
sed -i 's|CMPP_IDIR=$(srcdir)/$(@D) CMPP_ODIR=$(@D) $(CMPP) -mod|cd $(@D) \&\& CMPP_IDIR=$(srcdir)/. CMPP_ODIR=. ../$(CMPP) -mod \&\& cd ..|g' ./src/xspice/icm/GNUmakefile

emmake make -j$(nproc)

# Copy artifacts
echo "Copying artifacts..."
cp src/spice.mjs src/spice.js
cp src/spice.js ../../EEcircuit-engine/src/spice.js
cp src/spice.wasm ../../EEcircuit-engine/src/spice.wasm

echo "Build complete!"
