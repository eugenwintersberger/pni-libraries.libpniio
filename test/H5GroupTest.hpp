
#pragma once


extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5GroupTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5GroupTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_openobjects);
        CPPUNIT_TEST(test_linking);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST(test_parent);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File file;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_openobjects();
        void test_attributes();
        void test_attribute_manipulation();
        void test_linking();
        void test_comparison();
        void test_parent();
    
};
