#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


rm -rf jsoncpp

git clone --depth 1 https://github.com/open-source-parsers/jsoncpp

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."
