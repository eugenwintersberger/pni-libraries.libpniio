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
#include <pni/io/nx/algorithms/get_shape.hpp>
#include "get_shape_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_shape_test);

//-----------------------------------------------------------------------------
void get_shape_test::setUp()
{
    field_shape = shape_t{0,10,10};
    attr_shape  = shape_t{4,4};

    file = h5::nxfile::create_file("get_shape_test.nxs",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
}

//-----------------------------------------------------------------------------
void get_shape_test::tearDown() 
{ 
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_shape_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    h5::nxobject object = root;
    CPPUNIT_ASSERT_THROW(get_shape<shape_t>(object),type_error);
}

//-----------------------------------------------------------------------------
void get_shape_test::test_mdim_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxfield field = group.create_field<float32>("tmp",field_shape);
    h5::nxobject obj = field;

    check_shape(field_shape,get_shape<shape_t>(field));
    check_shape(field_shape,get_shape<shape_t>(obj));
}

//-----------------------------------------------------------------------------
void get_shape_test::test_scalar_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfield field = group.create_field<float32>("tmp");
    h5::nxobject obj = field;

    check_shape(shape_t{1},get_shape<shape_t>(field));
    check_shape(shape_t{1},get_shape<shape_t>(obj));
}

//-----------------------------------------------------------------------------
void get_shape_test::test_mdim_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxattribute attr = group.attributes.create<float32>("strian",
                           attr_shape);
    h5::nxobject object = attr;
    
    check_shape(attr_shape,get_shape<shape_t>(attr));
    check_shape(attr_shape,get_shape<shape_t>(object));
}

//-----------------------------------------------------------------------------
void get_shape_test::test_scalar_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxattribute attr = group.attributes.create<float32>("strian");
    h5::nxobject object = attr;
    
    check_shape(shape_t{},get_shape<shape_t>(attr));
    check_shape(shape_t{},get_shape<shape_t>(object));
}


