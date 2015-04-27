//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
//  Created on: Apr 27, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/formatters/formatter.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

class value_formatter_test:public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(value_formatter_test);
        CPPUNIT_TEST(test_uint8);
        CPPUNIT_TEST(test_int8);
        CPPUNIT_TEST(test_uint16);
        CPPUNIT_TEST(test_int16);
        CPPUNIT_TEST(test_uint32);
        CPPUNIT_TEST(test_int32);
        CPPUNIT_TEST(test_uint64);
        CPPUNIT_TEST(test_int64);
        CPPUNIT_TEST(test_float32);
        CPPUNIT_TEST(test_float64);
        CPPUNIT_TEST(test_float128);
        CPPUNIT_TEST(test_complex32);
        CPPUNIT_TEST(test_complex64);
        CPPUNIT_TEST(test_complex128);      
        CPPUNIT_TEST(test_bool);
        CPPUNIT_TEST(test_string);  
        CPPUNIT_TEST_SUITE_END();

        typedef value                 input_type; 
        typedef formatter<input_type> formatter_type;
        formatter_type format;

    public:
        void setUp();
        void tearDown();
        void test_uint8();
        void test_int8();
        void test_uint16();
        void test_int16();
        void test_uint32();
        void test_int32();
        void test_int64();
        void test_uint64();
        void test_float32();
        void test_float64();
        void test_float128();
        void test_complex32();
        void test_complex64();
        void test_complex128();
        void test_bool();
        void test_string();
};

