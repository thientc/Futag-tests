#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget https://gitlab.com/sabelka/libpq-standalone/-/archive/REL_14_4/libpq-standalone-REL_14_4.tar.gz

tar xf libpq-standalone-REL_14_4.tar.gz
mv libpq-standalone-REL_14_4  libpq-standalone
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."