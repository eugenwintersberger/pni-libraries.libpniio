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
//  Created on: Feb 2, 2015
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include "string_vector_parser_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(string_vector_parser_test);


//-----------------------------------------------------------------------------
void string_vector_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void string_vector_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void string_vector_parser_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p;
    result_type result = p("hello this  bla    test  word");
    CPPUNIT_ASSERT(result.size()==5);
}

//-----------------------------------------------------------------------------
void string_vector_parser_test::test_start_stop()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p('(',')');
    result_type result = p("( true false   false true  true )");
    CPPUNIT_ASSERT(result.size()==5);

    result_type ref{"true","false","false","true","true"};
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

//-----------------------------------------------------------------------------
void string_vector_parser_test::test_delimiter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    parser_type p(';');
    result_type result = p(" true;false ;true; true ; false   ");
    CPPUNIT_ASSERT(result.size()==5);

    result_type ref{"true","false","true","true","false"};
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

//-----------------------------------------------------------------------------
void string_vector_parser_test::test_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    parser_type p('[',']',',');
    result_type result = p("[ hello world , this  ,is some, stupid  ,  text!  ]");
    CPPUNIT_ASSERT(result.size() == 5);

    for(auto s: result) std::cout<<s<<std::endl;

    result_type ref{"hello world","this","is some","stupid","text!"};
    CPPUNIT_ASSERT(std::equal(result.begin(),result.end(),ref.begin()));
}

