#!/bin/bash
# Replaces run.sh logic to build with XSPICE
sed -i 's/--disable-xspice/--enable-xspice --disable-shared/g' Docker/run.sh
