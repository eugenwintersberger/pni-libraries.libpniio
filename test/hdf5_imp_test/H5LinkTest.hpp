//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>


#include <pni/io/nx/h5/h5link.hpp>
#include <pni/io/nx/h5/H5File.hpp>
#include <pni/io/nx/h5/H5Group.hpp>
#include <pni/io/nx/h5/H5Dataspace.hpp>
#include <pni/io/nx/h5/H5Datatype.hpp>
#include <pni/io/nx/h5/H5DatatypeFactory.hpp>
#include <pni/io/nx/h5/H5Dataset.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5LinkTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5LinkTest);
        CPPUNIT_TEST(test_internal);
        CPPUNIT_TEST(test_external);
        CPPUNIT_TEST(test_link_type);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file1;
        H5File _file2;
    public:
        void setUp();
        void tearDown();
        void test_internal();
        void test_external();
        void test_link_type();
};
