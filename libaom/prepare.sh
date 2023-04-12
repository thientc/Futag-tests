#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


# if [ ! -f libmpeg2-0.5.1.tar.gz ]; then
#     wget https://libmpeg2.sourceforge.io/files/libmpeg2-0.5.1.tar.gz
# fi
# tar xf libmpeg2-0.5.1.tar.gz

if [ ! -f 3c65175b1972da4a1992c1dae2365b48d13f9a8d.tar.gz ]; then
    wget https://aomedia.googlesource.com/aom/+archive/3c65175b1972da4a1992c1dae2365b48d13f9a8d.tar.gz
fi
tar xf 3c65175b1972da4a1992c1dae2365b48d13f9a8d.tar.gz -C aom-src

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."
