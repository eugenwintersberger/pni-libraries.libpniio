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

#include <pni/io/nx/algorithms/grow.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "grow_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(grow_test);

//-----------------------------------------------------------------------------
void grow_test::setUp()
{
    field_shape = shape_t{1,10,10};
    attr_shape  = shape_t{4,4};

    file = h5::nxfile::create_file("grow_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data",field_shape);
    attribute = field.attributes.create<float32>("temp",attr_shape);
}

//-----------------------------------------------------------------------------
void grow_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void grow_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    h5::nxobject object = root;
    CPPUNIT_ASSERT_THROW(grow(object),type_error);

}

//-----------------------------------------------------------------------------
void grow_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = field;

    auto s = get_shape<shape_t>(object);
    CPPUNIT_ASSERT(s[0] == 1);
    CPPUNIT_ASSERT_NO_THROW(grow(object));
    s = get_shape<shape_t>(object);
    CPPUNIT_ASSERT(s[0] == 2);
    CPPUNIT_ASSERT_NO_THROW(grow(object,1,10));
    s = get_shape<shape_t>(object);
    CPPUNIT_ASSERT(s[1] ==20);

}

//-----------------------------------------------------------------------------
void grow_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = attribute;
    CPPUNIT_ASSERT_THROW(grow(object),type_error);
    
}

