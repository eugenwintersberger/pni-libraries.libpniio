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
//  Created on: Jul 3, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_child_by_index_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_child_by_index_test);

//-----------------------------------------------------------------------------
void get_child_by_index_test::setUp()
{
    file = h5::nxfile::create_file("groups.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
    attribute = group.attr("NX_class");
}

//-----------------------------------------------------------------------------
void get_child_by_index_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_child_by_index_test::test_group_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = root;
    CPPUNIT_ASSERT(is_valid(get_child_by_index(object,size_t(0))));
}

//-----------------------------------------------------------------------------
void get_child_by_index_test::test_field_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = field;
    CPPUNIT_ASSERT_THROW(get_child_by_index(object,size_t(1)),nxfield_error); 
}

//-----------------------------------------------------------------------------
void get_child_by_index_test::test_attribute_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = attribute;
    CPPUNIT_ASSERT_THROW(get_child_by_index(object,1),nxattribute_error);
   
}
//-----------------------------------------------------------------------------
void get_child_by_index_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_valid(get_child_by_index(root,size_t(0))));
}

//-----------------------------------------------------------------------------
void get_child_by_index_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //would not compile - triggers static assertion
    //CPPUNIT_ASSERT_THROW(get_child_by_index(field,size_t(1)),nxfield_error); 
}

//-----------------------------------------------------------------------------
void get_child_by_index_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    //would not compile - triggers static assertion
    //CPPUNIT_ASSERT_THROW(get_child_by_index(attribute,1),nxattribute_error);
   
}

