#!/usr/bin/env bash

docker run -it --platform linux/x86_64 --rm --privileged --network host -v `pwd`:/host --name futag_test_lighttpd_ubuntu22 futag_test_lighttpd_ubuntu22 /bin/bash