#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f v1.9.2.tar.gz ]; then
    wget https://github.com/confluentinc/librdkafka/archive/refs/tags/v1.9.2.tar.gz
fi
tar xf v1.9.2.tar.gz

echo "-- [Futag]: Run python build.py for generating fuzz-drivers."