#!/bin/bash

rm -rf .svace-dir
/home/thientc/svace/bin/svace init
/home/thientc/svace/bin/svace build --force-debug-info python3 build.py
/home/thientc/svace/bin/svace analyze
/home/thientc/svace/bin/svace history import
/home/thientc/svace/bin/svace server single-start
