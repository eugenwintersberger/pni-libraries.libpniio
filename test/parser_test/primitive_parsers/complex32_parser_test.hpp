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
//  Created on: Jan 28, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/parsers.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

class complex32_parser_test:public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(complex32_parser_test);
        CPPUNIT_TEST(test_complex_zero);
        CPPUNIT_TEST(test_regular_value_for_j);
        CPPUNIT_TEST(test_regular_value_for_i);
        CPPUNIT_TEST(test_regular_value_for_I);
        CPPUNIT_TEST(test_real_only);
        CPPUNIT_TEST(test_imag_only);
        CPPUNIT_TEST(test_invalid_input);
        CPPUNIT_TEST_SUITE_END();

        typedef complex32              result_type; 
        typedef float32                base_type;
        typedef string::const_iterator iterator_type;
    
        typedef parser<iterator_type,result_type> parser_type;
        parser_type p;

    public:
        void setUp();
        void tearDown();
        void test_complex_zero();
        void test_real_only();
        void test_imag_only();
        void test_regular_value_for_j();
        void test_regular_value_for_i();
        void test_regular_value_for_I();
        void test_invalid_input();
};


