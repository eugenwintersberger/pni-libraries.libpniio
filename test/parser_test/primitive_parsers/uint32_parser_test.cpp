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
//  Created on: Jan 23, 2015
//      Author: Eugen Wintersberger
//

#include "uint32_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(uint32_parser_test);

//-----------------------------------------------------------------------------
void uint32_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void uint32_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void uint32_parser_test::test_regular_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(p.parse("12") == 12);
    CPPUNIT_ASSERT(p.parse("0")  == 0);
    CPPUNIT_ASSERT(p.parse("04") == 4);
}

//-----------------------------------------------------------------------------
void uint32_parser_test::test_invalid_input()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT_THROW(p.parse("x10"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1x0"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("10x"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("-10"),parser_error);
}

