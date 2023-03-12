FROM ubuntu:23.04

RUN apt -q -y update
RUN apt -q -y upgrade
RUN apt-get -q -y install llvm build-essential python3 clang

COPY . .
RUN make
RUN make all
