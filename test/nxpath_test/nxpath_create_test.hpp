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
//  Created on: Feb 26, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io::nx;

//!
//! \ingroup test_code
//! \brief test nxpath
//! 
//! Test the nxpath class
//!
class nxpath_create_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxpath_create_test);
    CPPUNIT_TEST(test_abs_no_file);
    CPPUNIT_TEST(test_abs_no_file_with_attribute);
    CPPUNIT_TEST(test_abs_with_file);
    CPPUNIT_TEST(test_abs_with_file_with_attribute);
    CPPUNIT_TEST(test_rel_no_attribute);
    CPPUNIT_TEST(test_rel_with_attribute);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
    
    void test_abs_no_file();
    void test_abs_with_file();
    void test_abs_no_file_with_attribute();
    void test_abs_with_file_with_attribute();

    void test_rel_no_attribute();
    void test_rel_with_attribute();
};


