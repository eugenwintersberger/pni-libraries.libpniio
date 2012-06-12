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

#include <pni/utils/Types.hpp>
#include "../src/NX.hpp"

#include "TestHelpers.hpp"

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::utils;
using namespace pni::nx::h5;

class NXSelectionTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(NXSelectionTest);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST(test_assignment);
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
        CPPUNIT_TEST_SUITE_END();
    private:
        NXFile file;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        template<typename T> void test_io_simple();


};

//testting to write to a simple scalar datatype
template<typename T> void NXSelectionTest::test_io_simple(){
    std::cout<<"NXSelectionTest::test_io_simple<T>()-------------------------";
    std::cout<<std::endl;
    NXField field = file.create_field<T>("scalar");
    T write,read;
    init_values<T>(write,read);

    CPPUNIT_ASSERT_NO_THROW(field.write(write));
    for(size_t i=1;i<10;i++){
        CPPUNIT_ASSERT_NO_THROW(field.grow(0,1));
        CPPUNIT_ASSERT_NO_THROW(field(i).write(write));
    }
    
    for(size_t i=0;i<10;i++){
        CPPUNIT_ASSERT_NO_THROW(field(i).read(read));
        //std::cout<<write<<" = "<<read<<std::endl;
        compare_values(write,read);
    }

    CPPUNIT_ASSERT_THROW(field(Slice(1,3)).write(write),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(field(Slice(0,4)).read(read),ShapeMissmatchError);
}



#endif
