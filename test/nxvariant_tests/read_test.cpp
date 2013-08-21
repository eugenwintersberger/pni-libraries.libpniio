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

#include "read_test.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif


CPPUNIT_TEST_SUITE_REGISTRATION(read_test);

//-----------------------------------------------------------------------------
void read_test::setUp()
{
    field_shape = shape_t{2,3,5};
    attr_shape  = shape_t{2,3};

    file = h5::nxfile::create_file("read_test.nx",true,0);
    group = file.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = file.create_field<uint32>("data",field_shape);
    attribute = field.attr<int16>("temp",attr_shape);

}

//-----------------------------------------------------------------------------
void read_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void read_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_types object = h5::nxgroup(file["/"]);
    CPPUNIT_ASSERT_THROW(write(object,farray_t()),nxgroup_error);

}

//-----------------------------------------------------------------------------
void read_test::test_field_full()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t(field_shape);
    field_rdata = farray_t(field_shape);
    for(size_t i=0;i<field_wdata.size();++i) field_wdata[i] = i;
    std::fill(field_rdata.begin(),field_rdata.end(),0);
    field.write(field_wdata);

    object_types object = field;
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata));

    for(size_t i=0;i<field_wdata.size();++i)
        CPPUNIT_ASSERT(field_wdata[i] == field_rdata[i]);


}

//-----------------------------------------------------------------------------
void read_test::test_field_partial()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t(shape_t{1,3,5});
    field_rdata = farray_t(shape_t{1,3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::fill(field_wdata.begin(),field_wdata.end(),i);
        field(i,slice(0,3),slice(0,5)).write(field_wdata);
    }

    //read data back
    object_types object = field;
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata,0,slice(0,3),slice(0,5)));
#ifdef NO_LAMBDA_FUNC
#ifdef NOFOREACH    
    BOOST_FOREACH(auto d, field_rdata)
#else
    for(auto d: field_rdata)
#endif
        CPPUNIT_ASSERT(d==0);
#else
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 0; }));
#endif
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata,1,slice(0,3),slice(0,5)));

#ifdef NO_LAMBDA_FUNC
#ifdef NOFOREACH
    BOOST_FOREACH(auto d, field_rdata)
#else
    for(auto d: field_rdata)
#endif
        CPPUNIT_ASSERT(d==0);
#else
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 1; }));
#endif




}

//-----------------------------------------------------------------------------
void read_test::test_attribute_full()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_types object = attribute;

    attr_wdata = aarray_t(shape_t{2,3});
    attr_rdata = aarray_t(shape_t{2,3});

    for(size_t i=0;i<attr_wdata.size();++i) attr_wdata[i] = i;
    std::fill(attr_rdata.begin(),attr_rdata.end(),0);

    CPPUNIT_ASSERT_NO_THROW(write(object,attr_wdata));
    CPPUNIT_ASSERT_NO_THROW(read(object,attr_rdata));

    attribute.read(attr_rdata);
    for(size_t i=0;i<attr_wdata.size();++i)
        CPPUNIT_ASSERT(attr_wdata[i] == attr_rdata[i]);

    CPPUNIT_ASSERT_THROW(write(object,attr_wdata,0,1),nxattribute_error);
    
}

//-----------------------------------------------------------------------------
void read_test::test_attribute_string()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_types object = field.attr<string>("test_string");;

    CPPUNIT_ASSERT_NO_THROW(write(object,"hello world"));
    string buffer;
    CPPUNIT_ASSERT_NO_THROW(read(object,buffer));
    CPPUNIT_ASSERT(buffer == "hello world");
}
