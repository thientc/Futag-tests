#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget https://github.com/glennrp/libpng/archive/refs/tags/v1.6.35.tar.gz

tar xf v1.6.35.tar.gz
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."