#!/usr/bin/env bash

docker build --network=host -t futag_test_luajit_ubuntu22 -f luaJIT.Dockerfile .