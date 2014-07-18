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
#include <pni/io/exceptions.hpp>

#include "get_name_test.hpp"

using pni::io::invalid_object_error;
using pni::io::io_error;

CPPUNIT_TEST_SUITE_REGISTRATION(get_name_test);

//-----------------------------------------------------------------------------
void get_name_test::setUp()
{
    file = h5::nxfile::create_file("get_name_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
    attribute = group.attributes["NX_class"];
}

//-----------------------------------------------------------------------------
void get_name_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//----------------------------------------------------------------------------
void get_name_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_name(root)  == "/");
    CPPUNIT_ASSERT(get_name(group) == "group");
}

//----------------------------------------------------------------------------
void get_name_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_name(field)== "data");
}

//----------------------------------------------------------------------------
void get_name_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_name(attribute) == "NX_class");
}

//-----------------------------------------------------------------------------
void get_name_test::test_nxobject_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = group;
    CPPUNIT_ASSERT(get_name(object) == "group");
}

//-----------------------------------------------------------------------------
void get_name_test::test_nxobject_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = field;
    CPPUNIT_ASSERT(get_name(object)=="data");
}

//-----------------------------------------------------------------------------
void get_name_test::test_nxobject_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = attribute;
    CPPUNIT_ASSERT(get_name(object) == "NX_class");
   
}

//-----------------------------------------------------------------------------
void get_name_test::test_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = h5::nxgroup();
    CPPUNIT_ASSERT_THROW(get_name(object),invalid_object_error);
}

