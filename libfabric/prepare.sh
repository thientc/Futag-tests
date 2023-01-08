#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f v1.17.0.tar.gz ]; then
    wget https://github.com/ofiwg/libfabric/archive/refs/tags/v1.17.0.tar.gz
fi
tar xf v1.17.0.tar.gz
cd libfabric-1.17.0
./autogen.sh
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."