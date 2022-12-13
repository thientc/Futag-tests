#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f FreeImage3180.zip ]; then
    wget http://downloads.sourceforge.net/freeimage/FreeImage3180.zip
fi

unzip FreeImage3180.zip

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."