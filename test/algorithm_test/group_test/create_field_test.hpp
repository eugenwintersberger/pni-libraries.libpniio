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
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/create_field.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_rank.hpp>
#include <pni/io/nx/algorithms/get_size.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>

using namespace pni::core;
using namespace pni::io::nx;

template<typename T>
class create_field_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(create_field_test<T>);
        CPPUNIT_TEST(test_on_field_object);
        CPPUNIT_TEST(test_on_attribute_object);
        CPPUNIT_TEST(test_simple);
        CPPUNIT_TEST(test_shape);
        CPPUNIT_TEST(test_shape_filter);
        CPPUNIT_TEST(test_shape_chunk);
        CPPUNIT_TEST(test_shape_chunk_filter);
        CPPUNIT_TEST_SUITE_END();
        typedef T type;
        static const type_id_t tid = type_id_map<T>::type_id;

        h5::nxfile file;
        h5::nxgroup root;
        h5::nxdeflate_filter filter;

        shape_t shape,chunk;

    public:
        void setUp();
        void tearDown();
        
        void test_on_field_object();
        void test_on_attribute_object();
        void test_simple();
        void test_shape();
        void test_shape_filter();
        void test_shape_chunk();
        void test_shape_chunk_filter();

};

//-----------------------------------------------------------------------------
template<typename T> void create_field_test<T>::setUp()
{
    shape = shape_t{0,10,10};
    chunk = shape_t{1,10,10};
    filter = h5::nxdeflate_filter(2,true);

    file = h5::nxfile::create_file("create_field_test.nx",true);
    root = file.root();
}

//-----------------------------------------------------------------------------
template<typename T> void create_field_test<T>::tearDown() 
{ 
    root.close();
    file.close();
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_on_field_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject  object = root.create_field<type>("temperature");

    //test on compile time function templates
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g1"),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g1",shape),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,filter),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,chunk),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,chunk,filter),type_error);

    //test on runtime function
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g1"),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g1",shape),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,filter),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,chunk),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,chunk,filter),type_error);
}

//-----------------------------------------------------------------------------
template<typename T> 
void create_field_test<T>::test_on_attribute_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = root.attributes["NX_class"];
    
    //test on compile time function templates
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g1"),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g1",shape),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,filter),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,chunk),type_error);
    CPPUNIT_ASSERT_THROW(create_field<type>(object,"g2",shape,chunk,filter),type_error);

    //test on runtime function
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g1"),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g1",shape),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,filter),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,chunk),type_error);
    CPPUNIT_ASSERT_THROW(create_field(object,tid,"g2",shape,chunk,filter),type_error);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_simple()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject parent=root;

    auto field = create_field<type>(parent,"f1");
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_name(field) == "f1");
    CPPUNIT_ASSERT(get_type(field) == tid);

    field = create_field(parent,tid,"f2");
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_name(field) == "f2");
    CPPUNIT_ASSERT(get_type(field) == tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_shape()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject parent=root;
    shape_t s{10,30};

    auto field = create_field<type>(parent,"f1",s);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f1");
    CPPUNIT_ASSERT(get_type(field) == tid);

    field = create_field(parent,tid,"f2",s);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f2");
    CPPUNIT_ASSERT(get_type(field) == tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_shape_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject parent=root;
    shape_t s{10,30};
    h5::nxdeflate_filter filter(2,true);

    auto field = create_field<type>(parent,"f1",s,filter);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f1");
    CPPUNIT_ASSERT(get_type(field) == tid);

    field = create_field(parent,tid,"f2",s,filter);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f2");
    CPPUNIT_ASSERT(get_type(field) == tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_shape_chunk()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject parent=root;
    shape_t s{10,30}, c{1,30};
    h5::nxdeflate_filter filter(2,true);

    auto field = create_field<type>(parent,"f1",s,c);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f1");
    CPPUNIT_ASSERT(get_type(field) == tid);

    field = create_field(parent,tid,"f2",s,c);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f2");
    CPPUNIT_ASSERT(get_type(field) == tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void create_field_test<T>::test_shape_chunk_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject parent=root;
    shape_t s{10,30}, c{1,30};
    h5::nxdeflate_filter filter(2,true);

    auto field = create_field<type>(parent,"f1",s,c,filter);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f1");
    CPPUNIT_ASSERT(get_type(field) == tid);

    field = create_field(parent,tid,"f2",s,c,filter);
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field)==2);
    CPPUNIT_ASSERT(get_size(field) == 300);
    CPPUNIT_ASSERT(get_name(field) == "f2");
    CPPUNIT_ASSERT(get_type(field) == tid);
}
