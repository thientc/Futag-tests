#!/usr/bin/env bash

docker run -it --rm --privileged --network host -v `pwd`:/host --name futag_test_curl_ubuntu20 futag_test_curl_ubuntu20 /bin/bash