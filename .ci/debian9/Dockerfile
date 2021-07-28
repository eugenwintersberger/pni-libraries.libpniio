FROM debian:stretch

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian stretch main" > /etc/apt/sources.list.d/debian9de.list'

RUN apt-get -qq update && apt-get -qq -y install libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps apt-utils curl apt-transport-https gnupg2 ca-certificates

RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian stretch main" -y
RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -qq -y install cmake ninja-build python3-pip g++ doxygen python3-sphinx git libboost-all-dev gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras
RUN apt-get -qq update && apt-get -qq -y install libh5cpp0.4.0-dev libh5cpp0.4.0 libhdf5-dev

RUN apt-get clean
RUN pip3 install --upgrade jinja2
RUN pip3 install conan
RUN pip3 install gitpython

RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

RUN conan user
RUN mkdir /src
WORKDIR /src
