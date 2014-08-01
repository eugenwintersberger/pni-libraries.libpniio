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
// NXNumericFieldTest.hpp
//
//  Created on: Dec 3, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/core/arrays.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

class NXFieldTest:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(NXFieldTest);
	CPPUNIT_TEST(test_creation);
	CPPUNIT_TEST(test_assignment);
	CPPUNIT_TEST(test_open);
    CPPUNIT_TEST(test_parent);
    //testing scalar object IO
    CPPUNIT_TEST(test_io_scalar<uint8>);
    CPPUNIT_TEST(test_io_scalar<int8>);
    CPPUNIT_TEST(test_io_scalar<uint16>);
    CPPUNIT_TEST(test_io_scalar<int16>);
    CPPUNIT_TEST(test_io_scalar<uint32>);
    CPPUNIT_TEST(test_io_scalar<int32>);
    CPPUNIT_TEST(test_io_scalar<uint64>);
    CPPUNIT_TEST(test_io_scalar<int64>);
    CPPUNIT_TEST(test_io_scalar<float32>);
    CPPUNIT_TEST(test_io_scalar<float64>);
    CPPUNIT_TEST(test_io_scalar<float128>);
    CPPUNIT_TEST(test_io_scalar<complex32>);
    CPPUNIT_TEST(test_io_scalar<complex64>);
    CPPUNIT_TEST(test_io_scalar<complex128>);
    CPPUNIT_TEST(test_io_scalar<binary>);
    CPPUNIT_TEST(test_io_bool_scalar);
    CPPUNIT_TEST(test_io_string_scalar);
    //testing array IO
    CPPUNIT_TEST(test_io_array<uint8>);
    CPPUNIT_TEST(test_io_array<int8>);
    CPPUNIT_TEST(test_io_array<uint16>);
    CPPUNIT_TEST(test_io_array<int16>);
    CPPUNIT_TEST(test_io_array<uint32>);
    CPPUNIT_TEST(test_io_array<int32>);
    CPPUNIT_TEST(test_io_array<uint64>);
    CPPUNIT_TEST(test_io_array<int64>);
    CPPUNIT_TEST(test_io_array<float32>);
    CPPUNIT_TEST(test_io_array<float64>);
    CPPUNIT_TEST(test_io_array<float128>);
    CPPUNIT_TEST(test_io_array<complex32>);
    CPPUNIT_TEST(test_io_array<complex64>);
    CPPUNIT_TEST(test_io_array<complex128>);
    CPPUNIT_TEST(test_io_array<binary>);
    //CPPUNIT_TEST(test_io_bool_array);
    CPPUNIT_TEST(test_grow);
    CPPUNIT_TEST(test_io_string_array);

    CPPUNIT_TEST(test_io_array);

	CPPUNIT_TEST_SUITE_END();
private:
	nxfile file;
    nxgroup root;
	static const uint64 n=10;
	uint16 testdata[10];
	shape_t  fshape;
	size_t nx;
	size_t ny;

public:
	void setUp();
	void tearDown();
	void test_creation();
	void test_assignment();
	void test_open();
    template<typename T> void test_io_simple();
    template<typename T> void test_io_scalar();
    void test_io_string_scalar();
    void test_io_bool_scalar();
    template<typename T> void test_io_array();
    void test_io_string_array();
    //void test_io_bool_array();
    void test_io_string();

    template<typename T> void test_scalar_selection();
    void test_grow();
    void test_parent();
    void test_io_array();

};

template<typename T> T create_init_data(const T &value) { return value; }

//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{10,50};
    auto write = dynamic_array<T>::create(s);
    auto read  = dynamic_array<T>::create(s);

    std::fill(write.begin(),write.end(),T(100));
    std::fill(write.begin(),write.end(),T(0));

    nxfield field1 = root.create_field<T>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    field1 = root.create_field<T>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),size_mismatch_error);

    nxdeflate_filter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = root.create_field<T>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

}


//-----------------------------------------------------------------------------
template<typename T> void NXFieldTest::test_io_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxfield field1 = root.create_field<T>("scalar");

    T write,read;

    init_values(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    compare_values(write,read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),size_mismatch_error);
}

