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

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class nxgroup_misc_test: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(nxgroup_misc_test);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_name);
    CPPUNIT_TEST(test_filename);
    CPPUNIT_TEST(test_parent);
	CPPUNIT_TEST_SUITE_END();
private:
	string _fname;
    h5::nxfile _f;
    h5::nxgroup _root;
    h5::nxgroup _child;
    h5::nxgroup _child2;
    static const string _filename;
public:
	void setUp();
	void tearDown();

    void test_size();
    void test_name();
    void test_filename();
    void test_parent();
};

const string nxgroup_misc_test::_filename = "nxgroup_misc_test.nxs";
