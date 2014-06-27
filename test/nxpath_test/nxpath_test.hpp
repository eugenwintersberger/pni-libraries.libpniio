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
// ===========================================================================
//
//  Created on: Jun 25, 2014
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
class nxpath_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxpath_test);
    CPPUNIT_TEST(test_from_string_no_file);
    CPPUNIT_TEST(test_from_string_with_file);
    CPPUNIT_TEST(test_from_string_no_file_attr);
    CPPUNIT_TEST(test_from_string_with_file_attr);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

    void test_from_string_no_file();
    void test_from_string_with_file();
    void test_from_string_with_file_attr();
    void test_from_string_no_file_attr();



};


