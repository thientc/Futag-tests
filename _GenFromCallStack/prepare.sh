#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


if [ ! -d pugixml-1.12 ]; then
    rm -rf pugixml-1.12
fi
tar xf pugixml-1.12.tar.gz

if [ ! -d json-c-json-c-0.16-20220414 ]; then
    rm -rf json-c-json-c-0.16-20220414
fi
tar xf json-c-0.16-20220414.tar.gz

echo "-- [Futag]: Getting Futag 1.3.1:"
if [ ! -f futag-llvm.1.3.1.tar.xz ]; then
    wget https://github.com/ispras/Futag/releases/download/1.3.1/futag-llvm.1.3.1.tar.xz
fi
if [ ! -d futag-llvm ]; then
    rm -rf futag-llvm
fi
echo "-- [Futag]: Extracting Futag 1.3.1 ... "
tar xf futag-llvm.1.3.1.tar.xz

echo "-- [Futag]: Установите Питон-пакет futag.1.3.1.tar.gz:"
echo "$ pip install futag-llvm/python-package/futag-1.3.1.tar.gz"
echo ""

echo "-- [Futag]: Примеры использования:"
echo "$ python futag-llvm/python-package/futag-parse.py <json-file> <path-to-library>"
echo ""
echo "-- [Futag]: Для json-c:"
echo "$ python futag-llvm/python-package/futag-parse.py libjson-c.json json-c-json-c-0.16-20220414"
echo "-- [Futag]: Для pugixml:"
echo "$ python futag-llvm/python-package/futag-parse.py pugixml.json pugixml-1.12"
