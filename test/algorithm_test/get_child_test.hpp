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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/get_child.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class get_child_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(get_child_test);
        CPPUNIT_TEST(test_field_object);
        CPPUNIT_TEST(test_group_object);
        CPPUNIT_TEST(test_attribute_object);
        CPPUNIT_TEST(test_group_by_name);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        h5::nxfield field;
        h5::nxgroup group,root;
        h5::nxattribute attribute;
        
    public:
        void setUp();
        void tearDown();
        
        void test_group_by_name();
        void test_field_object();
        void test_group_object();
        void test_attribute_object();

};

