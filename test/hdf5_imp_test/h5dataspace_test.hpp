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
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

extern "C"{
#include <hdf5.h>
}

#include<vector>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/h5dataspace.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class h5dataspace_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(h5dataspace_test);
        CPPUNIT_TEST(test_default_construction); 
        CPPUNIT_TEST(test_object_construction);
        CPPUNIT_TEST(test_container_construction);
        CPPUNIT_TEST(test_current_iterator);
        CPPUNIT_TEST(test_grow);
        CPPUNIT_TEST_SUITE_END();

        hsize_t dims[3] = {10,20,3};
    public:
        void setUp();
        void tearDown();

        void test_default_construction();
        void test_object_construction();
        void test_init_list_construction();
        void test_container_construction();
        void test_current_iterator();
        void test_grow();
};

