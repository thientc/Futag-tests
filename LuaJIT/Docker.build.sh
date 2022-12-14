#!/usr/bin/env bash

docker build --network=host --platform linux/x86_64 -t futag_test_luajit_ubuntu22 -f luaJIT.Dockerfile .