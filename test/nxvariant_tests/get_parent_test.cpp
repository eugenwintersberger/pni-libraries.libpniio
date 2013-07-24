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

#include "get_parent_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_parent_test);

//-----------------------------------------------------------------------------
void get_parent_test::setUp()
{
    file = h5::nxfile::create_file("is_valid.nx",true,0);
    group = file.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = file.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void get_parent_test::tearDown() 
{ 
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_parent_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_types object = h5::nxgroup(group["instrument"]);
    CPPUNIT_ASSERT(is_valid(get_parent(object)));
    CPPUNIT_ASSERT(get_name(get_parent(object)) == "group");
    CPPUNIT_ASSERT(get_name(get_parent(object_types(group))) == "/");
    
    CPPUNIT_ASSERT(get_name(get_parent(get_parent(object_types(group))))=="/");
}

//-----------------------------------------------------------------------------
void get_parent_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_types object = field;

    CPPUNIT_ASSERT(get_name(get_parent(object)) == "/");

}

//-----------------------------------------------------------------------------
void get_parent_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_types a(group.attr("NX_class"));

    auto p = get_parent(a);
    CPPUNIT_ASSERT(is_group(p));
    CPPUNIT_ASSERT(is_valid(p));
    CPPUNIT_ASSERT(get_name(p)=="group");
}

