#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

# libudunits2-dev libnetcdf-dev

echo "Required: libudunits2-dev libnetcdf-dev!"

rm -rf cmor-3.6.1
tar xf cmor_3.6.1.orig.tar.xz

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."