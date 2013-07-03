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

#include "get_object_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_object_test);

//-----------------------------------------------------------------------------
void get_object_test::setUp()
{
    file = h5::nxfile::create_file("is_valid.nx",true,0);
    group = file.create_group("group","NXentry");
    h5::nxgroup tg = group.create_group("instrument","NXinstrument");
    tg.create_group("detector","NXdetector");
    tg.create_field<uint32>("data",shape_t{0,1024,1024});
    tg.create_group("source","NXsource");
    field = file.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void get_object_test::tearDown() 
{ 
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_object_test::test_absolute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_types root = h5::nxgroup(file["/"]);
    nxpath p = path_from_string("/group/instrument/detector");

    CPPUNIT_ASSERT(is_valid(get_object(root,p)));
    CPPUNIT_ASSERT(is_group(get_object(root,p)));
    CPPUNIT_ASSERT(get_name(get_object(root,p))=="detector");


    CPPUNIT_ASSERT(is_valid(get_object(root,p)));
    CPPUNIT_ASSERT(is_group(get_object(root,p)));
    CPPUNIT_ASSERT(get_name(get_object(root,p))=="detector");

    p = path_from_string(":NXentry/instrument/:NXdetector");
    CPPUNIT_ASSERT(is_valid(get_object(root,p)));
    CPPUNIT_ASSERT(is_group(get_object(root,p)));
    CPPUNIT_ASSERT(get_name(get_object(root,p))=="detector");
}

//-----------------------------------------------------------------------------
void get_object_test::test_relative()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_types root = h5::nxgroup(file["/"]);
    nxpath p = path_from_string("../instrument/detector");
    CPPUNIT_ASSERT(!p.is_absolute());

    object_types ig = get_object(root,path_from_string("/group/instrument"));
    CPPUNIT_ASSERT(get_name(ig) == "instrument");
    object_types d  = get_object(ig,p);
    CPPUNIT_ASSERT(get_name(d) == "detector");



}

