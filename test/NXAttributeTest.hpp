/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXAttributeTest.hpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Eugen Wintersberger
 */


#ifndef __NXATTRIBUTETEST_HPP__
#define __NXATTRIBUTETEST_HPP__

#include "common.hpp"
#include "data.hpp"

#define SARRAY( type ) SArray<type,10,20>
#define SBUFFER( type ) SBuffer<type,200>

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
        CPPUNIT_TEST(test_scalar_attribute<UInt8>);
        CPPUNIT_TEST(test_scalar_attribute<Int8>);
        CPPUNIT_TEST(test_scalar_attribute<UInt16>);
        CPPUNIT_TEST(test_scalar_attribute<Int16>);
        CPPUNIT_TEST(test_scalar_attribute<UInt32>);
        CPPUNIT_TEST(test_scalar_attribute<Int32>);
        CPPUNIT_TEST(test_scalar_attribute<UInt64>);
        CPPUNIT_TEST(test_scalar_attribute<Int64>);
        CPPUNIT_TEST(test_scalar_attribute<Float32>);
        CPPUNIT_TEST(test_scalar_attribute<Float64>);
        CPPUNIT_TEST(test_scalar_attribute<Float128>);
        CPPUNIT_TEST(test_scalar_attribute<Complex32>);
        CPPUNIT_TEST(test_scalar_attribute<Complex64>);
        CPPUNIT_TEST(test_scalar_attribute<Complex128>);

        CPPUNIT_TEST(test_scalar_attribute<String>);
        CPPUNIT_TEST(test_scalar_attribute<Bool>);
        CPPUNIT_TEST(test_scalar_attribute<Binary>);

        //testing buffer io
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<UInt8> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Int8> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<UInt16> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Int16> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<UInt32> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Int32> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<UInt64> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Int64> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Float32> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Float64> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Float128> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Complex32> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Complex64> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Complex128> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<String> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Bool> >);
        CPPUNIT_TEST(test_buffer_attribute<DBuffer<Binary> >);

        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(UInt8) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Int8) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(UInt16) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Int16) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(UInt32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Int32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(UInt64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Int64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Float32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Float64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Float128) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Complex32) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Complex64) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Complex128) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Bool) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(Binary) >);
        CPPUNIT_TEST(test_buffer_attribute<SBUFFER(String) >);

        //testing array io
        CPPUNIT_TEST(test_array_attribute<DArray<UInt8> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Int8> >);
        CPPUNIT_TEST(test_array_attribute<DArray<UInt16> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Int16> >);
        CPPUNIT_TEST(test_array_attribute<DArray<UInt32> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Int32> >);
        CPPUNIT_TEST(test_array_attribute<DArray<UInt64> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Int64> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Float32> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Float64> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Float128> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Complex32> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Complex64> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Complex128> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Bool> >);
        CPPUNIT_TEST(test_array_attribute<DArray<String> >);
        CPPUNIT_TEST(test_array_attribute<DArray<Binary> >);

        CPPUNIT_TEST(test_array_attribute<SARRAY(UInt8) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Int8) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(UInt16) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Int16) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(UInt32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Int32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(UInt64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Int64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Float32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Float64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Float128) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Complex32) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Complex64) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Complex128) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Bool) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(Binary) >);
        CPPUNIT_TEST(test_array_attribute<SARRAY(String) >);
        
        CPPUNIT_TEST_SUITE_END();
    private:
        NXFile _f;
        APTYPE _parent;
        shape_t _shape;
        size_t _size;

        //==========static functions to create parent objects==================
        static void create_parent(const NXFile &f,NXFile &p);
        static void create_parent(const NXFile &f,NXGroup &p);
        static void create_parent(const NXFile &f,NXField &p);

        //==============static functions to create arrays======================
        template<typename T>
        static void create_array(const shape_t &s,DArray<T> &a)
        {
            a = DArray<T>(s);
        }

        //---------------------------------------------------------------------
        template<typename T,size_t ...DIMS>
        static void create_array(const shape_t &s,SArray<T,DIMS...> &a)
        {
            //there is nothing to do here
        }

        //---------------------------------------------------------------------
        template<typename T>
        static void create_buffer(const size_t &size,DBuffer<T> &b)
        {
            b = DBuffer<T>(size);
        }

        //---------------------------------------------------------------------
        template<typename T,size_t SIZE>
        static void create_buffer(const size_t &size,SBuffer<T,SIZE> &b)
        {
        }
    public:
        void setUp();
        void tearDown();
        void test_creation();
        template<typename T> void test_scalar_attribute();
        template<typename ATYPE> void test_array_attribute();
        template<typename BTYPE> void test_buffer_attribute();
};

//-----------------------------------------------------------------------------
template<typename APTYPE> 
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXFile &p)
{
    p = f;
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXGroup &p)
{
    p = f.create_group("testgroup");
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXField &p)
{
    p = f.create_field<String>("hello");
    p.write("hello world");
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::setUp()
{
    //create the file where to store data
    _f = NXFile::create_file("NXAttributeTest.h5",true,0);

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
    NXAttribute a;
    CPPUNIT_ASSERT(a.size()==1);
    CPPUNIT_ASSERT(!a.is_valid());
    CPPUNIT_ASSERT(a.rank() == 0);

    //creating a scalar attribute
    NXAttribute a1(_parent.template attr<String>("attribute"));
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.type_id() == TypeID::STRING);
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.size() == 1);
    auto s = a1.shape<shape_t>();
    CPPUNIT_ASSERT(s.size() == 0);

    //create an array attribute
    NXAttribute a2(_parent.template attr<Bool>("array",_shape));
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.type_id() == TypeID::BOOL);
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
            _parent.template attr<T>("a1"),pni::nx::NXAttributeError);

    //try to open a non-existing attribute
    CPPUNIT_ASSERT_THROW(_parent.attr("b1"),pni::nx::NXAttributeError);
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


#endif
