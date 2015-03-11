//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include "nxattribute_partial_io_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<float128>);

CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<complex128>);

CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<binary>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<bool_t>);
CPPUNIT_TEST_SUITE_REGISTRATION(nxattribute_partial_io_test<string>);
