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

BOOST_PYTHON_MODULE(pniutils)
{
    wrap_nxobject();
}
