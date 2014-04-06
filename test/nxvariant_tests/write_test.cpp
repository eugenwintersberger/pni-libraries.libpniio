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
 *  Created on: Jul 5, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

#include "write_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(write_test);

//-----------------------------------------------------------------------------
void write_test::setUp()
{
    field_shape = shape_t{2,3,5};
    attr_shape  = shape_t{2,3};

    file = h5::nxfile::create_file("write_test.nx",true,0);
    group = file.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = file.create_field<uint32>("data",field_shape);
    attribute = field.attr<int16>("temp",attr_shape);

}

//-----------------------------------------------------------------------------
void write_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void write_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_types object = h5::nxgroup(file["/"]);
    CPPUNIT_ASSERT_THROW(write(object,farray_t()),nxgroup_error);

}

//-----------------------------------------------------------------------------
void write_test::test_field_full()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t::create(field_shape);
    field_rdata = farray_t::create(field_shape);
    for(size_t i=0;i<field_wdata.size();++i) field_wdata[i] = i;
    std::fill(field_rdata.begin(),field_rdata.end(),0);

    object_types object = field;
    CPPUNIT_ASSERT_NO_THROW(write(object,field_wdata));

    field.read(field_rdata);
    for(size_t i=0;i<field_wdata.size();++i)
        CPPUNIT_ASSERT(field_wdata[i] == field_rdata[i]);


}

//-----------------------------------------------------------------------------
void write_test::test_field_partial()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t::create(shape_t{1,3,5});
    field_rdata = farray_t::create(shape_t{1,3,5});

    //write data
    object_types object = field;
    for(size_t i=0;i<2;++i)
    {
        std::fill(field_wdata.begin(),field_wdata.end(),i);
        CPPUNIT_ASSERT_NO_THROW(write(object,field_wdata,i,slice(0,3),slice(0,5)));
    }

    //read data back
    field(0,slice(0,3),slice(0,5)).read(field_rdata);
#ifdef NO_LAMBDA_FUNC
#ifdef NOFOREACH
    BOOST_FOREACH(auto value, field_rdata)
#else 
    for(auto value: field_rdata)
#endif
        CPPUNIT_ASSERT(value==0);
#else
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 0; }));
#endif
    field(1,slice(0,3),slice(0,5)).read(field_rdata);
#ifdef NO_LAMBDA_FUNC
#ifdef NOFOREACH
    BOOST_FOREACH(auto value,field_rdata)
#else
    for(auto value: field_rdata)
#endif
        CPPUNIT_ASSERT(value == 1);
#else
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 1; }));
#endif
}

//-----------------------------------------------------------------------------
void write_test::test_attribute_full()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_types object = attribute;

    attr_wdata = aarray_t::create(shape_t{2,3});
    attr_rdata = aarray_t::create(shape_t{2,3});

    for(size_t i=0;i<attr_wdata.size();++i) attr_wdata[i] = i;
    std::fill(attr_rdata.begin(),attr_rdata.end(),0);

    CPPUNIT_ASSERT_NO_THROW(write(object,attr_wdata));

    attribute.read(attr_rdata);
    for(size_t i=0;i<attr_wdata.size();++i)
        CPPUNIT_ASSERT(attr_wdata[i] == attr_rdata[i]);

    CPPUNIT_ASSERT_THROW(write(object,attr_wdata,0,1),nxattribute_error);
    
}

