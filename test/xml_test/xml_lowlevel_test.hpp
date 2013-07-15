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
 *  Created on: Jul 11, 2013
 *      Author: Eugen Wintersberger
 */

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

static const string node_from_string_str = "<node>\n<group> </group>\n<group>"
                                    " </group>\n<group> </group>\n </node>";
static const string node_from_bad_str = "this has to fail";


class xml_lowlevel_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(xml_lowlevel_test);
        CPPUNIT_TEST(test_read_xml_attribute);
        CPPUNIT_TEST(test_create_group);
        CPPUNIT_TEST(test_read_xml_data_str);
        CPPUNIT_TEST(test_read_xml_array_int_blank);
        CPPUNIT_TEST(test_read_xml_array_int_comma);
        CPPUNIT_TEST(test_read_xml_array_int_semicolon);
        CPPUNIT_TEST(test_read_xml_array_int_fail);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        h5::nxgroup root_group;

        string xml_str1;
        std::vector<int32> int_vec;
        std::vector<float64> float_vec;
    public:
        void setUp();
        void tearDown();
        
        void test_read_xml_attribute();
        void test_read_xml_data_str();
        void test_read_xml_array_int_blank();
        void test_read_xml_array_int_comma();
        void test_read_xml_array_int_semicolon();
        void test_read_xml_array_int_fail();
        void test_create_group();

};
