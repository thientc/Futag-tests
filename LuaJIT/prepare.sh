#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget https://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz

tar xf LuaJIT-2.1.0-beta3.tar.gz
mv LuaJIT-2.1.0-beta3 LuaJIT

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."