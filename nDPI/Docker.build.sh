#!/usr/bin/env bash

docker build --network=host -t futag_test_ndpi_ubuntu22 -f nDPI.Dockerfile .