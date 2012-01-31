#ifndef __H5DATASETTEST_HPP__
#define __H5DATASETTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Types.hpp>
#include <pni/utils/Buffer.hpp>
#include <pni/utils/Shape.hpp>

#include "../src/h5/H5Selection.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5SelectionTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5SelectionTest);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_setup);
        CPPUNIT_TEST_SUITE_END();
    private:
        Shape s;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_setup();

};

#endif
