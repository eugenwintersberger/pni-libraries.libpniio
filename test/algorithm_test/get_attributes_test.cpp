//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aug 21, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>
#include <pni/io/exceptions.hpp>

#include "get_attributes_test.hpp"

using pni::io::object_error;
using pni::io::invalid_object_error;


CPPUNIT_TEST_SUITE_REGISTRATION(get_attributes_test);

//-----------------------------------------------------------------------------
void get_attributes_test::setUp()
{
    file = h5::nxfile::create_file("get_attributes_test.nx",true,0);
    root = file.root();
    field = root.create_field<uint32>("data");
    field.attributes.create<string>("units").write("mm");
    field.attributes.create<float32>("temperature").write(123.32);
    attr = field.attributes.create<bool_t>("controllerflag");
    attr.write(true);
}

//-----------------------------------------------------------------------------
void get_attributes_test::tearDown() 
{ 
    field.close();
    root.close();
    attr.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_attributes_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = root;
    vector_type attributes;

    CPPUNIT_ASSERT_NO_THROW(get_attributes(object,attributes));
    CPPUNIT_ASSERT(attributes.size()==6);

}

//-----------------------------------------------------------------------------
void get_attributes_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_type object = field;
    vector_type attributes;

    CPPUNIT_ASSERT_NO_THROW(get_attributes(object,attributes));
    CPPUNIT_ASSERT(attributes.size() == 3);
}

//-----------------------------------------------------------------------------
void get_attributes_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = attr;
    vector_type attributes;
    
    CPPUNIT_ASSERT_THROW(get_attributes(object,attributes),type_error);
}

//-----------------------------------------------------------------------------
void get_attributes_test::test_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject f = h5::nxfield();
    h5::nxobject g = h5::nxgroup();
    vector_type container;
    CPPUNIT_ASSERT_THROW(get_attributes(f,container),invalid_object_error);
    CPPUNIT_ASSERT_THROW(get_attributes(g,container),invalid_object_error);
}

