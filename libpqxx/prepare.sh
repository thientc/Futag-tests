#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f 7.7.4.tar.gz ]; then
    wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.4.tar.gz
fi

tar xf 7.7.4.tar.gz
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."