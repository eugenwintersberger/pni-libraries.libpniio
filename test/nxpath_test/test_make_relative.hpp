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
//  Created on: Sep 11, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "../TestHelpers.hpp"

//!
//! \ingroup test_code
//! \brief test nxpath
//! 
//! Test the nxpath class
//!
class test_make_relative:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(test_make_relative);
    CPPUNIT_TEST(test_1);
    CPPUNIT_TEST(test_2);
    CPPUNIT_TEST(test_3);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
    
    void test_2();
    void test_1();
    void test_3();
};


