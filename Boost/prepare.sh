#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f boost_1_80_0_rc1.tar.gz ]; then
    wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0_rc1.tar.gz
fi
FUTAG_PATH=/home/futag/Futag-tests/futag-llvm

export CC=$FUTAG_PATH/bin/clang
export CXX=$FUTAG_PATH/bin/clang++
export CFLAGS="-fsanitize=address -g -O0"
export CXXFLAGS="-fsanitize=address -g -O0"
rm -rf boost_1_80_0
tar xf boost_1_80_0_rc1.tar.gz
cd boost_1_80_0
./bootstrap.sh

$FUTAG_PATH/bin/scan-build -enable-checker futag.FutagAnalyzer -analyzer-config futag.FutagAnalyzer:report_dir=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-analysis ./b2 --debug-building stage install --build-dir=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-build --prefix=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-install

echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."

# $FUTAG_PATH/bin/scan-build -enable-checker futag.FutagAnalyzer -analyzer-config futag.FutagAnalyzer:report_dir=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-analysis ./tools/build/src/engine/b2  install --build-dir=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-build --prefix=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-install

# $FUTAG_PATH/bin/scan-build -enable-checker futag.FutagAnalyzer -analyzer-config futag.FutagAnalyzer:report_dir=/home/futag/Futag-tests/Boost/boost_1_80_0/.futag-analysis  ./build.sh --cxx=$FUTAG_PATH/bin/clang++ --cxxflags="-fsanitize=address -g -O0"
