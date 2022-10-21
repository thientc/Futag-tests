#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget http://hg.nginx.org/nginx/archive/39a422cf9876.tar.gz

tar xf 39a422cf9876.tar.gz

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."