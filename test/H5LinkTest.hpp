#pragma once


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/Types.hpp>


#include "../src/h5/H5Link.hpp"
#include "../src/h5/H5File.hpp"
#include "../src/h5/H5Group.hpp"
#include "../src/h5/H5Dataspace.hpp"
#include "../src/h5/H5Datatype.hpp"
#include "../src/h5/H5DatatypeFactory.hpp"
#include "../src/h5/H5Dataset.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

class H5LinkTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5LinkTest);
        CPPUNIT_TEST(test_internal);
        CPPUNIT_TEST(test_external);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file1;
        H5File _file2;
    public:
        void setUp();
        void tearDown();
        void test_internal();
        void test_external();
};
