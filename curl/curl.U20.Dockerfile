# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

#Download base image ubuntu 20.04
FROM ubuntu:20.04

LABEL maintainer="thientcgithub@gmail.com"
LABEL description="This is custom Docker Image based on Ubuntu 20.04 for testing Futag on curl."

RUN apt update --fix-missing
RUN export DEBIAN_FRONTEND=noninteractive
RUN ln -fs /usr/share/zoneinfo/Europe/Moscow /etc/localtime
RUN apt-get install -y tzdata
RUN dpkg-reconfigure --frontend noninteractive tzdata

RUN apt install -y apt-utils libncurses5 gcc g++ make gdb openssh-client git wget xz-utils python3 python3-pip python-is-python3  nano cmake libtool libssl-dev
RUN useradd -ms /bin/bash futag

USER futag
WORKDIR /home/futag/
RUN git clone https://github.com/thientc/Futag-tests.git
WORKDIR /home/futag/Futag-tests
RUN ./get-Futag.sh

USER root
RUN pip install futag-llvm/python-package/futag-1.3.tar.gz

USER futag 
WORKDIR /home/futag/Futag-tests/curl
RUN ./prepare.sh
RUN python3 build.py