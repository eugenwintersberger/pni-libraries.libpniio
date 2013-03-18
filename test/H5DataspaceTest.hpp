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
 * Created on: Jan 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

extern "C"{
#include <hdf5.h>
}

#include<vector>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/H5Dataspace.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5DataspaceTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5DataspaceTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef std::vector<size_t> shape_t;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
        void test_resize();
    
};

