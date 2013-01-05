
#pragma once

extern "C" {
#include <hdf5.h>
}


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "h5/H5NamedObject.hpp"

using namespace pni::io::nx::h5;

//cannot construct an H5Object type directly so we need a small helper class
class H5TestObject:public H5NamedObject
{
    public:
        H5TestObject(hid_t id):H5NamedObject(id) {};
};

class H5NamedObjectTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5NamedObjectTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_destruction);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST_SUITE_END();
    private:
        hid_t file;
        hid_t group;
        hid_t type;
        hid_t dataspace;
        hid_t dataset;

    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_destruction();
        void test_comparison();
};

