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
//  Created on: Mar 11, 2015
//      Author: Eugen Wintersberger
//

#include "test_is_empty.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_is_empty);


//----------------------------------------------------------------------------
void test_is_empty::setUp() { }

//----------------------------------------------------------------------------
void test_is_empty::tearDown() {}

//----------------------------------------------------------------------------
void test_is_empty::test_yes()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    nxpath p;
    CPPUNIT_ASSERT(is_empty(p));
}

//----------------------------------------------------------------------------
void test_is_empty::test_no()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(!is_empty(nxpath::from_string("test.nxs://")));
    CPPUNIT_ASSERT(!is_empty(nxpath::from_string("/")));
}

