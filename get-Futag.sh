#!/bin/bash

echo "************************************************"
echo "*      ______  __  __  ______  ___     ______  *"
echo "*     / ____/ / / / / /_  __/ /   |   / ____/  *"
echo "*    / /_    / / / /   / /   / /| |  / / __    *"
echo "*   / __/   / /_/ /   / /   / ___ | / /_/ /    *"
echo "*  /_/      \____/   /_/   /_/  |_| \____/     *"
echo "*                                              *"
echo "*     Fuzzing targets Automated Generator       *"
echo "*                                              *"
echo "************************************************"
echo "*    This script prepares  testing libraries   *"
echo "************************************************"
echo ""

echo "-- [Futag]: Getting latest Futag package."
wget https://github.com/ispras/Futag/releases/download/latest/futag-llvm-package.latest.tar.xz

echo "-- [Futag]: Extracting..."
tar xf futag-llvm-package.latest.tar.xz
echo "-- [Futag]: Done!"
