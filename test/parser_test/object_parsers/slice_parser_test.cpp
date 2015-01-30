//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: May 06, 2013
//      Author: Eugen Wintersberger
//

#include "slice_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(slice_parser_test);

//-----------------------------------------------------------------------------
void slice_parser_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void slice_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void slice_parser_test::test_full_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    string s1 = "1:10";
    string s2 = "10:100:2";
    string s3 = "5";
    slice s = p(s1);

    CPPUNIT_ASSERT(s.first() == 1);
    CPPUNIT_ASSERT(s.last()  == 10);
    CPPUNIT_ASSERT(s.stride() == 1);

    s = p(s2);
    
    CPPUNIT_ASSERT(s.first() == 10);
    CPPUNIT_ASSERT(s.last()  == 100);
    CPPUNIT_ASSERT(s.stride() == 2);
    
    s = p(s3);
    
    CPPUNIT_ASSERT(s.first() == 5);
    CPPUNIT_ASSERT(s.last()  == 6);
    CPPUNIT_ASSERT(s.stride() == 1);

}

//-----------------------------------------------------------------------------
void slice_parser_test::test_half_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    string s1 = ":100";
    string s2 = ":200:3";
    
    slice s = p(s1);

    CPPUNIT_ASSERT(s.first() == 0);
    CPPUNIT_ASSERT(s.last()  == 100);
    CPPUNIT_ASSERT(s.stride() == 1);

    s = p(s2);
    
    CPPUNIT_ASSERT(s.first() == 0);
    CPPUNIT_ASSERT(s.last()  == 200);
    CPPUNIT_ASSERT(s.stride() == 3);
}
