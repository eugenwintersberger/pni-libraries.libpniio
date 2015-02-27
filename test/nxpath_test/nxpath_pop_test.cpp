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

#include "nxpath_pop_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_pop_test);


//----------------------------------------------------------------------------
void nxpath_pop_test::setUp() 
{ 
    p = nxpath::from_string(":NXentry/:NXinstrument/:NXdetector");
}

//----------------------------------------------------------------------------
void nxpath_pop_test::tearDown() {}

//----------------------------------------------------------------------------
void nxpath_pop_test::test_front()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    nxpath::element_type e = p.front();
    p.pop_front();
    CPPUNIT_ASSERT(p.size() == 2);
    CPPUNIT_ASSERT(nxpath::to_string(p)==":NXinstrument/:NXdetector");
}

//----------------------------------------------------------------------------
void nxpath_pop_test::test_back()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath::element_type e = p.back();
    p.pop_back();
    CPPUNIT_ASSERT(p.size() == 2);
    CPPUNIT_ASSERT(nxpath::to_string(p)==":NXentry/:NXinstrument");
}

//----------------------------------------------------------------------------
void nxpath_pop_test::test_front_back()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    p.pop_front();
    p.pop_back();
    CPPUNIT_ASSERT(nxpath::to_string(p)==":NXinstrument");
}

