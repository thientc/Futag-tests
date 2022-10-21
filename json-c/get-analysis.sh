#!/usr/bin/env bash
docker create -it --rm --privileged --name futag_test_jsonc_ubuntu22 futag_test_jsonc_ubuntu22 /bin/bash
docker cp futag_test_jsonc_ubuntu22:/home/futag/Futag-tests/json-c/json-c/futag-analysis/futag-analysis-result.json .
docker rm -f futag_test_jsonc_ubuntu22
