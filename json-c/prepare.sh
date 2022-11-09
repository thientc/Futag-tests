#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


if [ ! -f json-c-0.16-20220414.tar.gz ]; then
    wget https://github.com/json-c/json-c/archive/refs/tags/json-c-0.16-20220414.tar.gz
fi
tar xf json-c-0.16-20220414.tar.gz

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."