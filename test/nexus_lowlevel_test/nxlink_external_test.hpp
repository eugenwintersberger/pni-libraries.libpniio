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
//  Created on: Mar 12, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/nx/nx.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class nxlink_external_test: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(nxlink_external_test);
    CPPUNIT_TEST(test_field_by_string);
    CPPUNIT_TEST(test_field_by_path);
    CPPUNIT_TEST(test_group_by_string);
    CPPUNIT_TEST(test_group_by_path);
    CPPUNIT_TEST(test_error);
	CPPUNIT_TEST_SUITE_END();
private:
    static const string link_file_name;
    static const string target_file_name;
    h5::nxfile  link_file;
    h5::nxfile  target_file;
    h5::nxgroup root_group;
    h5::nxgroup location;
public:
	void setUp();
	void tearDown();
    void test_field_by_string();
    void test_field_by_path();
    void test_group_by_string();
    void test_group_by_path();
    void test_error();

};

const string nxlink_external_test::link_file_name = 
"nxlink_external_test.link.nxs";
const string nxlink_external_test::target_file_name = 
"nxlink_external_test.target.nxs";

