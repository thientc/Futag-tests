# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

#Download base image ubuntu 22.04
FROM ubuntu:22.04

LABEL maintainer="thientc84@gmail.com"
LABEL description="This is custom Docker Image based on Ubuntu 22.04 for testing Futag."

RUN apt update --fix-missing
RUN apt install -y apt-utils
RUN useradd -ms /bin/bash futag

#Установка необходимых библиотек для futag
RUN apt install -y libncurses5 gcc g++ make gdb openssh-client git wget xz-utils python3 python3-pip  nano

USER futag
WORKDIR /home/futag/
RUN git clone https://github.com/thientc/Futag-tests.git
WORKDIR /home/futag/Futag-tests
RUN wget https://github.com/ispras/Futag/releases/download/latest/futag-llvm-package.latest.tar.xz
RUN tar xf futag-llvm-package.latest.tar.xz


USER root
RUN pip install futag-llvm-package/python-package/futag-1.1.tar.gz

USER futag 
WORKDIR /home/futag/Futag-tests/php

USER futag
RUN ./prepare.sh
RUN python3 build.py