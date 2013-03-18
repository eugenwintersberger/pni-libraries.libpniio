/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *
 * Created on: Jan 31, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<initializer_list>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include "../src/h5/H5Selection.hpp"
#include "../src/h5/H5Dataset.hpp"
#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"

#include "TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;



class H5SelectionTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5SelectionTest);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_setup);
        CPPUNIT_TEST(test_write_simple_types);
        CPPUNIT_TEST(test_write_scalar);
        CPPUNIT_TEST(test_write_array);
        CPPUNIT_TEST(test_write_buffer);
        CPPUNIT_TEST(test_read_simple_types);
        CPPUNIT_TEST(test_read_scalar);
        CPPUNIT_TEST(test_read_buffer);
        CPPUNIT_TEST(test_read_array);
        //testing selections on a non-extendible
        //multidimensional dataset using sinel 
        //scalar values
        CPPUNIT_TEST(test_io_simple_no_ext<UInt8>);
        CPPUNIT_TEST(test_io_simple_no_ext<Int8>);
        CPPUNIT_TEST(test_io_simple_no_ext<UInt16>);
        CPPUNIT_TEST(test_io_simple_no_ext<Int16>);
        CPPUNIT_TEST(test_io_simple_no_ext<UInt32>);
        CPPUNIT_TEST(test_io_simple_no_ext<Int32>);
        CPPUNIT_TEST(test_io_simple_no_ext<UInt64>);
        CPPUNIT_TEST(test_io_simple_no_ext<Int64>);
        CPPUNIT_TEST(test_io_simple_no_ext<Float32>);
        CPPUNIT_TEST(test_io_simple_no_ext<Float64>);
        CPPUNIT_TEST(test_io_simple_no_ext<Float128>);
        CPPUNIT_TEST(test_io_simple_no_ext<Complex32>);
        CPPUNIT_TEST(test_io_simple_no_ext<Complex64>);
        CPPUNIT_TEST(test_io_simple_no_ext<Complex128>);
        CPPUNIT_TEST(test_io_simple_no_ext<String>);
        CPPUNIT_TEST(test_io_simple_no_ext<Binary>);
        //testing selections on a non-extendible
        //multidimensional dataset using scalar
        //objects (this is only useful for numerical 
        //values);a
        CPPUNIT_TEST(test_scalar_selection<UInt8>);
        //testing partial IO using buffers on a fixed
        //size dataset using numerical and binary data
        //in connection with a buffer object
        CPPUNIT_TEST(test_array_selection<UInt8>);
        //testing partial IO using an array on a fixed
        //size dataset using numerical data only
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file;
        shape_t _shape;
        shape_t _chunk;
        H5Dataset _dset;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_setup();
        template<typename T> void test_scalar_selection();
        template<typename T> void test_array_selection();

};

//------------------------------------------------------------------------------
template<typename T> void H5SelectionTest::test_scalar_selection()
{
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    shape_t s{3,5};
    H5Dataspace space(s);

    //create a simple not extensible scalar dataset
    H5Dataset dset("dataset",_file,type,space);
    H5Selection sel = dset.selection();
        
    T write,read;
    init_values(write,read);
#ifdef INITLISTBUG
    CPPUNIT_ASSERT_NO_THROW(sel.stride(0,1));
    CPPUNIT_ASSERT_NO_THROW(sel.stride(1,1));
    CPPUNIT_ASSERT_NO_THROW(sel.count(0,1));
    CPPUNIT_ASSERT_NO_THROW(sel.count(1,1));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
    CPPUNIT_ASSERT_NO_THROW(sel.stride({1,1}));
    CPPUNIT_ASSERT_NO_THROW(sel.count({1,1}));
    CPPUNIT_ASSERT_NO_THROW(sel.offset({0,0}));
#endif

    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
#ifdef INITLISTBUG
            CPPUNIT_ASSERT_NO_THROW(sel.offset(0,i));
            CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
#endif
            CPPUNIT_ASSERT_NO_THROW(sel.write(write));
        }
    }
    
    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
#ifdef INITLISTBUG
            CPPUNIT_ASSERT_NO_THROW(sel.offset(0,i));
            CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
#endif
            CPPUNIT_ASSERT_NO_THROW(sel.read(read));
            compare_values(read,write);
        }
    }

}

//------------------------------------------------------------------------------
template<typename T> void H5SelectionTest::test_io_scalar_no_ext()
{
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    size_t nx = 3, ny = 5;
    H5Dataspace space({nx,ny});

    //create a simple not extensible scalar dataset
    H5Dataset dset("scalar",_file,type,space);
    H5Selection sel = dset.selection();
        
    scalar<T> write,read;
    init_values(write,read);
#ifdef INITLISTBUG
    CPPUNIT_ASSERT_NO_THROW(sel.count(0,1));
    CPPUNIT_ASSERT_NO_THROW(sel.count(1,1));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
    CPPUNIT_ASSERT_NO_THROW(sel.count({1,1}));
    CPPUNIT_ASSERT_NO_THROW(sel.offset({0,0}));
#endif

    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
#ifdef INITLISTBUG
            CPPUNIT_ASSERT_NO_THROW(sel.offset(0,i));
            CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
#endif
            CPPUNIT_ASSERT_NO_THROW(sel.write(write));
        }
    }
    
    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
#ifdef INITLISTBUG
            CPPUNIT_ASSERT_NO_THROW(sel.offset(0,i));
            CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
#endif
            CPPUNIT_ASSERT_NO_THROW(sel.read(read));
            compare_values(read,write);
        }
    }
}

//-----------------------------------------------------------------------------
template<typename T> void H5SelectionTest::test_io_buffer_no_ext()
{
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    size_t nx = 3, ny = 5;
    H5Dataspace space({nx,ny});

    //create a simple not extensible scalar dataset
    H5Dataset dset("scalar",_file,type,space);
    H5Selection sel = dset.selection();
        
    dbuffer<T> write(3),read(3);
    init_values(write,read);
#ifdef INITLISTBUG
    CPPUNIT_ASSERT_NO_THROW(sel.count(0,3));
    CPPUNIT_ASSERT_NO_THROW(sel.count(1,1));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
    CPPUNIT_ASSERT_NO_THROW(sel.count({3,1}));
    CPPUNIT_ASSERT_NO_THROW(sel.offset({0,0}));
#endif

    //write loop
    for(size_t j=0;j<ny;j++){
        write = T(j);
#ifdef INITLISTBUG
        CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
        CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
        CPPUNIT_ASSERT_NO_THROW(sel.offset({0,j}));
#endif
        CPPUNIT_ASSERT_NO_THROW(sel.write(write));
    }
    
    //write loop
    for(size_t j=0;j<ny;j++){
#ifdef INITLISTBUG
        CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
        CPPUNIT_ASSERT_NO_THROW(sel.offset(1,j));
#else
        CPPUNIT_ASSERT_NO_THROW(sel.offset({0,j}));
#endif
        CPPUNIT_ASSERT_NO_THROW(sel.read(read));
        for(size_t i = 0;i<read.size();i++){
            compare_values(read[i],T(j));
        }
    }
}

//------------------------------------------------------------------------------
template<typename T> void H5SelectionTest::test_io_array_no_ext()
{
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    size_t nx = 3, ny = 5;
    H5Dataspace space({nx,ny});

    //create a simple not extensible scalar dataset
    H5Dataset dset("scalar",_file,type,space);
    H5Selection sel = dset.selection();
       
    shape_t s = {5};
    auto write = ArrayFactory<T,Buffer>::create(s);
    write.name("write");write.unit("a.u");write.description("write data");
    auto read = ArrayFactory<T,Buffer>::create(s);
    read.name("read"); read.unit("a.u"); read.description("read data");
    init_values(write,read);
#ifdef INITLISTBUG
    CPPUNIT_ASSERT_NO_THROW(sel.count(0,1));
    CPPUNIT_ASSERT_NO_THROW(sel.count(1,5));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(0,0));
    CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
    CPPUNIT_ASSERT_NO_THROW(sel.count({1,5}));
    CPPUNIT_ASSERT_NO_THROW(sel.offset({0,0}));
#endif

    //write loop
    for(size_t j=0;j<nx;j++){
        write = T(j);
#ifdef INITLISTBUG
        CPPUNIT_ASSERT_NO_THROW(sel.offset(0,j));
        CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
        CPPUNIT_ASSERT_NO_THROW(sel.offset({j,0}));
#endif
        CPPUNIT_ASSERT_NO_THROW(sel.write(write));
    }
    
    //write loop
    for(size_t j=0;j<nx;j++){
#ifdef INITLISTBUG
        CPPUNIT_ASSERT_NO_THROW(sel.offset(0,j));
        CPPUNIT_ASSERT_NO_THROW(sel.offset(1,0));
#else
        CPPUNIT_ASSERT_NO_THROW(sel.offset({j,0}));
#endif
        CPPUNIT_ASSERT_NO_THROW(sel.read(read));
        write = j;
        CPPUNIT_ASSERT( write == read);
    }
}

