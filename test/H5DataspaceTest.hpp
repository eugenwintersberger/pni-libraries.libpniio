
#ifndef __H5DATASPACETEST_HPP__
#define __H5DATASPACETEST_HPP__

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Shape.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/h5/H5Dataspace.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5DataspaceTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5DataspaceTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
        void test_resize();
    
};

#endif
