#!/usr/bin/env bash

docker build --network=host --platform linux/x86_64 -t futag_test_jsonc_ubuntu22 -f json-c.Dockerfile .