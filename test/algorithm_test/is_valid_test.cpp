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

#include "is_valid_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(is_valid_test);

//-----------------------------------------------------------------------------
void is_valid_test::setUp()
{
    file = h5::nxfile::create_file("is_valid_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
    attribute = group.attr("NX_class");
}

//-----------------------------------------------------------------------------
void is_valid_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//----------------------------------------------------------------------------
void is_valid_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(group));
    group.close();
    CPPUNIT_ASSERT(!is_valid(group));
}

//----------------------------------------------------------------------------
void is_valid_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(field));
    field.close();
    CPPUNIT_ASSERT(!is_valid(field));
}

//----------------------------------------------------------------------------
void is_valid_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(attribute));
    attribute.close();
    CPPUNIT_ASSERT(!is_valid(attribute));
}

//----------------------------------------------------------------------------
void is_valid_test::test_file()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(file));
    file.close();
    CPPUNIT_ASSERT(!is_valid(file));
}

//-----------------------------------------------------------------------------
void is_valid_test::test_nxobject_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    object_type object;
    CPPUNIT_ASSERT(!is_valid(object));
    object = group;
    CPPUNIT_ASSERT(is_valid(object));
}

//-----------------------------------------------------------------------------
void is_valid_test::test_nxobject_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object;
    CPPUNIT_ASSERT(!is_valid(object));
    object = field;
    CPPUNIT_ASSERT(is_valid(object)); 
}

//-----------------------------------------------------------------------------
void is_valid_test::test_nxobject_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object;
    CPPUNIT_ASSERT(!is_valid(object));
    object = attribute;
    CPPUNIT_ASSERT(is_valid(object));
   
}

