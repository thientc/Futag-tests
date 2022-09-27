#!/usr/bin/env bash

docker build --network=host -t futag_test_curl_ubuntu22 -f curl.Dockerfile .