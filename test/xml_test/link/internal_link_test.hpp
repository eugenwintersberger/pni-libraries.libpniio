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
//  Created on: Apr 22, 2015
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/link.hpp>
#include <pni/io/nx/algorithms.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;


class internal_link_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(internal_link_test);
        CPPUNIT_TEST(test_link);
        CPPUNIT_TEST_SUITE_END();

        xml::node root_node;
        xml::node link_node;
        
        h5::nxfile nxs_file;        
        
        static const string xml_file_name;
        static const string nxs_file_name;
    public:
        void setUp();
        void tearDown();
        
        void test_link();
};

const string internal_link_test::xml_file_name = "internal_link_test.xml";
const string internal_link_test::nxs_file_name = "internal_link_test.nxs";
