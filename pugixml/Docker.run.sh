#!/usr/bin/env bash

docker run -it --rm --privileged --network host -v `pwd`:/host --name futag_test_pugixml_ubuntu22 futag_test_pugixml_ubuntu22 /bin/bash