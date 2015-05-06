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
// Created on: Jul 23, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
extern "C" {
#include <hdf5.h>
}


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>

#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>

using namespace pni::io::nx::h5;

class hdf5_utilities_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(hdf5_utilities_test);
        CPPUNIT_TEST(test_get_filename);
        CPPUNIT_TEST(test_get_path);
        CPPUNIT_TEST(test_get_name);
        CPPUNIT_TEST(test_get_parent);
        CPPUNIT_TEST(test_get_parent_path);
        CPPUNIT_TEST_SUITE_END();
    private:
        object_imp file;
        object_imp group;
        object_imp attribute;
        object_imp dataset;
        object_imp root;

        object_imp create_link_create_list() const;
        object_imp create_group(const object_imp &parent,
                                const pni::core::string &name) const;
        object_imp create_dataset(const object_imp &parent,
                                  const pni::core::string &name) const;
        object_imp create_attribute(const object_imp &parent,
                                    const pni::core::string &name) const;
    public:
        void setUp();
        void tearDown();
        
        void test_get_filename();
        void test_get_path();
        void test_get_name();
        void test_get_parent();
        void test_get_parent_path();
};

