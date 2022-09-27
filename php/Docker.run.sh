#!/usr/bin/env bash

docker run -it --rm --privileged --network host -v `pwd`:/host --name futag_test_php7_ubuntu18 futag_test_php7_ubuntu18 /bin/bash