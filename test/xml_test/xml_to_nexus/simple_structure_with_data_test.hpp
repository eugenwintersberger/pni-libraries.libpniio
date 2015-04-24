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
//  Created on: Apr 23, 2015
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/xml_to_nexus.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/algorithms.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

static const string xml_file = "simple_structure_with_data.xml";
static const string nxs_file = "simple_structure_with_data.nxs";

class simple_structure_with_data_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(simple_structure_with_data_test);
        CPPUNIT_TEST(test_simple);
        CPPUNIT_TEST_SUITE_END();
        

        h5::nxobject root_group;        
        h5::nxfile   file;
        xml::node    root_node;

        string xml_str1;
        std::vector<int32> int_vec;
        std::vector<float64> float_vec;
    public:
        void setUp();
        void tearDown();
        
        void test_simple();
};
