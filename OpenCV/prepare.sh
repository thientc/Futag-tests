#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f 4.6.0.tar.gz ]; then
    wget https://github.com/opencv/opencv/archive/refs/tags/4.6.0.tar.gz
fi
tar xf 4.6.0.tar.gz
echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."