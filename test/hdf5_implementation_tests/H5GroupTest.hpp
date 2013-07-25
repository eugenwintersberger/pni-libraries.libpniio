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
 * Created on: Jan 13, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once


extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nxlink_type.hpp>
#include <pni/io/nx/h5/H5File.hpp>
#include <pni/io/nx/h5/H5Group.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5GroupTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5GroupTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_openobjects);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST(test_parent);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File file;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_openobjects();
        void test_attributes();
        void test_attribute_manipulation();
        void test_comparison();
        void test_parent();
    
};
