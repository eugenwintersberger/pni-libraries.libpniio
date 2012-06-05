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

#include <functional>
#include <random>

#include "NX.hpp"
#include <pni/utils/ArrayFactory.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "TestHelpers.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class NXFieldTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NXFieldTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testOpen);
    CPPUNIT_TEST(test_resize);
    //testing a simple scalar field
    CPPUNIT_TEST(test_io_simple<UInt8>);
    CPPUNIT_TEST(test_io_simple<Int8>);
    CPPUNIT_TEST(test_io_simple<UInt16>);
    CPPUNIT_TEST(test_io_simple<Int16>);
    CPPUNIT_TEST(test_io_simple<UInt32>);
    CPPUNIT_TEST(test_io_simple<Int32>);
    CPPUNIT_TEST(test_io_simple<UInt64>);
    CPPUNIT_TEST(test_io_simple<Int64>);
    CPPUNIT_TEST(test_io_simple<Binary>);
    CPPUNIT_TEST(test_io_simple<Float32>);
    CPPUNIT_TEST(test_io_simple<Float64>);
    CPPUNIT_TEST(test_io_simple<Float128>);
    CPPUNIT_TEST(test_io_simple<Complex32>);
    CPPUNIT_TEST(test_io_simple<Complex64>);
    CPPUNIT_TEST(test_io_simple<Complex128>);
    CPPUNIT_TEST(test_io_simple<String>);
    //testing scalar object IO
    CPPUNIT_TEST(test_io_scalar<UInt8>);
    CPPUNIT_TEST(test_io_scalar<Int8>);
    CPPUNIT_TEST(test_io_scalar<UInt16>);
    CPPUNIT_TEST(test_io_scalar<Int16>);
    CPPUNIT_TEST(test_io_scalar<UInt32>);
    CPPUNIT_TEST(test_io_scalar<Int32>);
    CPPUNIT_TEST(test_io_scalar<UInt64>);
    CPPUNIT_TEST(test_io_scalar<Int64>);
    CPPUNIT_TEST(test_io_scalar<Float32>);
    CPPUNIT_TEST(test_io_scalar<Float64>);
    CPPUNIT_TEST(test_io_scalar<Float128>);
    CPPUNIT_TEST(test_io_scalar<Complex32>);
    CPPUNIT_TEST(test_io_scalar<Complex64>);
    CPPUNIT_TEST(test_io_scalar<Complex128>);
    //testing buffer io 
    CPPUNIT_TEST(test_io_buffer<UInt8>);
    CPPUNIT_TEST(test_io_buffer<Int8>);
    CPPUNIT_TEST(test_io_buffer<UInt16>);
    CPPUNIT_TEST(test_io_buffer<Int16>);
    CPPUNIT_TEST(test_io_buffer<UInt32>);
    CPPUNIT_TEST(test_io_buffer<Int32>);
    CPPUNIT_TEST(test_io_buffer<UInt64>);
    CPPUNIT_TEST(test_io_buffer<Int64>);
    CPPUNIT_TEST(test_io_buffer<Binary>);
    CPPUNIT_TEST(test_io_buffer<Float32>);
    CPPUNIT_TEST(test_io_buffer<Float64>);
    CPPUNIT_TEST(test_io_buffer<Float128>);
    CPPUNIT_TEST(test_io_buffer<Complex32>);
    CPPUNIT_TEST(test_io_buffer<Complex64>);
    CPPUNIT_TEST(test_io_buffer<Complex128>);
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
    template<typename T> void test_io_simple();
    template<typename T> void test_io_scalar();
    template<typename T> void test_io_buffer();
    template<typename T> void test_io_array();
    void test_io_string();

};

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_array(){
    std::cout<<"NXFieldTest::test_io_array()--------------------------------";
    std::cout<<std::endl;
    Shape s = {10,50};
    Array<T,Buffer> write = ArrayFactory<T,Buffer>::create(s);
    Array<T,Buffer> read = ArrayFactory<T,Buffer>::create(s);

    write = 100;
    read  = 0;

    NXField field1 = file.create_field<T>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    field1 = file.create_field<T>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);

    NXDeflateFilter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = file.create_field<T>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

}

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_buffer(){
    Shape s={1024};
    Buffer<T> write_buffer(1024);
    Buffer<T> read_buffer(1024);

    init_values(write_buffer,read_buffer);

    NXField field1 = file.create_field<T>("scalar",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    for(size_t i=0;i<1024;i++) 
        compare_values(write_buffer[i],read_buffer[i]);

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<T>("scalar2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);

    write_buffer.free();
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),MemoryAccessError);
}

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_scalar(){
    NXField field1 = file.create_field<T>("scalar");

    Scalar<T> scalar("value","a.u");
    Scalar<T> read("value","a.u");

    init_values(scalar,read);

    CPPUNIT_ASSERT_NO_THROW(field1.write(scalar));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    compare_values(scalar.value(),read.value());

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(scalar),ShapeMissmatchError);
}

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_simple(){
    NXField field1 = file.create_field<T>("scalar");
    T write,read;
    init_values<T>(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    compare_values(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);

}


#endif /* NXNUMERICFIELDTEST_HPP_ */
