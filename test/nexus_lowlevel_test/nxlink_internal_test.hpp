//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Mar 11, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/nx/nx.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class nxlink_internal_test: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(nxlink_internal_test);
    CPPUNIT_TEST(test_field_by_instance);
    CPPUNIT_TEST(test_field_by_string_absolute);
    CPPUNIT_TEST(test_field_by_string_relative);
    CPPUNIT_TEST(test_field_by_path);
    CPPUNIT_TEST(test_group_by_instance);
    CPPUNIT_TEST(test_group_by_string);
    CPPUNIT_TEST(test_group_by_path);
	CPPUNIT_TEST_SUITE_END();
private:
    h5::nxfile  target_file;
    h5::nxfield target_field;
    h5::nxgroup target_group,root_group;
    h5::nxgroup location;
public:
	void setUp();
	void tearDown();
    void test_field_by_instance();
    void test_field_by_string_absolute();
    void test_field_by_string_relative();
    void test_field_by_path();
    void test_group_by_instance();
    void test_group_by_string();
    void test_group_by_path();

};

