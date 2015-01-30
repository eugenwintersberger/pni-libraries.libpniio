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
//  Created on: Jan 22, 2015
//      Author: Eugen Wintersberger
//

#include "string_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(string_parser_test);

//-----------------------------------------------------------------------------
void string_parser_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void string_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void string_parser_test::test_regular_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(p("hello world") == "hello world");
    CPPUNIT_ASSERT(p(" this is a text") == " this is a text");
}




