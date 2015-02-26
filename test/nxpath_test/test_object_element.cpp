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

#include "test_object_element.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_object_element);


//----------------------------------------------------------------------------
void test_object_element::setUp() { }

//----------------------------------------------------------------------------
void test_object_element::tearDown() {}

//----------------------------------------------------------------------------
void test_object_element::test_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath::element_type e = object_element("detector","NXdetector");
    CPPUNIT_ASSERT(e.first == "detector");
    CPPUNIT_ASSERT(e.second == "NXdetector");
}

//----------------------------------------------------------------------------
void test_object_element::test_name_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath::element_type e = object_element("detector","");
    CPPUNIT_ASSERT(e.first=="detector");
    CPPUNIT_ASSERT(e.second.empty());
}

//----------------------------------------------------------------------------
void test_object_element::test_type_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath::element_type e = object_element("","NXdetector");
    CPPUNIT_ASSERT(e.first.empty());
    CPPUNIT_ASSERT(e.second == "NXdetector");
}

//----------------------------------------------------------------------------
void test_object_element::test_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(object_element("",""),value_error);

}
