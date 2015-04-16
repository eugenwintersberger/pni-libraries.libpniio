
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/core/arrays.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace pni::core;
using namespace pni::io::nx;

class scalar_attribute_test_int32 : public CppUnit::TestFixture
{ 
    private:
        CPPUNIT_TEST_SUITE(scalar_attribute_test_int32);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_create_object);
        CPPUNIT_TEST_SUITE_END();

        xml::node root;
        xml::node child;

        h5::nxfile file; 
        h5::nxobject group;

    public:
        void setUp();
        void tearDown();
       
        void test_inquery();
        void test_create_object();
};
