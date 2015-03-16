//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_path_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_path_test);

//-----------------------------------------------------------------------------
void get_path_test::setUp()
{
    file = h5::nxfile::create_file("get_path_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = group.create_field<uint32>("data");
    attribute = group.attributes["NX_class"];
}

//-----------------------------------------------------------------------------
void get_path_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//----------------------------------------------------------------------------
void get_path_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT(get_path(group) == "/group:NXentry");
    CPPUNIT_ASSERT(get_path(root) == "/");
}

//----------------------------------------------------------------------------
void get_path_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_path(field)== "/group:NXentry/data");
}

//----------------------------------------------------------------------------
void get_path_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_path(attribute) == "/group:NXentry@NX_class");
}

//-----------------------------------------------------------------------------
void get_path_test::test_nxobject_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = group;
    CPPUNIT_ASSERT(get_path(object) == "/group:NXentry");
}

//-----------------------------------------------------------------------------
void get_path_test::test_nxobject_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = field;
    CPPUNIT_ASSERT(get_path(object)=="/group:NXentry/data");
}

//-----------------------------------------------------------------------------
void get_path_test::test_nxobject_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = attribute;
    CPPUNIT_ASSERT(get_path(object) == "/group:NXentry@NX_class");
    attribute = root.attributes["NX_class"];
    CPPUNIT_ASSERT(get_path(attribute)=="/@NX_class");
   
}

