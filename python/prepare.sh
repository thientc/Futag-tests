#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


if [ ! -f Python-3.10.11.tar.xz ]; then
    wget https://www.python.org/ftp/python/3.10.11/Python-3.10.11.tar.xz
fi
tar xf Python-3.10.11.tar.xz

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."
