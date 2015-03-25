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
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/algorithms/create_attribute.hpp>

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

template<typename T>
class create_attribute_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(create_attribute_test<T>);
        CPPUNIT_TEST(test_field_scalar);
        CPPUNIT_TEST(test_field_multidim);
        CPPUNIT_TEST(test_group_scalar);
        CPPUNIT_TEST(test_group_multidim);
        CPPUNIT_TEST(test_attribute);
        CPPUNIT_TEST(test_errors);
        CPPUNIT_TEST_SUITE_END();

        typedef T attr_type;
        static const type_id_t attr_tid = type_id_map<attr_type>::type_id;

        h5::nxfile file;
        h5::nxgroup group,root;
        h5::nxfield field;
        h5::nxattribute attr;

        shape_t field_shape,cs_shape;
    
        void default_test(const h5::nxobject &a);
        
    public:
        void setUp();
        void tearDown();
       
        void test_field_scalar();
        void test_field_multidim();
        void test_group_scalar();
        void test_group_multidim();
        void test_attribute();
        void test_errors();
};

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::setUp()
{
    field_shape = shape_t{0,10,10};
    cs_shape  = shape_t{1,10,10};

    file = h5::nxfile::create_file("create_attribute_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = group.create_field<int32>("test");
    attr  = field.attributes.create<float32>("temperature");
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::tearDown() 
{ 
    attr.close();
    field.close();
    group.close();
    root.close();
    file.close();
}
//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::default_test(const h5::nxobject &a)
{
    CPPUNIT_ASSERT(is_valid(a));
    CPPUNIT_ASSERT(is_attribute(a));
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_group_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject root_group = root;
    
    h5::nxobject f;
    CPPUNIT_ASSERT_NO_THROW(f=create_attribute<attr_type>(root_group,"test1"));
    CPPUNIT_ASSERT(is_valid(f));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f) == "test1");
    CPPUNIT_ASSERT(get_rank(f) == 0);
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
    CPPUNIT_ASSERT(get_size(f) == 1);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s.size()    == 0);

    //by default overwrite is false - this should throw
    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(root_group,"test1"),
                         object_error);
    //if we wet overwrite to true - we can create a new attribute
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute<attr_type>(root_group,"test1",true));
    CPPUNIT_ASSERT(get_type(f)==attr_tid);

    CPPUNIT_ASSERT_NO_THROW(f = create_attribute(root_group,attr_tid,"test1",true));
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_group_multidim()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject root_group = root;
    shape_t shape{4,3};
    h5::nxobject f;
    CPPUNIT_ASSERT(is_valid(f=create_attribute<attr_type>(root_group,"test2",shape)));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==2);
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 4);
    CPPUNIT_ASSERT(s[1] == 3);
    
    //by default overwrite is false - this should throw
    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(root_group,"test2",shape),object_error);
    //if we wet overwrite to true - we can create a new attribute
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute<attr_type>(root_group,"test2",shape,true));
    CPPUNIT_ASSERT(get_type(f)==attr_tid);
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute(root_group,type_id_t::INT16,"test2",true));
    CPPUNIT_ASSERT(get_type(f) == type_id_t::INT16);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_field_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject parent = field;
    
    h5::nxobject f;
    CPPUNIT_ASSERT_NO_THROW(f=create_attribute<attr_type>(parent,"test1"));
    CPPUNIT_ASSERT(is_valid(f));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f) == "test1");
    CPPUNIT_ASSERT(get_rank(f) == 0);
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
    CPPUNIT_ASSERT(get_size(f) == 1);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s.size()    == 0);

    //by default overwrite is false - this should throw
    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(parent,"test1"),
                         object_error);
    //if we wet overwrite to true - we can create a new attribute
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute<attr_type>(parent,"test1",true));
    CPPUNIT_ASSERT(get_type(f)==attr_tid);

    CPPUNIT_ASSERT_NO_THROW(f = create_attribute(parent,attr_tid,"test1",true));
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_field_multidim()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject parent = field;

    shape_t shape{4,3};
    h5::nxobject f;
    CPPUNIT_ASSERT(is_valid(f=create_attribute<attr_type>(parent,"test2",shape)));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==2);
    CPPUNIT_ASSERT(get_type(f) == attr_tid);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 4);
    CPPUNIT_ASSERT(s[1] == 3);
    
    //by default overwrite is false - this should throw
    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(parent,"test2",shape),object_error);
    //if we wet overwrite to true - we can create a new attribute
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute<attr_type>(parent,"test2",shape,true));
    CPPUNIT_ASSERT(get_type(f)==attr_tid);
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute(parent,type_id_t::INT16,"test2",true));
    CPPUNIT_ASSERT(get_type(f) == type_id_t::INT16);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = group.attributes["NX_class"];
    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(object,"g1"),type_error);
}

//----------------------------------------------------------------------------
template<typename T>
void create_attribute_test<T>::test_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object;

    CPPUNIT_ASSERT_THROW(create_attribute<attr_type>(object,"test"),
                         invalid_object_error);
}

