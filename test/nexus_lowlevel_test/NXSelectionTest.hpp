/*
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
 * NXSelectionTest.hpp
 *
 *  Created on: Feb 14, 2012
 *      Author: Eugen Wintersberger
 */
#pragma once

#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include "EqualityCheck.hpp"


#include "TestHelpers.hpp"

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

using namespace pni::core;
using namespace pni::io::nx::h5;

class NXSelectionTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(NXSelectionTest);

        //test scalar selections
        CPPUNIT_TEST(test_scalar_selection<uint8>);
        CPPUNIT_TEST(test_scalar_selection<int8>);
        CPPUNIT_TEST(test_scalar_selection<uint16>);
        CPPUNIT_TEST(test_scalar_selection<int16>);
        CPPUNIT_TEST(test_scalar_selection<uint32>);
        CPPUNIT_TEST(test_scalar_selection<int32>);
        CPPUNIT_TEST(test_scalar_selection<uint64>);
        CPPUNIT_TEST(test_scalar_selection<int64>);
        CPPUNIT_TEST(test_scalar_selection<float32>);
        CPPUNIT_TEST(test_scalar_selection<float64>);
        CPPUNIT_TEST(test_scalar_selection<float128>);
        CPPUNIT_TEST(test_scalar_selection<complex32>);
        CPPUNIT_TEST(test_scalar_selection<complex64>);
        CPPUNIT_TEST(test_scalar_selection<complex128>);

        //test non-scalar selections using arrays and buffers for IO
        CPPUNIT_TEST(test_array_selection<uint8>);
        CPPUNIT_TEST(test_array_selection<int8>);
        CPPUNIT_TEST(test_array_selection<uint16>);
        CPPUNIT_TEST(test_array_selection<int16>);
        CPPUNIT_TEST(test_array_selection<uint32>);
        CPPUNIT_TEST(test_array_selection<int32>);
        CPPUNIT_TEST(test_array_selection<uint64>);
        CPPUNIT_TEST(test_array_selection<int64>);
        CPPUNIT_TEST(test_array_selection<float32>);
        CPPUNIT_TEST(test_array_selection<float64>);
        CPPUNIT_TEST(test_array_selection<float128>);
        CPPUNIT_TEST(test_array_selection<complex32>);
        CPPUNIT_TEST(test_array_selection<complex64>);
        CPPUNIT_TEST(test_array_selection<complex128>);

        CPPUNIT_TEST_SUITE_END();
    private:
        nxfile file;
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
    nxfield field = file.create_field<T>("array",shape);

    T write=T(0),read=T(0);
    
    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    CPPUNIT_ASSERT(field.shape<shape_t>()[0] == 3);
    CPPUNIT_ASSERT(field.shape<shape_t>()[1] == 4);

    //check selection parameters
    CPPUNIT_ASSERT(field(1,1).size()==1);
    CPPUNIT_ASSERT(field(1,1).shape<shape_t>().size()==0);
    CPPUNIT_ASSERT(field(1,1).rank()==0);

    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    CPPUNIT_ASSERT(field.shape<shape_t>()[0] == 3);
    CPPUNIT_ASSERT(field.shape<shape_t>()[1] == 4);


    for(size_t i=1;i<shape[0];i++)
    {
        for(size_t j=0;j<shape[1];j++)
        {
            write = T(i*j);
            read = T(0);
            CPPUNIT_ASSERT(field(i,j).size()==1);
            field(i,j).write(write);
            field(i,j).read(read);
            check_equality(read,write);
        }
    }

    CPPUNIT_ASSERT_THROW(field(slice(1,3)).write(write),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(field(slice(0,4)).read(read),shape_mismatch_error);
}

//-----------------------------------------------------------------------------
//testting to write to an array selection
template<typename T> void NXSelectionTest::test_array_selection()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t shape{3,4};
    nxfield field = file.create_field<T>("array",shape);

    darray<T> write(shape_t({3})),read(shape_t({3}));
    std::fill(write.begin(),write.end(),T(0));
    std::fill(read.begin(),read.end(),T(0));

    for(size_t j=0;j<shape[1];j++)
    {
        std::fill(write.begin(),write.end(),T(j));
        std::fill(read.begin(),read.end(),T(0));
        
        field(slice(0,3),j).write(write);
        field(slice(0,3),j).read(read);

        for(size_t i=0;i<write.size();i++) check_equality(read[i],write[i]);
    }

    CPPUNIT_ASSERT_THROW(field(slice(1,3),0).write(write),shape_mismatch_error);
    dbuffer<T> rbuff(2);
    CPPUNIT_ASSERT_THROW(field(slice(0,3),0).read(rbuff),size_mismatch_error);
    rbuff.free();
    CPPUNIT_ASSERT_THROW(field(slice(0,3),0).read(rbuff),memory_not_allocated_error);
}

