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
//************************************************************************
//
// Created on: Jul 22, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
extern "C" {
#include <hdf5.h>
}


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/h5object_types.hpp>

using namespace pni::io::nx::h5;

class h5object_types_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(h5object_types_test);
        CPPUNIT_TEST(test_hdf5_type_plist);
        CPPUNIT_TEST(test_hdf5_type_file);
        CPPUNIT_TEST(test_hdf5_type_group);
        CPPUNIT_TEST(test_hdf5_type_dataset);
        CPPUNIT_TEST(test_hdf5_type_attribute);
        CPPUNIT_TEST(test_hdf5_type_datatype);
        CPPUNIT_TEST(test_hdf5_type_dataspace);
        CPPUNIT_TEST(test_hdf5_type_error);
        CPPUNIT_TEST(test_nexus_type_file);
        CPPUNIT_TEST(test_nexus_type_field);
        CPPUNIT_TEST(test_nexus_type_group);
        CPPUNIT_TEST(test_nexus_type_attribute);
        CPPUNIT_TEST(test_nexus_type_error);
        CPPUNIT_TEST_SUITE_END();
    private:
        object_imp file;
    public:
        void setUp();
        void tearDown();
        
        void test_hdf5_type_plist();
        void test_hdf5_type_file();
        void test_hdf5_type_group();
        void test_hdf5_type_dataset();
        void test_hdf5_type_attribute();
        void test_hdf5_type_datatype();
        void test_hdf5_type_dataspace();
        void test_hdf5_type_error();
        void test_nexus_type_file();
        void test_nexus_type_field();
        void test_nexus_type_group();
        void test_nexus_type_attribute();
        void test_nexus_type_error();

};

