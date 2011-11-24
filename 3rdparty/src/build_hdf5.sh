#!/bin/bash

tar -xjf hdf*.tar.bz2
cd hdf5*

./configure --prefix=$1 --disable-cxx --disable-fortran --disable-hl\
    --enable-threadsafty --with-pthread=/usr

make -j2
make install
