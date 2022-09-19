#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget https://curl.se/download/curl-7.85.0.tar.gz
tar xf curl-7.85.0.tar.gz
mv curl-7.85.0 curl
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."