//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Sep 13, 2012
//      Author: Eugen Wintersberger
//


#pragma once
#include "../common.hpp"
#include "../data.hpp"
#include "../uniform_distribution.hpp"
#include <pni/core/arrays.hpp>
#include <pni/io/exceptions.hpp>
using pni::io::invalid_object_error;

template<typename T> using sarray = static_array<T,10,20>;

//!
//! \ingroup test_classes
//! \brief Attribute facilities test
//! 
//! Testing attribute facilities of different Nexus objects
//! \tparam APTYPE attribute parent type (group, field, or file)
//!
template<typename APTYPE> class NXAttributeTest: public CppUnit::TestFixture  
{
        CPPUNIT_TEST_SUITE(NXAttributeTest<APTYPE>);
        //general testsa
        CPPUNIT_TEST(test_creation);

        //testing simple scalar attributes
        CPPUNIT_TEST(test_scalar_attribute<uint8>);
        CPPUNIT_TEST(test_scalar_attribute<int8>);
        CPPUNIT_TEST(test_scalar_attribute<uint16>);
        CPPUNIT_TEST(test_scalar_attribute<int16>);
        CPPUNIT_TEST(test_scalar_attribute<uint32>);
        CPPUNIT_TEST(test_scalar_attribute<int32>);
        CPPUNIT_TEST(test_scalar_attribute<uint64>);
        CPPUNIT_TEST(test_scalar_attribute<int64>);
        CPPUNIT_TEST(test_scalar_attribute<float32>);
        CPPUNIT_TEST(test_scalar_attribute<float64>);
        CPPUNIT_TEST(test_scalar_attribute<float128>);
        CPPUNIT_TEST(test_scalar_attribute<complex32>);
        CPPUNIT_TEST(test_scalar_attribute<complex64>);
        CPPUNIT_TEST(test_scalar_attribute<complex128>);

        CPPUNIT_TEST(test_scalar_attribute<string>);
        CPPUNIT_TEST(test_scalar_attribute<bool_t>);
        CPPUNIT_TEST(test_scalar_attribute<binary>);

        //testing array io
        CPPUNIT_TEST(test_array_attribute<dynamic_array<uint8> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<int8> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<uint16> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<int16> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<uint32> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<int32> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<uint64> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<int64> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<float32> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<float64> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<float128> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<complex32> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<complex64> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<complex128> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<bool_t> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<string> >);
        CPPUNIT_TEST(test_array_attribute<dynamic_array<binary> >);

        CPPUNIT_TEST(test_array_attribute<sarray<uint8> >);
        CPPUNIT_TEST(test_array_attribute<sarray<int8> >);
        CPPUNIT_TEST(test_array_attribute<sarray<uint16> >);
        CPPUNIT_TEST(test_array_attribute<sarray<int16> >);
        CPPUNIT_TEST(test_array_attribute<sarray<uint32> >);
        CPPUNIT_TEST(test_array_attribute<sarray<int32> >);
        CPPUNIT_TEST(test_array_attribute<sarray<uint64> >);
        CPPUNIT_TEST(test_array_attribute<sarray<int64> >);
        CPPUNIT_TEST(test_array_attribute<sarray<float32> >);
        CPPUNIT_TEST(test_array_attribute<sarray<float64> >);
        CPPUNIT_TEST(test_array_attribute<sarray<float128> >);
        CPPUNIT_TEST(test_array_attribute<sarray<complex32> >);
        CPPUNIT_TEST(test_array_attribute<sarray<complex64> >);
        CPPUNIT_TEST(test_array_attribute<sarray<complex128> >);
        CPPUNIT_TEST(test_array_attribute<sarray<bool_t> >);
        CPPUNIT_TEST(test_array_attribute<sarray<binary> >);
        CPPUNIT_TEST(test_array_attribute<sarray<string> >);

        CPPUNIT_TEST(test_partial_scalar<uint8>);
        CPPUNIT_TEST(test_partial_scalar<int8>);
        CPPUNIT_TEST(test_partial_scalar<uint16>);
        CPPUNIT_TEST(test_partial_scalar<int16>);
        CPPUNIT_TEST(test_partial_scalar<uint32>);
        CPPUNIT_TEST(test_partial_scalar<int32>);
        CPPUNIT_TEST(test_partial_scalar<uint64>);
        CPPUNIT_TEST(test_partial_scalar<int64>);

        CPPUNIT_TEST(test_partial_scalar<float32>);
        CPPUNIT_TEST(test_partial_scalar<float64>);
        CPPUNIT_TEST(test_partial_scalar<float128>);
        
        CPPUNIT_TEST(test_partial_scalar<complex32>);
        CPPUNIT_TEST(test_partial_scalar<complex64>);
        CPPUNIT_TEST(test_partial_scalar<complex128>);

        CPPUNIT_TEST(test_partial_scalar<bool_t>);
        CPPUNIT_TEST(test_partial_scalar<binary>);
        CPPUNIT_TEST(test_partial_scalar<string>);


        CPPUNIT_TEST(test_partial_array<uint8>);

        CPPUNIT_TEST(test_array);
        
        CPPUNIT_TEST_SUITE_END();
    private:
        nxfile _f;
        nxgroup _root;
        APTYPE _parent;
        shape_t _shape;
        size_t _size;

        //==========static functions to create parent objects==================
        static void create_parent(const nxfile &f,nxgroup &p);
        static void create_parent(const nxfile &f,nxfield &p);

        //==============static functions to create arrays======================
        template<typename ATYPE>
        static void create_array(const shape_t &s,ATYPE &a)
        {
            a = ATYPE::create(s);
        }


    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_array();
        template<typename T> void test_scalar_attribute();
        template<typename T> void test_partial_scalar();
        template<typename T> void test_partial_array();
        template<typename ATYPE> void test_array_attribute();
};


//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const nxfile &f,nxgroup &p)
{
    p = f.root().create_group("testgroup");
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const nxfile &f,nxfield &p)
{
    p = f.root().create_field<string>("hello");
    p.write("hello world");
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::setUp()
{
    //create the file where to store data
    _f = nxfile::create_file("NXAttributeTest.nxs",true,0);

    //create the attribute parrent
    create_parent(_f,_parent);

    //create shape
    _shape = shape_t({10,20});
    _size = 200;
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::tearDown()
{
    _parent.close();
    _f.close();
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::test_creation()
{
    //checking the default constructor
    nxattribute a;
    CPPUNIT_ASSERT(!a.is_valid());
    CPPUNIT_ASSERT_THROW(a.shape<shape_t>(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.type_id(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.size(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.rank(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.filename(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.name(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(a.parent(),invalid_object_error);

    //creating a scalar attribute
    nxattribute a1(_parent.attributes.template create<string>("attribute"));
    CPPUNIT_ASSERT(a1.filename() == "NXAttributeTest.nxs");
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.type_id() == type_id_t::STRING);
    CPPUNIT_ASSERT(a1.rank() == 1);
    CPPUNIT_ASSERT(a1.size() == 1);
    auto s = a1.shape<shape_t>();
    CPPUNIT_ASSERT(s.size() == 1);
    CPPUNIT_ASSERT(a1.name() == "attribute");

    APTYPE p;
    CPPUNIT_ASSERT_NO_THROW(p = a1.parent());
    CPPUNIT_ASSERT(p.is_valid());

    //create an array attribute
    nxattribute a2(_parent.attributes.template create<bool_t>("array",_shape));
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.type_id() == type_id_t::BOOL);
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.size() == 200);
    s = a2.shape<shape_t>();
    CPPUNIT_ASSERT(s.size() == 2);
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),_shape.begin()));

    //trying copy and move construction
    nxattribute a3 = a2;
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(a2.is_valid());

    nxattribute a4 = std::move(a2);
    CPPUNIT_ASSERT(a4.is_valid());
    CPPUNIT_ASSERT(!a2.is_valid());
}

//-----------------------------------------------------------------------------
template<typename APTYPE> 
template<typename T> void NXAttributeTest<APTYPE>::test_scalar_attribute()
{
    PRINT_TEST_FUNCTION_SIG;

    CPPUNIT_ASSERT(_parent.is_valid());

    //write data
    T write_value = create_scalar_data<T>();
    //write from object
    _parent.attributes.template create<T>("a1").write(write_value);
    _parent.attributes["a1"].write(1,(const T *)&write_value);
    //write from pointer
    _f.flush();
       
    //read data
    T read_value;
    //read to object
    _parent.attributes["a1"].read(read_value);
    //read to memory
    _parent.attributes["a1"].read(1,&read_value);

    check_equality(write_value,read_value);

    //--------------------test some exceptions---------------------------------
    //try to recreate an attribute
    CPPUNIT_ASSERT_THROW(
            _parent.attributes.template create<T>("a1"),pni::io::object_error);

    //try to open a non-existing attribute
    CPPUNIT_ASSERT_THROW(_parent.attributes["b1"],pni::io::key_error);
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
template<typename ATYPE> void NXAttributeTest<APTYPE>::test_array_attribute()
{
    PRINT_TEST_FUNCTION_SIG;
    typedef typename ATYPE::value_type value_t;
  
    ATYPE write;
    create_array(_shape,write);
    ATYPE read(write); 

    std::vector<value_t> data(create_array_data<value_t>(write.size()));
    std::copy(data.begin(),data.end(),write.begin());

    _parent.attributes.template create<value_t>("a2",_shape).write(write);
    _parent.attributes["a2"].read(read);

    CPPUNIT_ASSERT(std::equal(read.begin(),read.end(),write.begin()));
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::test_array()
{
    PRINT_TEST_FUNCTION_SIG;
    shape_t s{3};
    auto data = dynamic_array<string>::create(s);
    data[0] = "hello";
    data[1] = "world this";
    data[2] = "is a test";

    array o1(data);
    
    _parent.attributes.template create<string>("test",s).write(o1);
    array o2(dynamic_array<string>::create(s));
    _parent.attributes["test"].read(o2);

}

//----------------------------------------------------------------------------
template<typename APTYPE> 
template<typename T>
void NXAttributeTest<APTYPE>::test_partial_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uniform_distribution<T> generator_type; 
    
    generator_type generator;
    
    _parent.attributes.template create<T>("test",_shape);

    auto a = _parent.attributes["test"](0,0);

    //test shape and rank
    CPPUNIT_ASSERT(a.size()==1);
    CPPUNIT_ASSERT(a.rank()==0);
    CPPUNIT_ASSERT(a.template shape<shape_t>() == shape_t{});

    T write = generator();
    a.write(write);

    T read;
    a.read(read);

    check_equality(write,read);
}

//----------------------------------------------------------------------------
template<typename APTYPE>
template<typename T>
void NXAttributeTest<APTYPE>::test_partial_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uniform_distribution<T> generator_type;
    typedef dynamic_array<T> array_type;

    generator_type generator;

    _parent.attributes.template create<T>("test",_shape);

    auto a = _parent.attributes["test"](slice(0,10),1);
    
    CPPUNIT_ASSERT(a.rank() == 1);
    CPPUNIT_ASSERT(a.template shape<shape_t>() == shape_t{10});
    CPPUNIT_ASSERT(a.size() == 10);

    auto write = array_type::create(a.template shape<shape_t>());
    auto read  = array_type::create(a.template shape<shape_t>());
    std::generate(write.begin(),write.end(),generator);

    a.write(write);
    a.read(read);

    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));
}
