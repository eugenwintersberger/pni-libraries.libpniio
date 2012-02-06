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

};

#endif
