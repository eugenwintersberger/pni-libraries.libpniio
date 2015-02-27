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

#include "test_split_path.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_split_path);


//----------------------------------------------------------------------------
void test_split_path::setUp() 
{ 
    p = nxpath::from_string("test.nxs://:NXentry/:NXinstrument/detector@NX_class");
}

//----------------------------------------------------------------------------
void test_split_path::tearDown() {}

//----------------------------------------------------------------------------
void test_split_path::test_standard()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT_NO_THROW(split_path(p,3,p1,p2)); 
    CPPUNIT_ASSERT(nxpath::to_string(p1)=="test.nxs://:NXentry/:NXinstrument");
    CPPUNIT_ASSERT(nxpath::to_string(p2)=="detector@NX_class");
}

//----------------------------------------------------------------------------
void test_split_path::test_at_root()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT_NO_THROW(split_path(p,0,p1,p2)); 
    std::cout<<nxpath::to_string(p1)<<std::endl;
    std::cout<<nxpath::to_string(p2)<<std::endl;
    CPPUNIT_ASSERT(nxpath::to_string(p1)=="test.nxs");
    CPPUNIT_ASSERT(nxpath::to_string(p2)=="/:NXentry/:NXinstrument/detector@NX_class");
}

//----------------------------------------------------------------------------
void test_split_path::test_index_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT_THROW(split_path(p,10,p1,p2),index_error); 
}
