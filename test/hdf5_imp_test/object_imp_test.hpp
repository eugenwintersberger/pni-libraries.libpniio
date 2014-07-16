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
// Created on: Jul 14, 2014
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

using namespace pni::io::nx::h5;

class object_imp_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(object_imp_test);
        CPPUNIT_TEST(test_default);
        CPPUNIT_TEST(test_create_from_attribute); 
        CPPUNIT_TEST(test_create_from_dataset);
        CPPUNIT_TEST(test_create_from_datatype);
        CPPUNIT_TEST(test_create_from_dataspace);
        CPPUNIT_TEST(test_create_from_file);
        CPPUNIT_TEST(test_create_from_plist);
        CPPUNIT_TEST(test_move);
        CPPUNIT_TEST(test_copy);
        CPPUNIT_TEST_SUITE_END();
    private:
        hid_t file;
        hid_t group;
        hid_t type;
        hid_t dataspace;
        hid_t dataset;

    public:
        void setUp();
        void tearDown();

        void test_default();
        void test_create_from_dataset();
        void test_create_from_attribute();
        void test_create_from_dataspace();
        void test_create_from_datatype();
        void test_create_from_file();
        void test_create_from_plist();
        void test_move();
        void test_copy();

};

