
#ifndef __H5GROUPTEST_HPP__
#define __H5GROUPTEST_HPP__


extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5GroupTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5GroupTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_objectcreation);
        CPPUNIT_TEST(test_openobjects);
        CPPUNIT_TEST(test_attributes);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File file;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_objectcreation();
        void test_openobjects();
        void test_attributes();
    
};

#endif
