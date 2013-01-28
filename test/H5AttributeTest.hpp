
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

        CPPUNIT_TEST(test_scalar_attribute<uint8>);
        CPPUNIT_TEST(test_scalar_attribute<int8>);
        CPPUNIT_TEST(test_scalar_attribute<uint16>);
        CPPUNIT_TEST(test_scalar_attribute<int16>);
        CPPUNIT_TEST(test_scalar_attribute<uint32>);
        CPPUNIT_TEST(test_scalar_attribute<int32>);
        CPPUNIT_TEST(test_scalar_attribute<uint64>);
        CPPUNIT_TEST(test_scalar_attribute<int64>);
        CPPUNIT_TEST(test_scalar_attribute<float32>);
        CPPUNIT_TEST(test_scalar_attribute<float64>);
        CPPUNIT_TEST(test_scalar_attribute<float128>);
        CPPUNIT_TEST(test_scalar_attribute<complex32>);
        CPPUNIT_TEST(test_scalar_attribute<complex64>);
        CPPUNIT_TEST(test_scalar_attribute<complex128>);
        CPPUNIT_TEST(test_scalar_attribute<string>);
        CPPUNIT_TEST(test_scalar_attribute<bool>);

        CPPUNIT_TEST(test_array_attribute<uint8>);
        CPPUNIT_TEST(test_array_attribute<int8>);
        CPPUNIT_TEST(test_array_attribute<uint16>);
        CPPUNIT_TEST(test_array_attribute<int16>);
        CPPUNIT_TEST(test_array_attribute<uint32>);
        CPPUNIT_TEST(test_array_attribute<int32>);
        CPPUNIT_TEST(test_array_attribute<uint64>);
        CPPUNIT_TEST(test_array_attribute<int64>);
        CPPUNIT_TEST(test_array_attribute<float32>);
        CPPUNIT_TEST(test_array_attribute<float64>);
        CPPUNIT_TEST(test_array_attribute<float128>);
        CPPUNIT_TEST(test_array_attribute<complex32>);
        CPPUNIT_TEST(test_array_attribute<complex64>);
        CPPUNIT_TEST(test_array_attribute<complex128>);
        CPPUNIT_TEST(test_array_attribute<string>);
        CPPUNIT_TEST(test_array_attribute<bool>);
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

