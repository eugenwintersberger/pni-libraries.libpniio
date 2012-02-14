#ifndef __H5DATASETTEST_HPP__
#define __H5DATASETTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Types.hpp>
#include <pni/utils/Buffer.hpp>
#include <pni/utils/Shape.hpp>

#include "../src/h5/H5Selection.hpp"
#include "../src/h5/H5Dataset.hpp"
#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"

#include "TestHelpers.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;



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
        CPPUNIT_TEST(test_io_simple_no_ext<UInt8>);
        /*
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
        */
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file;
        Shape _shape;
        Shape _chunk;
        H5Dataset _dset;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_setup();
        void test_write_simple_types();
        void test_write_scalar();
        void test_write_array();
        void test_write_buffer();
        void test_read_simple_types();
        void test_read_scalar();
        void test_read_buffer();
        void test_read_array();
        template<typename T> void test_io_simple_no_ext();
        template<typename T> void test_io_scalar_no_ext();
        template<typename T> void test_io_buffer_no_ext();
        template<typename T> void test_io_array_no_ext();

};

template<typename T> void H5SelectionTest::test_io_simple_no_ext()
{
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    size_t nx = 3, ny = 5;
    H5Dataspace space({nx,ny});

    //create a simple not extensible scalar dataset
    H5Dataset dset("scalar",_file,type,space);
    H5Selection sel = dset.selection();
        
    T write,read;
    init_values(write,read);
    CPPUNIT_ASSERT_NO_THROW(sel.count({1,1}));
    CPPUNIT_ASSERT_NO_THROW(sel.offset({0,0}));

    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
            CPPUNIT_ASSERT_NO_THROW(sel.write(write));
        }
    }
    
    //write loop
    for(size_t i=0;i<nx; i++){
        for(size_t j=0;j<ny;j++){
            CPPUNIT_ASSERT_NO_THROW(sel.offset({i,j}));
            CPPUNIT_ASSERT_NO_THROW(sel.read(read));
            compare_values(read,write);
        }
    }

}

template<typename T> void H5SelectionTest::test_io_scalar_no_ext()
{

}

template<typename T> void H5SelectionTest::test_io_buffer_no_ext()
{

}

template<typename T> void H5SelectionTest::test_io_array_no_ext()
{

}

#endif
