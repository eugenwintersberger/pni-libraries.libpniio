//
// Declaration of Nexus object template.
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
// ==========================================================================
//
//  Created on: Aug 4, 2011
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/nx/nx.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class nxgroup_access_test: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(nxgroup_access_test);
    CPPUNIT_TEST(test_operator_index);
    CPPUNIT_TEST(test_operator_name);
    CPPUNIT_TEST(test_at_index);
    CPPUNIT_TEST(test_at_name);
	CPPUNIT_TEST_SUITE_END();
private:
	string _fname;
    h5::nxfile _f;
    h5::nxgroup _root;
    h5::nxgroup _child;
public:
	void setUp();
	void tearDown();

    void test_operator_index();
    void test_operator_name();
    void test_at_index();
    void test_at_name();
};

