/*
 * nx.cpp
 *
 *  Created on: Jan 5, 2012
 *      Author: Eugen Wintersberger
 */

extern "C"{
    #include<Python.h>
}

#include <boost/python.hpp>
#include <iostream>

#include "../src/NX.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;

void wrap_nxobject();
void wrap_nxgroup();
void wrap_nxfile();
void wrap_nxfield();
void wrap_nxnumericfield();
void wrap_nxstringfield();
void wrap_nxbinaryfield();

BOOST_PYTHON_MODULE(nxh5)
{
    wrap_nxobject();
    wrap_nxgroup();
    wrap_nxfile();
    wrap_nxfield();
    wrap_nxnumericfield();
    wrap_nxstringfield();
    wrap_nxbinaryfield();
}
