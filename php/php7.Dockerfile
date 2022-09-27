# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

#Download base image ubuntu 22.04
FROM ubuntu:18.04

LABEL maintainer="thientc84@gmail.com"
LABEL description="This is custom Docker Image based on Ubuntu 22.04 for testing Futag on php 7.4.30."

RUN apt update --fix-missing
RUN apt install -y apt-utils 
RUN export DEBIAN_FRONTEND=noninteractive
RUN ln -fs /usr/share/zoneinfo/Europe/Moscow /etc/localtime
RUN apt-get install -y tzdata
RUN dpkg-reconfigure --frontend noninteractive tzdata

RUN apt install -y libncurses5 gcc g++ make gdb openssh-client git wget xz-utils python3 python3-pip autoconf nano re2c pkg-config libtool libxml2-dev libsqlite3-dev libbison-dev libssl-dev libiconv-hook-dev libonig-dev pkg-config libcurl4-gnutls-dev

RUN useradd -ms /bin/bash futag

USER futag
WORKDIR /home/futag/
RUN git clone https://github.com/thientc/Futag-tests.git
WORKDIR /home/futag/Futag-tests
RUN ./get-Futag.sh

USER root
RUN pip3 install futag-llvm-package/python-package/futag-1.1.tar.gz

USER futag 
WORKDIR /home/futag/Futag-tests/php
RUN ./prepare.sh
RUN python3 build.py
