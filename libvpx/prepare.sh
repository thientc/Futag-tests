#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


# if [ ! -f libmpeg2-0.5.1.tar.gz ]; then
#     wget https://libmpeg2.sourceforge.io/files/libmpeg2-0.5.1.tar.gz
# fi
# tar xf libmpeg2-0.5.1.tar.gz

if [ ! -f v1.13.0.tar.gz ]; then
    wget https://github.com/webmproject/libvpx/archive/refs/tags/v1.13.0.tar.gz
fi
tar xf v1.13.0.tar.gz

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."
