#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

# libudunits2-dev libnetcdf-dev


rm -rf json-c-json-c-0.16-20220414/.futag-consumer/* 
rm -rf gdal-3.4.1
tar xf gdal_3.4.1+dfsg.orig.tar.xz

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."