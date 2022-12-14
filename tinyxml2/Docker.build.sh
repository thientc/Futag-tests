#!/usr/bin/env bash

docker build --network=host --platform linux/x86_64 -t futag_test_tinyxml2_ubuntu22 -f tinyxml2.Dockerfile .