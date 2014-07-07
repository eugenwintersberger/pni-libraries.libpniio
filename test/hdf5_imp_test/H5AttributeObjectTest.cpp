//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Aug 15, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "H5AttributeObjectTest.hpp"

#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxexceptions.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(H5AttributeObjectTest);

using pni::io::invalid_object_error;
using pni::io::object_error;

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::setUp()
{
    //open the HDF5 file 
    file = H5Fcreate("H5AttributeObjectTest.h5",H5F_ACC_TRUNC,
                     H5P_DEFAULT,H5P_DEFAULT);
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::tearDown()
{
    //close the HDF5 file
    H5Fclose(file);
}

//-----------------------------------------------------------------------------
hid_t H5AttributeObjectTest::create_group(hid_t pid,const string &name) const
{
    return H5Gcreate2(pid,name.c_str(),H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::local_function(hid_t id)
{
    H5AttributeObject o(std::move(H5TestObject(id)));
    CPPUNIT_ASSERT(o.is_valid());
    //now the object will be destroyed 
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_creation()
{
    PRINT_TEST_FUNCTION_SIG;

    //default constructor
    H5AttributeObject o;
    CPPUNIT_ASSERT(!o.is_valid());
    CPPUNIT_ASSERT_THROW(o.object_type(),invalid_object_error);
    //try to construct an instance from an invalid HDF5 ID.
    CPPUNIT_ASSERT_THROW(H5TestObject(-1),object_error);
  
    //test constructor from new object
    H5AttributeObject test(H5TestObject(create_group(file,"group")));

    //check the object type
    CPPUNIT_ASSERT(test.object_type() == H5ObjectType::GROUP);
    CPPUNIT_ASSERT(test.is_valid());
    CPPUNIT_ASSERT(test.path() == "/group");
    CPPUNIT_ASSERT(test.name() == "group");
    CPPUNIT_ASSERT(test.base() == "/");
    CPPUNIT_ASSERT_NO_THROW(test.close());
    CPPUNIT_ASSERT(!test.is_valid());

    //test copy constructor
    H5AttributeObject t1(H5TestObject(create_group(file,"group2")));

    H5AttributeObject t2(t1);
    CPPUNIT_ASSERT((t2.is_valid())&&(t1.is_valid()));
    CPPUNIT_ASSERT_NO_THROW(t1.close());
    CPPUNIT_ASSERT(!t1.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    
    //test move construction
    H5AttributeObject t3(std::move(t2));
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t3.is_valid());
    CPPUNIT_ASSERT(t3.object_type() == H5ObjectType::GROUP);
    t3.close();
    CPPUNIT_ASSERT(!t3.is_valid());

}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_assignment()
{
    PRINT_TEST_FUNCTION_SIG;

    H5AttributeObject o1(H5TestObject(create_group(file,"group")));

    CPPUNIT_ASSERT(o1.is_valid());
    H5AttributeObject o2;
    o2= o1;
    CPPUNIT_ASSERT(o1.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());


    H5AttributeObject o3;
    o3= std::move(o1);
    CPPUNIT_ASSERT(!o1.is_valid());
    CPPUNIT_ASSERT(o3.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_destruction()
{
    PRINT_TEST_FUNCTION_SIG;

    hid_t id = create_group(file,"group");
    //here the H5Object takes ownership over the id
    local_function(id);
    CPPUNIT_ASSERT(!(H5Iis_valid(id)>0));
}


//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_comparison()
{
    PRINT_TEST_FUNCTION_SIG;

    H5AttributeObject o1(H5TestObject(create_group(file,"group")));
    H5AttributeObject o2(H5TestObject(create_group(file,"group2")));
    H5AttributeObject o3(H5TestObject(H5Gopen2(file,"group",H5P_DEFAULT)));
   
    CPPUNIT_ASSERT(o1!=o2);
    CPPUNIT_ASSERT(o1==o3);
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_inquery()
{
    PRINT_TEST_FUNCTION_SIG;

    H5AttributeObject o1(H5TestObject(create_group(file,"group")));

    o1.attr<float32>("test1");
    o1.attr<uint8>("test2");

    CPPUNIT_ASSERT(o1.filename() == "H5AttributeObjectTest.h5");

    CPPUNIT_ASSERT(o1.nattr() == 2);
    //check for existing attributes
    CPPUNIT_ASSERT(o1.has_attr("test1"));
    CPPUNIT_ASSERT(!o1.has_attr("bla"));
    
    CPPUNIT_ASSERT_THROW(o1.attr("bla"),pni::io::nx::nxattribute_error);
    CPPUNIT_ASSERT_NO_THROW(o1.attr(0));
    CPPUNIT_ASSERT_NO_THROW(o1.attr(1));
    CPPUNIT_ASSERT_THROW(o1.attr(2),index_error);
    CPPUNIT_ASSERT_THROW(o1.attr(100),index_error);

    //try to create a new one without overwrite
    CPPUNIT_ASSERT_THROW(o1.attr<string>("test1"),pni::io::nx::nxattribute_error);
    CPPUNIT_ASSERT_NO_THROW(o1.attr<string>("test1",true));

    CPPUNIT_ASSERT_NO_THROW(o1.del_attr("test1"));
    CPPUNIT_ASSERT_NO_THROW(o1.attr<string>("test1"));

}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_attribute_open()
{
    PRINT_TEST_FUNCTION_SIG;

    H5AttributeObject o(H5TestObject(create_group(file,"group")));

    CPPUNIT_ASSERT_NO_THROW(o.attr<float32>("temp"));
    CPPUNIT_ASSERT(o.has_attr("temp"));
    H5Attribute a;
    CPPUNIT_ASSERT_NO_THROW(a = o.attr("temp"));
    CPPUNIT_ASSERT(o.attr("temp").is_valid());
    CPPUNIT_ASSERT(a.is_valid());

    CPPUNIT_ASSERT_THROW(o.attr("bla"),pni::io::nx::nxattribute_error);
}

