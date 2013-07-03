/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 3, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_shape_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_shape_test);

//-----------------------------------------------------------------------------
void get_shape_test::setUp()
{
    field_shape = shape_t{0,10,10};
    attr_shape  = shape_t{4,4};

    file = h5::nxfile::create_file("is_valid.nx",true,0);
    group = file.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = file.create_field<uint32>("data",field_shape);
    field.attr<float32>("temp",attr_shape);
}

//-----------------------------------------------------------------------------
void get_shape_test::tearDown() 
{ 
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_shape_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_types object = h5::nxgroup(file["/"]);
    CPPUNIT_ASSERT_THROW(get_shape<shape_t>(object),nxgroup_error);

}

//-----------------------------------------------------------------------------
void get_shape_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_types object = field;

    shape_t shape;

    CPPUNIT_ASSERT_NO_THROW(shape = get_shape<shape_t>(object));
    for(auto oiter = field_shape.begin(), siter = shape.begin();
             oiter != field_shape.end();
        ++oiter,++siter)
        CPPUNIT_ASSERT(*oiter == *siter);

}

//-----------------------------------------------------------------------------
void get_shape_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t shape;
    object_types object = field.attr("temp");
    CPPUNIT_ASSERT_NO_THROW(shape = get_shape<shape_t>(object));

    for(auto oiter = attr_shape.begin(), siter = shape.begin();
             oiter != attr_shape.end();
        ++oiter,++siter)
        CPPUNIT_ASSERT(*oiter == *siter);
    
}

