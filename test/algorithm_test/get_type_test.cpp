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
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_type_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_type_test);

//-----------------------------------------------------------------------------
void get_type_test::setUp()
{
    field_shape = shape_t{0,10,10};
    attr_shape  = shape_t{4,4};

    file = h5::nxfile::create_file("is_valid.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data",field_shape);
    field.attributes.create<float32>("temp",attr_shape);
}

//-----------------------------------------------------------------------------
void get_type_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_type_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = root;
    CPPUNIT_ASSERT_THROW(get_type(object),nxgroup_error);

}

//-----------------------------------------------------------------------------
void get_type_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = field;
    CPPUNIT_ASSERT(is_valid(object));

    type_id_t value = get_type(object);
    std::cout<<value<<std::endl;
    CPPUNIT_ASSERT(get_type(object) == type_id_t::UINT32);

}

//-----------------------------------------------------------------------------
void get_type_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t shape;
    object_type object = field.attributes["temp"];
    CPPUNIT_ASSERT(get_type(object) == type_id_t::FLOAT32);
    
}

