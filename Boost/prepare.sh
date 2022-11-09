#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f php-7.4.30.tar.gz ]; then
    wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0_rc1.tar.gz
fi
tar xf boost_1_80_0_rc1.tar.gz
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."