FROM ubuntu:19.10

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq install -y software-properties-common curl
RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian eoan main" -y
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq -y dist-upgrade

RUN /bin/bash -c 'echo "Europe/Berlin" > /etc/timezone'
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq -y install cmake ninja-build python-pip g++ doxygen python-sphinx git libboost-all-dev gfortran
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get  -y install libpnicore1.1.0-dev libpnicore1.1.0 libh5cpp0.3.2-dev libh5cpp0.3.2 libhdf5-dev

RUN apt-get clean
RUN pip install conan
RUN pip install gitpython

RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

RUN conan user
RUN mkdir /src
WORKDIR /src
