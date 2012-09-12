
#ifndef __H5DATATYPETEST_HPP__
#define __H5DATATYPETEST_HPP__

extern "C"{
#include <hdf5.h>
}

#include<boost/current_function.hpp>
#include <pni/utils/Types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/h5/H5Datatype.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5DatatypeTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5DatatypeTest);
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
        void test_comparison();
        void test_global_factory();
       
    
};

#endif
