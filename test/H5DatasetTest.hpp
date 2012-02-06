
#ifndef __H5DATASETTEST_HPP__
#define __H5DATASETTEST_HPP__

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Array.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"
#include "../src/h5/H5Dataset.hpp"
#include "../src/h5/H5Selection.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5DatasetTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5DatasetTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST(test_write_simple_types);
        CPPUNIT_TEST(test_write_scalar);
        CPPUNIT_TEST(test_write_array);
        CPPUNIT_TEST(test_write_buffer);
        CPPUNIT_TEST(test_read_simple_types);
        CPPUNIT_TEST(test_read_array);
        CPPUNIT_TEST(test_read_buffer);
        CPPUNIT_TEST(test_read_scalar);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file;
        H5Group _group;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
        void test_resize();
        void test_write_simple_types();
        void test_write_scalar();
        void test_write_array();
        void test_write_buffer();
        void test_read_simple_types();
        void test_read_array();
        void test_read_buffer();
        void test_read_scalar();
};

#endif
