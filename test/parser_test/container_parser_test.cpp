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
//  Created on: Jan 20, 2015
//      Author: Eugen Wintersberger
//

#include "container_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(container_parser_test);


//-----------------------------------------------------------------------------
void container_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void container_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void container_parser_test::test_simple()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = parse("[1,2,3,4,5]");
    std::cerr<<result.size()<<std::endl;
    CPPUNIT_ASSERT(result.size() == 5);
}

//-----------------------------------------------------------------------------
void container_parser_test::test_overflow()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    result_type result = parse("[500,20]");
    CPPUNIT_ASSERT(result.size()==2);
    std::cout<<result[0]<<std::endl;
    CPPUNIT_ASSERT(result[0]==2000);
    CPPUNIT_ASSERT(result[1]==20);
}
