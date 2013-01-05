
#pragma once


extern "C"{
#include <hdf5.h>
}

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "h5/H5File.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5FileTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5FileTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
};
