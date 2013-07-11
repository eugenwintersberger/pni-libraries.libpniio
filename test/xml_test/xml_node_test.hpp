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

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

static const string node_from_string_str = "<node>\n<group> </group>\n<group>"
                                    " </group>\n<group> </group>\n </node>";


class xml_node_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(xml_node_test);
        CPPUNIT_TEST(test_node_from_file);
        CPPUNIT_TEST(test_node_from_string);
        CPPUNIT_TEST_SUITE_END();

        string xml_str1;
    public:
        void setUp();
        void tearDown();
        
        void test_node_from_file();
        void test_node_from_string();

};
