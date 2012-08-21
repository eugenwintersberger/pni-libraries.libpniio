/*
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
 * NXSelectionTest.hpp
 *
 *  Created on: Feb 14, 2012
 *      Author: Eugen Wintersberger
 */

#ifndef __NXSELECTIONTEST_HPP__
#define __NXSELECTIONTEST_HPP__

#include <boost/current_function.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include "NX.hpp"
#include "EqualityCheck.hpp"


#include "TestHelpers.hpp"

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::utils;
using namespace pni::nx::h5;

class NXSelectionTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(NXSelectionTest);

        //test scalar selections
        CPPUNIT_TEST(test_scalar_selection<UInt8>);
        CPPUNIT_TEST(test_scalar_selection<Int8>);
        CPPUNIT_TEST(test_scalar_selection<UInt16>);
        CPPUNIT_TEST(test_scalar_selection<Int16>);
        CPPUNIT_TEST(test_scalar_selection<UInt32>);
        CPPUNIT_TEST(test_scalar_selection<Int32>);
        CPPUNIT_TEST(test_scalar_selection<UInt64>);
        CPPUNIT_TEST(test_scalar_selection<Int64>);
        CPPUNIT_TEST(test_scalar_selection<Float32>);
        CPPUNIT_TEST(test_scalar_selection<Float64>);
        CPPUNIT_TEST(test_scalar_selection<Float128>);
        CPPUNIT_TEST(test_scalar_selection<Complex32>);
        CPPUNIT_TEST(test_scalar_selection<Complex64>);
        CPPUNIT_TEST(test_scalar_selection<Complex128>);

        //test non-scalar selections using arrays and buffers for IO
        CPPUNIT_TEST(test_array_selection<UInt8>);
        CPPUNIT_TEST(test_array_selection<Int8>);
        CPPUNIT_TEST(test_array_selection<UInt16>);
        CPPUNIT_TEST(test_array_selection<Int16>);
        CPPUNIT_TEST(test_array_selection<UInt32>);
        CPPUNIT_TEST(test_array_selection<Int32>);
        CPPUNIT_TEST(test_array_selection<UInt64>);
        CPPUNIT_TEST(test_array_selection<Int64>);
        CPPUNIT_TEST(test_array_selection<Float32>);
        CPPUNIT_TEST(test_array_selection<Float64>);
        CPPUNIT_TEST(test_array_selection<Float128>);
        CPPUNIT_TEST(test_array_selection<Complex32>);
        CPPUNIT_TEST(test_array_selection<Complex64>);
        CPPUNIT_TEST(test_array_selection<Complex128>);

        CPPUNIT_TEST_SUITE_END();
    private:
        NXFile file;
    public:
        void setUp();
        void tearDown();
        template<typename T> void test_scalar_selection();
        template<typename T> void test_array_selection();


};

//-----------------------------------------------------------------------------
//testting to write to a simple scalar datatype
template<typename T> void NXSelectionTest::test_scalar_selection()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t shape{3,4};
    NXField field = file.create_field<T>("array",shape);

    T write,read;

    for(size_t i=1;i<shape[0];i++)
    {
        for(size_t j=0;j<shape[1];j++)
        {
            write = T(i*j);
            read = T(0);
            field(i,j).write(write);
            field(i,j).read(read);
            check_equality(read,write);
        }
    }

    CPPUNIT_ASSERT_THROW(field(Slice(1,3)).write(write),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(field(Slice(0,4)).read(read),ShapeMissmatchError);
}

//-----------------------------------------------------------------------------
//testting to write to an array selection
template<typename T> void NXSelectionTest::test_array_selection()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t shape{3,4};
    NXField field = file.create_field<T>("array",shape);

    DArray<T> write(shape_t({3})),read(shape_t({3}));

    for(size_t j=0;j<shape[1];j++)
    {
        std::fill(write.begin(),write.end(),T(j));
        std::fill(read.begin(),read.end(),T(0));
        
        field(Slice(0,3),j).write(write);
        field(Slice(0,3),j).read(read);

        for(size_t i=0;i<write.size();i++) check_equality(read[i],write[i]);
    }

    CPPUNIT_ASSERT_THROW(field(Slice(1,3),0).write(write),ShapeMissmatchError);
    DBuffer<T> rbuff(2);
    CPPUNIT_ASSERT_THROW(field(Slice(0,3),0).read(rbuff),SizeMissmatchError);
    rbuff.free();
    CPPUNIT_ASSERT_THROW(field(Slice(0,3),0).read(rbuff),MemoryNotAllocatedError);
}


#endif
