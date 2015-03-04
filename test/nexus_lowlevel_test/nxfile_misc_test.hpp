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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

//testing class for ArrayShape objects

#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class nxfile_misc_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfile_misc_test);
	CPPUNIT_TEST(test_readonly);
    CPPUNIT_TEST(test_is_valid);
	CPPUNIT_TEST(test_root);
    CPPUNIT_TEST(test_close);
	CPPUNIT_TEST_SUITE_END();
    h5::nxfile f;
    static const string filename;
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_is_valid();
    void test_readonly();
    void test_root();
    void test_close();
};

const string nxfile_misc_test::filename = "nxfile_misc_test.nxs";

