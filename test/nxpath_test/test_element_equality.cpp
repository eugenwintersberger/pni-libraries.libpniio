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
//  Created on: May 4, 2015
//      Author: Eugen Wintersberger
//

#include "test_element_equality.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_element_equality);


//----------------------------------------------------------------------------
void test_element_equality::setUp() { }

//----------------------------------------------------------------------------
void test_element_equality::tearDown() {}

//----------------------------------------------------------------------------
void test_element_equality::test_equality()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(element_type("entry","NXentry") == 
                   element_type("entry","NXentry"));

    CPPUNIT_ASSERT(element_type("","NXentry") == 
                   element_type("","NXentry"));
    
    CPPUNIT_ASSERT(element_type("entry","") == 
                   element_type("entry",""));
    
}

//----------------------------------------------------------------------------
void test_element_equality::test_inequality()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(element_type("entry","NXentry") !=
                   element_type("scan_1","NXentry"));
    CPPUNIT_ASSERT(element_type("entry","NXinstrument") !=
                   element_type("entry","NXentry"));
                   
    CPPUNIT_ASSERT(element_type("","NXentry")!=
                   element_type("entry","NXentry"));
    CPPUNIT_ASSERT(element_type("entry","NXentry")!=
                   element_type("entry",""));

    CPPUNIT_ASSERT(element_type("entry","NXentry") != 
                   element_type("","NXentry"));
    CPPUNIT_ASSERT(element_type("","NXentry") != 
                   element_type("entry","NXentry"));
                   
    CPPUNIT_ASSERT(element_type("","NXentry") != 
                   element_type("","NXinstrument"));
    CPPUNIT_ASSERT(element_type("entry","") !=
                   element_type("scan1",""));
   
}


