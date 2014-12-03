//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 3, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;


/*!
\brief test for XML data operations

Test checks operations on XML node data. 
*/
class array_attribute_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(array_attribute_fixture);
        CPPUNIT_TEST(test_read_array_int_blank);
        CPPUNIT_TEST(test_read_array_int_comma);
        CPPUNIT_TEST(test_read_array_int_semicolon);
        CPPUNIT_TEST(test_read_array_int_fail);
        CPPUNIT_TEST(test_read_array_float);
        CPPUNIT_TEST_SUITE_END();

        typedef xml::attribute_data<array> attr_data;
        typedef std::vector<int32> int32_vector;
        typedef std::vector<float64> float64_vector;
        std::vector<int32> int_vec;
        std::vector<float64> float_vec;

        xml::node get_first(const string &s) const;
    public:
        void setUp();
        void tearDown();
        
        void test_read_array_int_blank();
        void test_read_array_int_comma();
        void test_read_array_int_semicolon();
        void test_read_array_int_fail();
        void test_read_array_float();
};
