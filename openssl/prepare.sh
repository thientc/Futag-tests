#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f openssl-1.1.1s.tar.gz ]; then
    wget https://www.openssl.org/source/openssl-1.1.1s.tar.gz
fi
tar xf openssl-1.1.1s.tar.gz
cd openssl-1.1.1s
./config
echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."