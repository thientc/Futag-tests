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

echo "-- [Futag]: Getting stable Futag package."
if [ ! -f futag-llvm.2.0.4.tar.xz ]; then
    wget https://github.com/ispras/Futag/releases/download/2.0.4/futag-llvm.2.0.4.tar.xz
fi
echo "-- [Futag]: Extracting..."
tar xf futag-llvm.2.0.4.tar.xz
cd futag-llvm
./buildAFLplusplus.sh
echo "-- [Futag]: Futag package is extracted to futag-llvm folder!"