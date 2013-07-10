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
 *  Created on: Jun 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "is_field_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(is_field_test);

//-----------------------------------------------------------------------------
void is_field_test::setUp()
{
    file = h5::nxfile::create_file("groups.nx",true,0);
    group = file.create_group("group","NXentry");
    field = file.create_field<uint32>("data");
    attribute = group.attr("NX_class");
}

//-----------------------------------------------------------------------------
void is_field_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void is_field_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_types object = group;
    CPPUNIT_ASSERT(!is_field(object));
}

//-----------------------------------------------------------------------------
void is_field_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_types object = field;
    CPPUNIT_ASSERT(is_field(object)); 
}

//-----------------------------------------------------------------------------
void is_field_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_types object = attribute;
    CPPUNIT_ASSERT(!is_field(object));
   
}

