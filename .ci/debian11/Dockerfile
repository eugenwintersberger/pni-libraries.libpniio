FROM debian:bullseye

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

# RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian bullseye main" > /etc/apt/sources.list.d/debian9de.list'
RUN apt-get update
RUN apt-get install -y base-passwd
RUN apt-get -qq update && apt-get -qq -y install libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps apt-utils curl apt-transport-https gnupg2 ca-certificates
RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian bullseye main" -y
# RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -qq -y install cmake ninja-build python3-pip g++ doxygen python3-sphinx git libboost-all-dev gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras
RUN apt-get -qq update && apt-get -qq -y install libpnicore1.1.1-dev libpnicore1.1.1 libh5cpp0.4.1-dev libh5cpp0.4.1 libhdf5-dev

# add p00user
RUN useradd -rm -d /home/p00user -s /bin/bash p00user
USER p00user
RUN mkdir -p /home/p00user/src
WORKDIR /home/p00user/src
