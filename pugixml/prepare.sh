#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).


if [ ! -f pugixml-1.12.tar.gz ]; then
    wget http://github.com/zeux/pugixml/releases/download/v1.12/pugixml-1.12.tar.gz
fi
tar xf pugixml-1.12.tar.gz

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."
