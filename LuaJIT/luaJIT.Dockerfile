# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

#Download base image ubuntu 20.04
FROM ubuntu:20.04

LABEL maintainer="thientcgithub@gmail.com"
LABEL description="This is custom Docker Image based on Ubuntu 20.04 for testing Futag."

RUN apt update --fix-missing
RUN apt install -y apt-utils libncurses5 gcc gcc-multilib binutils binutils-gold binutils-dev g++ make gdb openssh-client git wget xz-utils python3 python3-pip python-is-python3  nano cmake libtool
RUN useradd -ms /bin/bash futag

USER futag
WORKDIR /home/futag/
RUN git clone https://github.com/thientc/Futag-tests.git
WORKDIR /home/futag/Futag-tests
RUN ./get-Futag.sh

USER root
RUN pip install /home/futag/Futag-tests/futag-llvm/python-package/futag-2.0.4.tar.gz

USER futag 
WORKDIR /home/futag/Futag-tests/LuaJIT
RUN ./prepare.sh
RUN python3 build.py