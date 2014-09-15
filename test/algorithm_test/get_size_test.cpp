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
//  Created on: Jul 5, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_size_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_size_test);
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
void get_size_test::setUp()
{
    field_shape = shape_t{1,10,10};
    attr_shape  = shape_t{4,4};

    file = h5::nxfile::create_file("is_valid.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data",field_shape);
    attribute = field.attributes.create<float32>("temp",attr_shape);
}

//-----------------------------------------------------------------------------
void get_size_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_size_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = root;
    CPPUNIT_ASSERT(get_size(object)==2);
    CPPUNIT_ASSERT(get_size(root) == 2);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxgroup()),invalid_object_error);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxobject(h5::nxgroup())),
                         invalid_object_error);

}

//-----------------------------------------------------------------------------
void get_size_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_type object = field;

    CPPUNIT_ASSERT(get_size(object) == 100);
    CPPUNIT_ASSERT(get_size(field) == 100);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxfield()),invalid_object_error);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxobject(h5::nxfield())),
                         invalid_object_error);

}

//-----------------------------------------------------------------------------
void get_size_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t shape;
    object_type object = attribute;
    CPPUNIT_ASSERT(get_size(object) == 16);
    CPPUNIT_ASSERT(get_size(attribute) == 16);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxattribute()),invalid_object_error);
    CPPUNIT_ASSERT_THROW(get_size(h5::nxobject(h5::nxattribute())),
                         invalid_object_error);
    
}

