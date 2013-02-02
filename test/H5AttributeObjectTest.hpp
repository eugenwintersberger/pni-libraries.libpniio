
#pragma once

extern "C" {
#include <hdf5.h>
}

#include "common.hpp"

#include <pni/core/arrays.hpp>
#include <pni/io/nx/h5/H5AttributeObject.hpp>



/*!
\ingroup test_suites
\brief testing attribute object behavior

Testing the behavior of instances of H5AttributeObject. 
*/
class H5AttributeObjectTest:public CppUnit::TestFixture
{
        //registering tests for this test suite
        CPPUNIT_TEST_SUITE(H5AttributeObjectTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_destruction);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST(test_inquery);
        
        CPPUNIT_TEST(test_attribute_open);
        //scalar attribute creation tests
        CPPUNIT_TEST(test_scalar_attribute_create<uint8>);
        CPPUNIT_TEST(test_scalar_attribute_create<int8>);
        CPPUNIT_TEST(test_scalar_attribute_create<uint16>);
        CPPUNIT_TEST(test_scalar_attribute_create<int16>);
        CPPUNIT_TEST(test_scalar_attribute_create<uint32>);
        CPPUNIT_TEST(test_scalar_attribute_create<int32>);
        CPPUNIT_TEST(test_scalar_attribute_create<uint64>);
        CPPUNIT_TEST(test_scalar_attribute_create<int64>);

        CPPUNIT_TEST(test_scalar_attribute_create<float32>);
        CPPUNIT_TEST(test_scalar_attribute_create<float64>);
        CPPUNIT_TEST(test_scalar_attribute_create<float128>);
        
        CPPUNIT_TEST(test_scalar_attribute_create<complex32>);
        CPPUNIT_TEST(test_scalar_attribute_create<complex64>);
        CPPUNIT_TEST(test_scalar_attribute_create<complex128>);

        CPPUNIT_TEST(test_scalar_attribute_create<string>);
        CPPUNIT_TEST(test_scalar_attribute_create<binary>);
        CPPUNIT_TEST(test_scalar_attribute_create<bool>);

        //array attribute creation tests
        CPPUNIT_TEST(test_array_attribute_create<uint8>);
        CPPUNIT_TEST(test_array_attribute_create<int8>);
        CPPUNIT_TEST(test_array_attribute_create<uint16>);
        CPPUNIT_TEST(test_array_attribute_create<int16>);
        CPPUNIT_TEST(test_array_attribute_create<uint32>);
        CPPUNIT_TEST(test_array_attribute_create<int32>);
        CPPUNIT_TEST(test_array_attribute_create<uint64>);
        CPPUNIT_TEST(test_array_attribute_create<int64>);

        CPPUNIT_TEST(test_array_attribute_create<float32>);
        CPPUNIT_TEST(test_array_attribute_create<float64>);
        CPPUNIT_TEST(test_array_attribute_create<float128>);
        
        CPPUNIT_TEST(test_array_attribute_create<complex32>);
        CPPUNIT_TEST(test_array_attribute_create<complex64>);
        CPPUNIT_TEST(test_array_attribute_create<complex128>);

        CPPUNIT_TEST(test_array_attribute_create<string>);
        CPPUNIT_TEST(test_array_attribute_create<binary>);
        CPPUNIT_TEST(test_array_attribute_create<bool>);
        CPPUNIT_TEST_SUITE_END();
    private:
        //-------------------local private members-----------------------------
        hid_t file;      //!< HDF5 file 
        hid_t group;     //!< HDF5 group
        hid_t type;      //!< HDF5 type 
        hid_t dataspace; //!< HDF5 dataspace
        hid_t dataset;   //!< HDF5 dataset

        //-----------------------local types-----------------------------------
        /*!
        \brief private test class

        This test class provides a type which derives from H5AttributeObject.
        The reason for this is that H5AttributeObject cannot be constructed
        directly as its constructors are protected or private.
        */
        class H5TestObject:public H5AttributeObject
        {
            public:
                //! constructor
                H5TestObject(hid_t id):H5AttributeObject(id) {};
        };

        //-------------------private methods-----------------------------------
        /*!
        \brief create a group

        Function creates a group and returns the groups HDF5 ID. The function
        performs no error checking.
        \param pid HDF5 ID of the parent object
        \param name string object with the groups name
        \return HDF5 ID of the group
        */
        hid_t create_group(hid_t pid,const string &name) const;

        //---------------------------------------------------------------------
        /*! 
        \brief creates local instance 

        This function is used to test the destructor of an H5AttributeObject.
        It creates a local instance of H5AttributeObject using the HDF5 ID
        passed as an argument to this function. Thus it takes over the ownership
        of the HDF5 object belonging to the id. When the function looses scope
        the H5AttributeObject gets destroyed and thus the HDF5 object should be
        destroyed too. 
        \param id HDF5 object id
        */
        void local_function(hid_t id);

    public:
        //---------------------------------------------------------------------
        /*! 
        \brief setup method

        Called before each test.
        */
        void setUp();

        //---------------------------------------------------------------------
        /*! 
        \brief tear down method
        
        Called after each test.
        */
        void tearDown();

        //---------------------------------------------------------------------
        /*!
        \brief creation tests

        Test object constructors.
        */
        void test_creation();

        //---------------------------------------------------------------------
        /*! 
        \brief test assignment

        Test assignment operators
        */
        void test_assignment();

        //---------------------------------------------------------------------
        /*!
        \brief test destruction

        Test destruction of an H5AttributeObject. This test should ensure that
        with calling close or the destructor the object is really destroyed.
        */
        void test_destruction();

        //---------------------------------------------------------------------
        /*!
        \brief test comparison

        Test the comparison operators.
        */
        void test_comparison();

        //---------------------------------------------------------------------
        /*! 
        \brief test inquiry

        Test objects inquiry methods.
        */
        void test_inquery();

        //---------------------------------------------------------------------
        /*! 
        \brief test opening attributes

        Test opening existing attributes.
        */
        void test_attribute_open();

        //---------------------------------------------------------------------
        /*!
        \brief test scalar attribute creation

        Test for scalar attribute creation.
        \tparam T data type of the attribute
        */
        template<typename T> void test_scalar_attribute_create();

        //---------------------------------------------------------------------
        /*!
        \brief test array attribute creation

        Test for array attribute creation
        \tparam T data type of the array attribute
        */
        template<typename T> void test_array_attribute_create();
};

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeObjectTest::test_scalar_attribute_create()
{
    PRINT_TEST_FUNCTION_SIG;
    
    H5AttributeObject o(H5TestObject(create_group(file,"group")));

    H5Attribute a;

    CPPUNIT_ASSERT_NO_THROW(o.attr<T>("a1"));
    //test invalid creation
    CPPUNIT_ASSERT_THROW(o.attr<T>("a1"),H5AttributeError);
    //but
    CPPUNIT_ASSERT_NO_THROW(o.attr<T>("a1",true));
}

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeObjectTest::test_array_attribute_create()
{
    PRINT_TEST_FUNCTION_SIG;

    H5AttributeObject o(H5TestObject(create_group(file,"group")));

    shape_t s{10,3};

    CPPUNIT_ASSERT_NO_THROW(o.attr<T>("a1",s));
    CPPUNIT_ASSERT_THROW(o.attr<T>("a1",s),H5AttributeError);
    CPPUNIT_ASSERT_NO_THROW(o.attr<T>("a1",s,true));
}

