#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

rm -rf json-c-json-c-0.16-20220414
tar xf json-c-0.16-20220414.tar.gz

echo "-- [Futag]: Run python3 build.py for building library knowledge db."