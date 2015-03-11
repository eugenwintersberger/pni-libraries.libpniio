//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include "nxattribute_manage_test.hpp"

//------------------------------------------------------------------------------
void nxattribute_manage_test::setUp() 
{ 
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
}

//----------------------------------------------------------------------------
void nxattribute_manage_test::tearDown() 
{   
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
void nxattribute_manage_test::test_exists()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!root.attributes.exists("bla"));
    CPPUNIT_ASSERT_NO_THROW(root.attributes.create<string>("bla"));
    CPPUNIT_ASSERT(root.attributes.exists("bla"));
}

//----------------------------------------------------------------------------
void nxattribute_manage_test::test_remove()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_NO_THROW(root.attributes.create<string>("bla"));
    CPPUNIT_ASSERT(root.attributes.exists("bla"));
    CPPUNIT_ASSERT_NO_THROW(root.attributes.remove("bla"));
    CPPUNIT_ASSERT(!root.attributes.exists("bla"));
    CPPUNIT_ASSERT_THROW(root.attributes.remove("bla"),key_error);

}
