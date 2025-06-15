#!/bin/bash

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

if [ ! -f json-c-0.16-20220414.tar.gz ]; then
	wget https://github.com/davea42/libdwarf-code/releases/download/v2.0.0/libdwarf-2.0.0.tar.xz
fi

tar xf libdwarf-2.0.0.tar.xz

