#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f libpq-standalone-REL_15_1.tar.gz ]; then
    wget https://gitlab.com/sabelka/libpq-standalone/-/archive/REL_15_1/libpq-standalone-REL_15_1.tar.gz
fi
tar xf libpq-standalone-REL_15_1.tar.gz
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."