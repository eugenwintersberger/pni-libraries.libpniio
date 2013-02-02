/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Aug 13, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

extern "C" {
#include <hdf5.h>
}


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/H5NamedObject.hpp>

using namespace pni::io::nx::h5;

//cannot construct an H5Object type directly so we need a small helper class
class H5TestObject:public H5NamedObject
{
    public:
        H5TestObject(hid_t id):H5NamedObject(id) {};
};

class H5NamedObjectTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5NamedObjectTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_destruction);
        CPPUNIT_TEST(test_comparison);
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
        void test_creation();
        void test_assignment();
        void test_destruction();
        void test_comparison();
};

