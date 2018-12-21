FROM debian:jessie

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN /bin/bash -c 'echo "deb http://ftp.debian.org/debian jessie-backports main contrib non-free" > /etc/apt/sources.list.d/debian-backports.list'

RUN apt-get -qq update && apt-get -qq install -y software-properties-common curl

RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian jessie main" -y

RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -qq -y install ninja-build python-setuptools g++ doxygen git libboost-all-dev gfortran
RUN apt-get -qq update && apt-get -qq -y -t jessie-backports install cmake
RUN apt-get -qq update && apt-get -qq -y libpnicore1.1.0-dev libpnicore1.1.0 libh5cpp0.1.0-dev libh5cpp0.1.0 libhdf5-dev
RUN apt-get clean

RUN easy_install pip
RUN pip install conan
RUN pip install gitpython

RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

RUN conan user
RUN mkdir /src
WORKDIR /src

