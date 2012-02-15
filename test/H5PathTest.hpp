

#ifndef __H5PATHTEST_HPP__
#define __H5PATHTEST_HPP__


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Types.hpp>

#include "../src/h5/H5Path.hpp"

#include "TestHelpers.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;


class H5PathTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5PathTest);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_creation();
        

};
#endif 
