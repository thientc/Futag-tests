#!/usr/bin/env bash

docker build --network=host -t futag_test_libpq_ubuntu22 -f libpq.Dockerfile .