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

#include <boost/current_function.hpp>
#include "float32_vector_parser_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(float32_vector_parser_test);


//-----------------------------------------------------------------------------
void float32_vector_parser_test::setUp() 
{ 
    ref=result_type{1.2,3e+3,-3.4,4.429,-5.34e-3};
}

//-----------------------------------------------------------------------------
void float32_vector_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void float32_vector_parser_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p;
    result_type result = p("1.2 3e+3 -3.4 4.429 -5.34e-3");

    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));

    result = p("  1.2  3e+3    -3.4  4.429   -5.34e-3   ");
    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

//-----------------------------------------------------------------------------
void float32_vector_parser_test::test_start_stop()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p('(',')');
    result_type result = p("( 1.2 3.e3 -3.4 4.429  -5.34e-3   )");
    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));

    result = p("(1.2 3e+3 -3.4 4.429 -5.34e-3)");
    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

//-----------------------------------------------------------------------------
void float32_vector_parser_test::test_delimiter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p(';');
    result_type result = p("1.2;3e3;-3.4;4.429;-5.34e-3");
    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
    
    result = p("  1.2; 3e+3 ;-3.4   ;  4.429; -5.34e-3  ");
    CPPUNIT_ASSERT(result.size()==5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

//-----------------------------------------------------------------------------
void float32_vector_parser_test::test_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    parser_type p('[',']',',');
    result_type result = p("[1.2,3.e+3,-3.4,4.429,-5.34e-3]");
    CPPUNIT_ASSERT(result.size() == 5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));

    result = p("[  1.2, 3e+3,  -3.4  , 4.429,  -5.34e-3  ]");
    CPPUNIT_ASSERT(result.size() == 5);
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));

}

