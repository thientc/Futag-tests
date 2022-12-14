#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f v8.14.0.tar.gz ]; then
    wget https://github.com/libvips/libvips/archive/refs/tags/v8.14.0.tar.gz
fi
tar xf v8.14.0.tar.gz

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."