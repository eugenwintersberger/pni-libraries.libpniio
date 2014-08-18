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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once


extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nxlink_type.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class group_imp_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(group_imp_test);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_open_by_name);
        CPPUNIT_TEST(test_open_by_index);
        CPPUNIT_TEST(test_parent);
        CPPUNIT_TEST(test_create_scalar_attribute);
        CPPUNIT_TEST(test_create_mdim_attribute);
        CPPUNIT_TEST(test_get_attribute_by_name);
        CPPUNIT_TEST(test_get_attribute_by_index);
        CPPUNIT_TEST(test_delete_attribute);
        CPPUNIT_TEST(test_remove);
        CPPUNIT_TEST_SUITE_END();
    private:
        file_imp file;
        group_imp root_group;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_open_by_name();
        void test_open_by_index();
        void test_parent();
        void test_create_scalar_attribute();
        void test_create_mdim_attribute();
        void test_get_attribute_by_name();
        void test_get_attribute_by_index();
        void test_delete_attribute();
        void test_remove();
    
};
