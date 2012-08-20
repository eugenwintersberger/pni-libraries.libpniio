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

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include "NX.hpp"
#include <pni/utils/Array.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "TestHelpers.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class NXFieldTest:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(NXFieldTest);
	CPPUNIT_TEST(test_creation);
	CPPUNIT_TEST(test_assignment);
	CPPUNIT_TEST(test_open);
    CPPUNIT_TEST(test_resize);
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
	shape_t  fshape;
	size_t nx;
	size_t ny;

public:
	void setUp();
	void tearDown();
	void test_creation();
	void test_assignment();
	void test_open();
    void test_resize();
    template<typename T> void test_io_simple();
    template<typename T> void test_io_scalar();
    template<typename T> void test_io_buffer();
    template<typename T> void test_io_array();
    void test_io_string();

};

template<typename T> T create_init_data(const T &value) { return value; }

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{10,50};
    DArray<T> write(s);
    DArray<T> read(s);

    std::fill(write.begin(),write.end(),T(100));
    std::fill(write.begin(),write.end(),T(0));

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
template<typename T> void NXFieldTest::test_io_buffer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{1024};
    DBuffer<T> write_buffer(1024);
    DBuffer<T> read_buffer(1024);

    std::fill(write_buffer.begin(),write_buffer.end(),T(100));
    std::fill(read_buffer.begin(),read_buffer.end(),T(0));

    NXField field1 = file.create_field<T>("buffer",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    for(size_t i=0;i<1024;i++) 
        compare_values(write_buffer[i],read_buffer[i]);

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<T>("buffer2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);

    write_buffer.free();
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),MemoryNotAllocatedError);
}

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    NXField field1 = file.create_field<T>("scalar");

    T write,read;

    init_values(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    compare_values(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);
}



#endif /* NXNUMERICFIELDTEST_HPP_ */
