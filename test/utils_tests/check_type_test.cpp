/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 9, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "check_type_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<string>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<binary>);
CPPUNIT_TEST_SUITE_REGISTRATION(check_type_test<bool_t>);

