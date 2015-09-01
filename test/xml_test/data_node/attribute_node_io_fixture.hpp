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
//  Created on: Apr 15, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/nx/xml/data_node.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*!
\brief test for XML data operations

Test checks operations on XML node data. 
*/
class attribute_node_io_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(attribute_node_io_fixture);
        CPPUNIT_TEST(test_read_scalar);
        CPPUNIT_TEST(test_read_array);
        CPPUNIT_TEST(test_write_scalar);
        CPPUNIT_TEST(test_write_array);
        CPPUNIT_TEST_SUITE_END();

        pni::io::nx::xml::node root, root_array;
        pni::io::nx::xml::node child;

    public:
        void setUp();
        void tearDown();
       
        void test_read_scalar();
        void test_read_array();
        void test_write_scalar();
        void test_write_array();
};
