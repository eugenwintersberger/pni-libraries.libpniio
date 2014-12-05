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
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/field.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../uniform_distribution.hpp"


using namespace pni::core;
using namespace pni::io::nx;

class field_to_xml_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(field_to_xml_fixture);
        CPPUNIT_TEST(test_to_xml_1);
        CPPUNIT_TEST(test_to_xml_2);
        CPPUNIT_TEST(test_to_xml_3);
        CPPUNIT_TEST_SUITE_END();

        typedef xml::attribute_data<string> str_attr;
        typedef uniform_distribution<float32> float32_dist;

        h5::nxfile file;
        h5::nxobject root_group,field;
        string buffer;

    public:
        void setUp();
        void tearDown();
    
        void test_to_xml_1();
        void test_to_xml_2();
        void test_to_xml_3();
};
