#!/usr/bin/env bash

docker run -it --platform linux/x86_64 --rm --privileged --network host -v `pwd`:/host --name Futag_test_ubuntu22 Futag_test_ubuntu22 /bin/bash