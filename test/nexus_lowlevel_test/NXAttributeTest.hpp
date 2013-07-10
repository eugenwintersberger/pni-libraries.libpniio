/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * NXAttributeTest.hpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Eugen Wintersberger
 */


#pragma once
#include "common.hpp"
#include "data.hpp"
#include <pni/core/arrays.hpp>

#define SARRAY( type ) sarray<type,10,20>
#define SBUFFER( type ) sbuffer<type,200>

/*!
\ingroup test_classes
\brief Attribute facilities test

Testing attribute facilities of different Nexus objects
\tparam APTYPE attribute parent type (group, field, or file)
*/
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
        CPPUNIT_TEST(test_scalar_attribute<bool>);
        CPPUNIT_TEST(test_scalar_attribute<binary>);

        //testing buffer io
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<uint8> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<int8> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<uint16> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<int16> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<uint32> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<int32> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<uint64> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<int64> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<float32> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<float64> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<float128> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<complex32> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<complex64> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<complex128> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<string> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<bool> >);
        CPPUNIT_TEST(test_buffer_attribute<dbuffer<binary> >);

        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(uint8) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(int8) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(uint16) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(int16) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(uint32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(int32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(uint64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(int64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(float32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(float64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(float128) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(complex32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(complex64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(complex128) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(bool) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(binary) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(string) >);

        //testing array io
        CPPUNIT_TEST(test_array_attribute<darray<uint8> >);
        CPPUNIT_TEST(test_array_attribute<darray<int8> >);
        CPPUNIT_TEST(test_array_attribute<darray<uint16> >);
        CPPUNIT_TEST(test_array_attribute<darray<int16> >);
        CPPUNIT_TEST(test_array_attribute<darray<uint32> >);
        CPPUNIT_TEST(test_array_attribute<darray<int32> >);
        CPPUNIT_TEST(test_array_attribute<darray<uint64> >);
        CPPUNIT_TEST(test_array_attribute<darray<int64> >);
        CPPUNIT_TEST(test_array_attribute<darray<float32> >);
        CPPUNIT_TEST(test_array_attribute<darray<float64> >);
        CPPUNIT_TEST(test_array_attribute<darray<float128> >);
        CPPUNIT_TEST(test_array_attribute<darray<complex32> >);
        CPPUNIT_TEST(test_array_attribute<darray<complex64> >);
        CPPUNIT_TEST(test_array_attribute<darray<complex128> >);
        CPPUNIT_TEST(test_array_attribute<darray<bool> >);
        CPPUNIT_TEST(test_array_attribute<darray<string> >);
        CPPUNIT_TEST(test_array_attribute<darray<binary> >);

        CPPUNIT_TEST(test_array_attribute<SARRAY(uint8) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(int8) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(uint16) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(int16) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(uint32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(int32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(uint64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(int64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(float32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(float64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(float128) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(complex32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(complex64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(complex128) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(bool) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(binary) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(string) >);

        CPPUNIT_TEST(test_array);
        
        CPPUNIT_TEST_SUITE_END();
    private:
        nxfile _f;
        APTYPE _parent;
        shape_t _shape;
        size_t _size;

        //==========static functions to create parent objects==================
        static void create_parent(const nxfile &f,nxfile &p);
        static void create_parent(const nxfile &f,nxgroup &p);
        static void create_parent(const nxfile &f,nxfield &p);

        //==============static functions to create arrays======================
        template<typename T>
        static void create_array(const shape_t &s,darray<T> &a)
        {
            a = darray<T>(s);
        }

        //---------------------------------------------------------------------
        template<typename T,size_t ...DIMS>
        static void create_array(const shape_t &s,sarray<T,DIMS...> &a)
        {
            //there is nothing to do here
        }

        //---------------------------------------------------------------------
        template<typename T>
        static void create_buffer(const size_t &size,dbuffer<T> &b)
        {
            b = dbuffer<T>(size);
        }

        //---------------------------------------------------------------------
        template<typename T,size_t SIZE>
        static void create_buffer(const size_t &size,sbuffer<T,SIZE> &b)
        {
        }
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_array();
        template<typename T> void test_scalar_attribute();
        template<typename ATYPE> void test_array_attribute();
        template<typename BTYPE> void test_buffer_attribute();
};

//-----------------------------------------------------------------------------
template<typename APTYPE> 
void NXAttributeTest<APTYPE>::create_parent(const nxfile &f,nxfile &p)
{
    p = f;
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const nxfile &f,nxgroup &p)
{
    p = f.create_group("testgroup");
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const nxfile &f,nxfield &p)
{
    p = f.create_field<string>("hello");
    p.write("hello world");
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::setUp()
{
    //create the file where to store data
    _f = nxfile::create_file("NXAttributeTest.h5",true,0);

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
    CPPUNIT_ASSERT(a.size()==1);
    CPPUNIT_ASSERT(!a.is_valid());
    CPPUNIT_ASSERT(a.rank() == 0);

    //creating a scalar attribute
    nxattribute a1(_parent.template attr<string>("attribute"));
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.type_id() == type_id_t::STRING);
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.size() == 1);
    auto s = a1.shape<shape_t>();
    CPPUNIT_ASSERT(s.size() == 0);

    //create an array attribute
    nxattribute a2(_parent.template attr<bool>("array",_shape));
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.type_id() == type_id_t::BOOL);
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.size() == 200);
    s = a2.shape<shape_t>();
    CPPUNIT_ASSERT(s.size() == 2);
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),_shape.begin()));
}

//-----------------------------------------------------------------------------
template<typename APTYPE> 
template<typename T> void NXAttributeTest<APTYPE>::test_scalar_attribute()
{
    PRINT_TEST_FUNCTION_SIG;

    CPPUNIT_ASSERT(_parent.is_valid());

    //write data
    T write_value = create_scalar_data<T>();
    _parent.template attr<T>("a1").write(write_value);
    _f.flush();
       
    //read data
    T read_value;
    _parent.attr("a1").read(read_value);
    check_equality(write_value,read_value);

    //--------------------test some exceptions---------------------------------
    //try to recreate an attribute
    CPPUNIT_ASSERT_THROW(
            _parent.template attr<T>("a1"),pni::io::nx::nxattribute_error);

    //try to open a non-existing attribute
    CPPUNIT_ASSERT_THROW(_parent.attr("b1"),pni::io::nx::nxattribute_error);
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

    _parent.template attr<value_t>("a2",_shape).write(write);
    _parent.attr("a2").read(read);

    CPPUNIT_ASSERT(std::equal(read.begin(),read.end(),write.begin()));
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
template<typename BTYPE> void NXAttributeTest<APTYPE>::test_buffer_attribute()
{
    PRINT_TEST_FUNCTION_SIG;
    typedef typename BTYPE::value_type value_t;

    BTYPE write;
    create_buffer(_size,write);
    BTYPE read(write); 

    std::vector<value_t> data(create_array_data<value_t>(write.size()));
    std::copy(data.begin(),data.end(),write.begin());

    _parent.template attr<value_t>("a2",_shape).write(write);
    _parent.attr("a2").read(read);

    CPPUNIT_ASSERT(std::equal(read.begin(),read.end(),write.begin()));
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::test_array()
{
    PRINT_TEST_FUNCTION_SIG;
    shape_t s{3};
    darray<string> data(s);
    data[0] = "hello";
    data[1] = "world this";
    data[2] = "is a test";

    array o1(data);
    
    _parent.template attr<string>("test",s).write(o1);
    array o2 = darray<string>(s);
    _parent.attr("test").read(o2);

}

