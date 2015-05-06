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


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>

using namespace pni::io::nx::h5;

class attribute_utils_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(attribute_utils_test);
        CPPUNIT_TEST(test_has_attribute);
        CPPUNIT_TEST(test_delete_attribute);
        CPPUNIT_TEST(test_create_attribute);
        CPPUNIT_TEST(test_get_number_of_attributes);
        CPPUNIT_TEST(test_get_attribute_by_name);
        CPPUNIT_TEST(test_get_attribute_by_index);
        CPPUNIT_TEST_SUITE_END();
    private:
        object_imp file;
        object_imp attribute;
        object_imp root;

        object_imp create_attribute(const object_imp &parent,
                                    const pni::core::string &name) const;
    public:
        void setUp();
        void tearDown();

        void test_has_attribute();
        void test_delete_attribute();
        void test_create_attribute();
        void test_get_number_of_attributes();
        void test_get_attribute_by_name();
        void test_get_attribute_by_index();


        
};

