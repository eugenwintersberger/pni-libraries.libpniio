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
 * NXNumericFieldTest.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef __NXFIELDTEST_HPP__
#define __NXFIELDTEST_HPP__

#include "NX.hpp"
#include <pni/utils/Index.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::utils;
using namespace pni::nx::h5;

class NXFieldTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testOpen);
    CPPUNIT_TEST(test_resize);
    //testing a simple scalar field
    CPPUNIT_TEST(test_io_int<UInt8>);
    CPPUNIT_TEST(test_io_int<Int8>);
    CPPUNIT_TEST(test_io_int<UInt16>);
    CPPUNIT_TEST(test_io_int<Int16>);
    CPPUNIT_TEST(test_io_int<UInt32>);
    CPPUNIT_TEST(test_io_int<Int32>);
    CPPUNIT_TEST(test_io_int<UInt64>);
    CPPUNIT_TEST(test_io_int<Int64>);
    CPPUNIT_TEST(test_io_int<Binary>);
    CPPUNIT_TEST(test_io_float<Float32>);
    CPPUNIT_TEST(test_io_float<Float64>);
    CPPUNIT_TEST(test_io_float<Float128>);
    CPPUNIT_TEST(test_io_complex<Complex32>);
    CPPUNIT_TEST(test_io_complex<Complex64>);
    CPPUNIT_TEST(test_io_complex<Complex128>);
    CPPUNIT_TEST(test_io_string);
    //testing scalar object IO
    CPPUNIT_TEST(test_io_scalar<UInt8>);
    CPPUNIT_TEST(test_io_scalar<Int8>);
    CPPUNIT_TEST(test_io_scalar<UInt16>);
    CPPUNIT_TEST(test_io_scalar<Int16>);
    CPPUNIT_TEST(test_io_scalar<UInt32>);
    CPPUNIT_TEST(test_io_scalar<Int32>);
    CPPUNIT_TEST(test_io_scalar<UInt64>);
    CPPUNIT_TEST(test_io_scalar<Int64>);
    CPPUNIT_TEST(test_io_scalarfloat<Float32>);
    CPPUNIT_TEST(test_io_scalarfloat<Float64>);
    CPPUNIT_TEST(test_io_scalarfloat<Float128>);
    CPPUNIT_TEST(test_io_scalarcmplx<Complex32>);
    CPPUNIT_TEST(test_io_scalarcmplx<Complex64>);
    CPPUNIT_TEST(test_io_scalarcmplx<Complex128>);
    //testing buffer io 
    CPPUNIT_TEST(test_io_buffer_int<UInt8>);
    CPPUNIT_TEST(test_io_buffer_int<Int8>);
    CPPUNIT_TEST(test_io_buffer_int<UInt16>);
    CPPUNIT_TEST(test_io_buffer_int<Int16>);
    CPPUNIT_TEST(test_io_buffer_int<UInt32>);
    CPPUNIT_TEST(test_io_buffer_int<Int32>);
    CPPUNIT_TEST(test_io_buffer_int<UInt64>);
    CPPUNIT_TEST(test_io_buffer_int<Int64>);
    CPPUNIT_TEST(test_io_buffer_int<Binary>);
    CPPUNIT_TEST(test_io_buffer_float<Float32>);
    CPPUNIT_TEST(test_io_buffer_float<Float64>);
    CPPUNIT_TEST(test_io_buffer_float<Float128>);
    CPPUNIT_TEST(test_io_buffer_cmplx<Complex32>);
    CPPUNIT_TEST(test_io_buffer_cmplx<Complex64>);
    CPPUNIT_TEST(test_io_buffer_cmplx<Complex128>);
    //testing array IO
    CPPUNIT_TEST(test_io_array<UInt8>);
    CPPUNIT_TEST(test_io_array<Int8>);
    CPPUNIT_TEST(test_io_array<UInt16>);
    CPPUNIT_TEST(test_io_array<Int16>);
    CPPUNIT_TEST(test_io_array<UInt32>);
    CPPUNIT_TEST(test_io_array<Int32>);
    CPPUNIT_TEST(test_io_array<UInt64>);
    CPPUNIT_TEST(test_io_array<Int64>);
    CPPUNIT_TEST(test_io_array<Float32>);
    CPPUNIT_TEST(test_io_array<Float64>);
    CPPUNIT_TEST(test_io_array<Float128>);
    CPPUNIT_TEST(test_io_array<Complex32>);
    CPPUNIT_TEST(test_io_array<Complex64>);
    CPPUNIT_TEST(test_io_array<Complex128>);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile file;
	static const UInt64 n=10;
	UInt16 testdata[10];
	Shape  fshape;
	size_t nx;
	size_t ny;

public:
	void setUp();
	void tearDown();
	void testCreation();
	void testAssignment();
	void testOpen();
    void test_resize();
    template<typename T> void test_io_int();
    template<typename T> void test_io_float();
    template<typename T> void test_io_complex();
    template<typename T> void test_io_scalar();
    template<typename T> void test_io_scalarfloat();
    template<typename T> void test_io_scalarcmplx();
    template<typename T> void test_io_buffer_int();
    template<typename T> void test_io_buffer_float();
    template<typename T> void test_io_buffer_cmplx();
    template<typename T> void test_io_array();
    void test_io_string();

};

template<typename T> void NXFieldTest::test_io_array(){
    Shape s = {10,50};
    Array<T,Buffer> write(s);
    Array<T,Buffer> read(s);

    write = 100;
    read  = 0;

    NXField field1 = file.create_field<T>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

}

template<typename T> void NXFieldTest::test_io_buffer_int(){
    Shape s={1024};
    Buffer<T> write_buffer(1024);
    Buffer<T> read_buffer(1024);

    write_buffer = 100;
    read_buffer = 0;
    NXField field1 = file.create_field<T>("scalar",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    for(size_t i=0;i<1024;i++) 
        CPPUNIT_ASSERT(write_buffer[i] == read_buffer[i]);

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<T>("scalar2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);
}

template<typename T> void NXFieldTest::test_io_buffer_float(){
    Shape s={1024};
    Buffer<T> write_buffer(1024);
    Buffer<T> read_buffer(1024);

    write_buffer = 113.1234;
    read_buffer = 0;
    NXField field1 = file.create_field<T>("scalar",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    for(size_t i=0;i<1024;i++) 
        CPPUNIT_ASSERT_DOUBLES_EQUAL(write_buffer[i],read_buffer[i],1.e-6);

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<T>("scalar2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);
}

template<typename T> void NXFieldTest::test_io_buffer_cmplx(){
    Shape s={1024};
    Buffer<T> write_buffer(1024);
    Buffer<T> read_buffer(1024);

    write_buffer = T(113.1234,-1233.9283e-3);
    read_buffer = T(0,0);
    NXField field1 = file.create_field<T>("scalar",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    for(size_t i=0;i<1024;i++){
        CPPUNIT_ASSERT_DOUBLES_EQUAL(write_buffer[i].real(),read_buffer[i].real(),1.e-6);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(write_buffer[i].imag(),read_buffer[i].imag(),1.e-6);
    }

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<T>("scalar2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);
}

template<typename T> void NXFieldTest::test_io_scalar(){
    NXField field1 = file.create_field<T>("scalar");

    Scalar<T> scalar(1,"value","a.u");
    Scalar<T> read("value","a.u");

    CPPUNIT_ASSERT_NO_THROW(field1.write(scalar));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(scalar.value() == read.value());
}

template<typename T> void NXFieldTest::test_io_scalarfloat(){
    NXField field1 = file.create_field<T>("scalar");

    Scalar<T> scalar(1,"value","a.u");
    Scalar<T> read("value","a.u");

    CPPUNIT_ASSERT_NO_THROW(field1.write(scalar));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(scalar.value(),read.value(),1.e-6);
}

template<typename T> void NXFieldTest::test_io_scalarcmplx(){
    NXField field1 = file.create_field<T>("scalar");

    Scalar<T> scalar(1,"value","a.u");
    Scalar<T> read("value","a.u");

    CPPUNIT_ASSERT_NO_THROW(field1.write(scalar));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(scalar.value().real(),read.value().real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(scalar.value().imag(),read.value().imag(),1.e-6);
}

template<typename T> void NXFieldTest::test_io_int(){
    NXField field1 = file.create_field<T>("scalar");
    T write=0,read=0;

    write = 1;
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);
}

template<typename T> void NXFieldTest::test_io_float(){
    NXField field1 = file.create_field<T>("float");
    T write=0.0,read=0.0;

    write = 0.123e-4;
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(write,read,1.e-6);
}

template<typename T> void NXFieldTest::test_io_complex(){
    NXField field1 = file.create_field<T>("float");
    T write(0.0,0),read(0,0);

    write = T(0.123e-4,-1.234);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(write.real(),read.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(write.imag(),read.imag(),1.e-6);
}


#endif /* NXNUMERICFIELDTEST_HPP_ */
