#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

wget http://github.com/zeux/pugixml/releases/download/v1.12/pugixml-1.12.tar.gz
tar xf pugixml-1.12.tar.gz
mv pugixml-1.12 pugixml
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."