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
//  Created on: Feb 27, 2015
//      Author: Eugen Wintersberger
//

#include "test_is_absolute.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_is_absolute);


//----------------------------------------------------------------------------
void test_is_absolute::setUp() { }

//----------------------------------------------------------------------------
void test_is_absolute::tearDown() {}

//----------------------------------------------------------------------------
void test_is_absolute::test_yes()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(is_absolute(nxpath::from_string("test.nxs://")));
    CPPUNIT_ASSERT(is_absolute(nxpath::from_string("/:NXentry/")));
    CPPUNIT_ASSERT(is_absolute(nxpath::from_string("/")));
}

//----------------------------------------------------------------------------
void test_is_absolute::test_no()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(!is_absolute(nxpath::from_string("../")));
    CPPUNIT_ASSERT(!is_absolute(nxpath::from_string("./")));
    CPPUNIT_ASSERT(!is_absolute(nxpath::from_string(":NXinstrument")));
    CPPUNIT_ASSERT(!is_absolute(nxpath::from_string("instrument")));
    CPPUNIT_ASSERT(!is_absolute(nxpath::from_string("instrument:NXinstrument")));
}

