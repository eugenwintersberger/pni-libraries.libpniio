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
//  Created on: Feb 4, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <pni/io/parsers.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::core;
using namespace pni::io;

class float32_vector_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(float32_vector_parser_test);
    CPPUNIT_TEST(test_default);
    CPPUNIT_TEST(test_start_stop);
    CPPUNIT_TEST(test_delimiter);
    CPPUNIT_TEST(test_full);
	CPPUNIT_TEST_SUITE_END();

    typedef std::vector<float32> result_type;
    typedef parser<result_type> parser_type;

    result_type ref;

public:
	void setUp();
	void tearDown();
    void test_default();
    void test_start_stop();
    void test_delimiter();
    void test_full();
};




