#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f lighttpd-1.4.68.tar.gz ]; then
    wget https://download.lighttpd.net/lighttpd/releases-1.4.x/lighttpd-1.4.68.tar.gz
fi
tar xf lighttpd-1.4.68.tar.gz
echo "-- [Futag]: Run python3 build.py for generating fuzz-drivers."
