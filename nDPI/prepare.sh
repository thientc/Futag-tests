#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

# wget https://github.com/ntop/nDPI/archive/refs/tags/4.4.tar.gz
tar xf 4.4.tar.gz
mv nDPI-4.4 nDPI
cd nDPI
./autogen.sh
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."