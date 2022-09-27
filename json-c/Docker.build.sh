#!/usr/bin/env bash

docker build --network=host -t futag_test_jsonc_ubuntu22 -f json-c.Dockerfile .