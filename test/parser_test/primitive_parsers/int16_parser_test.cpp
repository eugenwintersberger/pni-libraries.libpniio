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
//  Created on: Jan 21, 2015
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <pni/io/exceptions.hpp>
#include "int16_parser_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(int16_parser_test);

//-----------------------------------------------------------------------------
void int16_parser_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void int16_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void int16_parser_test::test_regular_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(p("12")==12);
    CPPUNIT_ASSERT(p("0") == 0);
    CPPUNIT_ASSERT(p("-100")==-100);
}

//-----------------------------------------------------------------------------
void int16_parser_test::test_invalid_input()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT_THROW(p("a10"),parser_error);
    CPPUNIT_ASSERT_THROW(p("-10b"),parser_error);
    CPPUNIT_ASSERT_THROW(p("10x0"),parser_error);
}

