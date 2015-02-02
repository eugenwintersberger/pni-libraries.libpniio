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
//  Created on: Jan 30, 2015
//      Author: Eugen Wintersberger
//

#include "int8_vector_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(int8_vector_parser_test);


//-----------------------------------------------------------------------------
void int8_vector_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void int8_vector_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void int8_vector_parser_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p;
    result_type result = p("1 2 -3 4  -5");

    CPPUNIT_ASSERT(result.size()==5);
}

//-----------------------------------------------------------------------------
void int8_vector_parser_test::test_start_stop()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p('(',')');
    result_type result = p("( 1 2 -3 4  -5   )");
    CPPUNIT_ASSERT(result.size()==5);
}

//-----------------------------------------------------------------------------
void int8_vector_parser_test::test_delimiter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p(';');
    result_type result = p("1;2 ;-3; 4 ; -5");

    CPPUNIT_ASSERT(result.size()==5);
}

//-----------------------------------------------------------------------------
void int8_vector_parser_test::test_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    parser_type p('[',']',',');
    result_type result = p("[1,2 ,3, 4  ,  5]");
    CPPUNIT_ASSERT(result.size() == 5);
}

