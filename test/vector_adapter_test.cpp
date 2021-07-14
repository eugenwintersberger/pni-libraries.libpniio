/*
 * (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pninexus.
 *
 * pninexus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pninexus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 18, 2014
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/types.hpp>
#include "vector_adapter_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<float128>);

CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(vector_adapter_test<complex128>);
