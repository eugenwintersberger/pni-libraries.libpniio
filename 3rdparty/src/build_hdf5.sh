#!/bin/bash

tar -xjf hdf*.tar.bz2
cd hdf5*

./configure --prefix=$1 --disable-cxx --disable-fortran --disable-hl\
    --enable-threadsafty --with-pthread=/usr\
    --includedir=$1/include/pni/hdf5\
    --libdir=$1/lib/pni/hdf5

make -j2
make install
