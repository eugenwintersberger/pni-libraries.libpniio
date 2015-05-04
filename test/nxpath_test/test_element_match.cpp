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
//  Created on: Mar 26, 2015
//      Author: Eugen Wintersberger
//

#include "test_element_match.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_element_match);


//----------------------------------------------------------------------------
void test_element_match::setUp() { }

//----------------------------------------------------------------------------
void test_element_match::tearDown() {}

//----------------------------------------------------------------------------
void test_element_match::test_rule_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(match(element_type("entry","NXentry"),
                   element_type("entry","NXentry")));

    CPPUNIT_ASSERT(!match(element_type("scan_1","NXentry"),
                   element_type("entry","NXentry")));
    
    CPPUNIT_ASSERT(!match(element_type("entry","NXentry"),
                   element_type("entry","NXinstrument")));
    
}

//----------------------------------------------------------------------------
void test_element_match::test_rule_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(match(element_type("entry","NXentry"),
                   element_type("","NXentry")));
    CPPUNIT_ASSERT(match(element_type("","NXentry"),
                   element_type("entry","NXentry")));

    CPPUNIT_ASSERT(!match(element_type("","NXinstrument"),
                   element_type("control","NXmonitor")));
    CPPUNIT_ASSERT(!match(element_type("detector","NXdetector"),
                   element_type("","NXmonitor")));
}

//----------------------------------------------------------------------------
void test_element_match::test_rule_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(match(element_type("entry",""),
                         element_type("entry","")));
    CPPUNIT_ASSERT(match(element_type("","NXentry"),
                         element_type("","NXentry")));

    CPPUNIT_ASSERT(!match(element_type("entry",""),
                          element_type("scan","")));
    CPPUNIT_ASSERT(!match(element_type("","NXentry"),
                          element_type("","NXinstrument")));
}
