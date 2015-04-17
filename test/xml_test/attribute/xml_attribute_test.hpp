//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 16, 2013
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/core/arrays.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;


//!
//! \brief test for XML attribute operations
//! 
//! This test checks operations on XML attribute data. This includes checking 
//! for attribute existsance and reading data from attributes.
//!
class xml_attribute_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(xml_attribute_test);
        CPPUNIT_TEST(test_has_attribute);
        CPPUNIT_TEST(test_has_data);
        CPPUNIT_TEST(test_read_data_int);
        CPPUNIT_TEST(test_read_data_uint);
        CPPUNIT_TEST(test_read_data_float);
        CPPUNIT_TEST(test_read_array_int);
        CPPUNIT_TEST(test_read_array_float);
        CPPUNIT_TEST_SUITE_END();

        xml::node root;
        xml::node child;

    public:
        void setUp();
        void tearDown();
       
        void test_has_attribute();
        void test_has_data();
        void test_read_data_int();
        void test_read_data_uint();
        void test_read_data_float();
        void test_read_array_int();
        void test_read_array_float();


};
