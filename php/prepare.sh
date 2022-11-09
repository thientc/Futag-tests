#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f php-7.4.30.tar.gz ]; then
    wget https://github.com/php/php-src/archive/refs/tags/php-7.4.30.tar.gz
fi

tar xf php-7.4.30.tar.gz
cd php-src-php-7.4.30
./buildconf --force
echo "-- [Futag]: Run python build.py for generating fuzz-drivers."