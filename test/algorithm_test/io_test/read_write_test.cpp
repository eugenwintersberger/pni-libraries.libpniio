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
//  Created on: Sep 16, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "read_write_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(read_write_test);

//-----------------------------------------------------------------------------
void read_write_test::setUp()
{
    field_shape = shape_t{2,3,5};
    attr_shape  = shape_t{2,3};

    file = h5::nxfile::create_file("read_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data",field_shape);
    attribute = field.attributes.create<int16>("temp",attr_shape);

}

//-----------------------------------------------------------------------------
void read_write_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void read_write_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = root;
    CPPUNIT_ASSERT_THROW(write(object,farray_t()),type_error);

}

//-----------------------------------------------------------------------------
void read_write_test::test_field_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t::create(field_shape);
    field_rdata = farray_t::create(field_shape);
    std::iota(field_wdata.begin(),field_wdata.end(),0.0);
    std::fill(field_rdata.begin(),field_rdata.end(),0);
   
    CPPUNIT_ASSERT_NO_THROW(write(field,field_wdata));
    CPPUNIT_ASSERT_NO_THROW(read(field,field_rdata));

    for(size_t i=0;i<field_wdata.size();++i)
        CPPUNIT_ASSERT(field_wdata[i] == field_rdata[i]);

}

//-----------------------------------------------------------------------------
void read_write_test::test_field_object_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object = field;
    field_wdata = farray_t::create(field_shape);
    field_rdata = farray_t::create(field_shape);
    std::iota(field_wdata.begin(),field_wdata.end(),0.0);
    std::fill(field_rdata.begin(),field_rdata.end(),0);
   
    CPPUNIT_ASSERT_NO_THROW(write(object,field_wdata));
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata));

    for(size_t i=0;i<field_wdata.size();++i)
        CPPUNIT_ASSERT(field_wdata[i] == field_rdata[i]);


}
//-----------------------------------------------------------------------------
void read_write_test::test_field_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_wdata = farray_t::create(shape_t{1,3,5});
    field_rdata = farray_t::create(shape_t{1,3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::fill(field_wdata.begin(),field_wdata.end(),i);
        CPPUNIT_ASSERT_NO_THROW(write(field,field_wdata,i,slice(0,3),slice(0,5)));
    }

    //read data back - first block
    CPPUNIT_ASSERT_NO_THROW(read(field,field_rdata,0,slice(0,3),slice(0,5)));
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 0; }));

    //read back data - second block
    CPPUNIT_ASSERT_NO_THROW(read(field,field_rdata,1,slice(0,3),slice(0,5)));
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 1; }));

}

//-----------------------------------------------------------------------------
void read_write_test::test_field_object_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object = field;
    field_wdata = farray_t::create(shape_t{1,3,5});
    field_rdata = farray_t::create(shape_t{1,3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::fill(field_wdata.begin(),field_wdata.end(),i);
        CPPUNIT_ASSERT_NO_THROW(write(object,field_wdata,i,slice(0,3),slice(0,5)));
    }

    //read data back - first block
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata,0,slice(0,3),slice(0,5)));
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 0; }));

    //read back data - second block
    CPPUNIT_ASSERT_NO_THROW(read(object,field_rdata,1,slice(0,3),slice(0,5)));
    CPPUNIT_ASSERT(std::all_of(field_rdata.begin(),field_rdata.end(),
                   [](uint32 i){ return i == 1; }));

}
//-----------------------------------------------------------------------------
void read_write_test::test_attribute_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_type object = attribute;

    attr_wdata = aarray_t::create(shape_t{2,3});
    attr_rdata = aarray_t::create(shape_t{2,3});

    for(size_t i=0;i<attr_wdata.size();++i) attr_wdata[i] = i;
    std::fill(attr_rdata.begin(),attr_rdata.end(),0);

    CPPUNIT_ASSERT_NO_THROW(write(object,attr_wdata));
    CPPUNIT_ASSERT_NO_THROW(read(object,attr_rdata));

    attribute.read(attr_rdata);
    for(size_t i=0;i<attr_wdata.size();++i)
        CPPUNIT_ASSERT(attr_wdata[i] == attr_rdata[i]);

    CPPUNIT_ASSERT_THROW(write(object,attr_wdata,0,1),type_error);
    
}

//-----------------------------------------------------------------------------
void read_write_test::test_attribute_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object = field.attributes.create<string>("test_string");;

    CPPUNIT_ASSERT_NO_THROW(write(object,"hello world"));
    string buffer;
    CPPUNIT_ASSERT_NO_THROW(read(object,buffer));
    CPPUNIT_ASSERT(buffer == "hello world");
}
