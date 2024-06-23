FROM ubuntu:23.04

RUN apt -qq -y update
RUN apt -qq -y upgrade
RUN apt -qq -y upgrade
RUN apt-get -qq -y install build-essential
RUN apt-get -qq -y install tree

WORKDIR /usr/src/abaft
COPY . .
RUN tree
RUN make clean abaft test
