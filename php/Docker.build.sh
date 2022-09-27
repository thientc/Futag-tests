#!/usr/bin/env bash

docker build --network=host -t futag_test_php7_ubuntu18 -f php7.Dockerfile .