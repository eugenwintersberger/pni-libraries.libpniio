#pragma once

extern "C"{
#include <hdf5.h>
}

#include<vector>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/io/nx/h5/H5Dataspace.hpp>
#include <pni/io/nx/h5/H5Exceptions.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5DataspaceTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5DataspaceTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef std::vector<size_t> shape_t;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
        void test_resize();
    
};

