FROM ubuntu:23.04

RUN apt -q -y update
RUN apt -q -y upgrade
RUN apt-get -q -y install build-essential gcc make

COPY . .
RUN make abaft test
