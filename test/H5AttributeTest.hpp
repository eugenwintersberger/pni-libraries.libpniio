
#pragma once

extern "C" {
#include <hdf5.h>
}

#include "common.hpp"
#include "data.hpp"

#include<pni/core/arrays.hpp>

#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"


/*!
\ingroup test_suites
\brief test H5Attribute objects

Testing instances of H5Attribute.
*/
class H5AttributeTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5AttributeTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);

        CPPUNIT_TEST(test_scalar_attribute<UInt8>);
        CPPUNIT_TEST(test_scalar_attribute<Int8>);
        CPPUNIT_TEST(test_scalar_attribute<UInt16>);
        CPPUNIT_TEST(test_scalar_attribute<Int16>);
        CPPUNIT_TEST(test_scalar_attribute<UInt32>);
        CPPUNIT_TEST(test_scalar_attribute<Int32>);
        CPPUNIT_TEST(test_scalar_attribute<UInt64>);
        CPPUNIT_TEST(test_scalar_attribute<Int64>);
        CPPUNIT_TEST(test_scalar_attribute<Float32>);
        CPPUNIT_TEST(test_scalar_attribute<Float64>);
        CPPUNIT_TEST(test_scalar_attribute<Float128>);
        CPPUNIT_TEST(test_scalar_attribute<Complex32>);
        CPPUNIT_TEST(test_scalar_attribute<Complex64>);
        CPPUNIT_TEST(test_scalar_attribute<Complex128>);
        CPPUNIT_TEST(test_scalar_attribute<String>);
        CPPUNIT_TEST(test_scalar_attribute<Bool>);

        CPPUNIT_TEST(test_array_attribute<UInt8>);
        CPPUNIT_TEST(test_array_attribute<Int8>);
        CPPUNIT_TEST(test_array_attribute<UInt16>);
        CPPUNIT_TEST(test_array_attribute<Int16>);
        CPPUNIT_TEST(test_array_attribute<UInt32>);
        CPPUNIT_TEST(test_array_attribute<Int32>);
        CPPUNIT_TEST(test_array_attribute<UInt64>);
        CPPUNIT_TEST(test_array_attribute<Int64>);
        CPPUNIT_TEST(test_array_attribute<Float32>);
        CPPUNIT_TEST(test_array_attribute<Float64>);
        CPPUNIT_TEST(test_array_attribute<Float128>);
        CPPUNIT_TEST(test_array_attribute<Complex32>);
        CPPUNIT_TEST(test_array_attribute<Complex64>);
        CPPUNIT_TEST(test_array_attribute<Complex128>);
        CPPUNIT_TEST(test_array_attribute<String>);
        CPPUNIT_TEST(test_array_attribute<Bool>);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File file;   //!< file object
        H5Group group; //!< group object

    public:
        //---------------------------------------------------------------------
        /*!
        \brief setting up the test

        Run before each test.
        */
        void setUp();

        //---------------------------------------------------------------------
        /*!
        \brief tear down the test

        Run after each test.
        */
        void tearDown();

        //---------------------------------------------------------------------
        //! test attribute constructors
        void test_creation();

        //---------------------------------------------------------------------
        //! testing assignment operators
        void test_assignment();

        //---------------------------------------------------------------------
        //! testing comparision operators
        void test_comparison();

        //---------------------------------------------------------------------
        //! testing types inquery methods
        void test_inquery();

        template<typename T> void test_scalar_attribute();
        template<typename T> void test_array_attribute();
};

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeTest::test_scalar_attribute()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a = group.attr<T>("a1");

    //write data
    auto write = create_scalar_data<T>();
    a.write(&write);
    //read data back and check equality
    T read;
    a.read(&read);
    check_equality(write,read);
}

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeTest::test_array_attribute()
{
    PRINT_TEST_FUNCTION_SIG;

    shape_t s{10,20};
    darray<T> write(s);
    sarray<T,10,20> read;

    std::vector<T> b = create_array_data<T>(write.size());
    std::copy(b.begin(),b.end(),write.begin());
    
    H5Attribute a = group.attr<T>("a1",s);
    //write data
    a.write(write.storage().ptr());
    //read data back
    a.read(const_cast<T*>(read.storage().ptr()));

    //compare data
    for(size_t i=0;i<a.size();i++) check_equality(read[i],write[i]);
}

