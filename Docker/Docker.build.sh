#!/usr/bin/env bash

docker build --network=host --platform linux/x86_64 -t Futag_test_ubuntu22 -f Ubuntu22.Dockerfile .