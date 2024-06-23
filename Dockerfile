FROM ubuntu:23.04

RUN apt -qq -y update
RUN apt -qq -y upgrade
RUN apt -qq -y upgrade
RUN apt-get -qq -y install build-essential

WORKDIR /usr/src/abaft
COPY . .
RUN make clean abaft test
