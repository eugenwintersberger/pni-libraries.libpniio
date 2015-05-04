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

#include "nxpath_equality_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_equality_test);


//----------------------------------------------------------------------------
void nxpath_equality_test::setUp() { }

//----------------------------------------------------------------------------
void nxpath_equality_test::tearDown() {}

//----------------------------------------------------------------------------
void nxpath_equality_test::test_equality()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(nxpath::from_string("test.nxs://") == 
                   nxpath::from_string("test.nxs://"));
                   
    CPPUNIT_ASSERT(nxpath::from_string("/:NXentry")==
                   nxpath::from_string("/:NXentry"));
                   
    CPPUNIT_ASSERT(nxpath::from_string("/:NXentry@NX_class") == 
                   nxpath::from_string("/:NXentry@NX_class"));
                   
    CPPUNIT_ASSERT(nxpath::from_string(":NXinstrument/:NXdetector/data")==
                   nxpath::from_string(":NXinstrument/:NXdetector/data"));
        
    CPPUNIT_ASSERT(nxpath::from_string(":NXdetector/data@units")==
                   nxpath::from_string(":NXdetector/data@units"));
}

//----------------------------------------------------------------------------
void nxpath_equality_test::test_inequality()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

     CPPUNIT_ASSERT(nxpath::from_string("test.nxs://") != 
                   nxpath::from_string("test2.nxs://"));
                   
    CPPUNIT_ASSERT(nxpath::from_string("/:NXentry")!=
                   nxpath::from_string(":NXentry"));
                       
                   
    CPPUNIT_ASSERT(nxpath::from_string(":NXinstrument/:NXdetector/data")!=
                   nxpath::from_string(":NXinstrument/:NXdetector/data@units"));
        
}
