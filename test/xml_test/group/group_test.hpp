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
//  Created on: Nov 26, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/group.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class group_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(group_test);
        CPPUNIT_TEST(test_read_1);
        CPPUNIT_TEST(test_read_2);
        CPPUNIT_TEST(test_read_3);
        CPPUNIT_TEST(test_write_1);
        CPPUNIT_TEST_SUITE_END();

        xml::node root;
        xml::node child;
        string buffer;

        h5::nxfile file;
        h5::nxobject root_group;

        void set_xml(const string &fname);

    public:
        void setUp();
        void tearDown();
        
        void test_read_1();
        void test_read_2();
        void test_read_3();

        void test_write_1();
};
