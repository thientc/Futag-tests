#!/usr/bin/env bash

docker build --network=host -t futag_test_curl_ubuntu20 -f curl.U20.Dockerfile .