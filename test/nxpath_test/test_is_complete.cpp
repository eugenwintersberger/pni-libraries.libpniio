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
//  Created on: Feb 26, 2015
//      Author: Eugen Wintersberger
//

#include "test_is_complete.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_is_complete);


//----------------------------------------------------------------------------
void test_is_complete::setUp() { }

//----------------------------------------------------------------------------
void test_is_complete::tearDown() {}

//----------------------------------------------------------------------------
void test_is_complete::test_yes()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(is_complete(object_element("/","NXroot")));
}

//----------------------------------------------------------------------------
void test_is_complete::test_no()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(!is_complete(object_element("/","")));
    CPPUNIT_ASSERT(!is_complete(object_element("","NXroot")));
}

//----------------------------------------------------------------------------
void test_is_complete::test_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_THROW(is_complete(nxpath::element_type{"",""}),
                         value_error);
}
