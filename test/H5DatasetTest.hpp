
#ifndef __H5DATASETTEST_HPP__
#define __H5DATASETTEST_HPP__

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Selection.hpp"

#include "EqualityCheck.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class H5DatasetTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(H5DatasetTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST(test_scalar_data<UInt8>);
        CPPUNIT_TEST(test_scalar_data<Int8>);
        CPPUNIT_TEST(test_scalar_data<UInt16>);
        CPPUNIT_TEST(test_scalar_data<Int16>);
        CPPUNIT_TEST(test_scalar_data<UInt32>);
        CPPUNIT_TEST(test_scalar_data<Int32>);
        CPPUNIT_TEST(test_scalar_data<UInt64>);
        CPPUNIT_TEST(test_scalar_data<Int64>);
        CPPUNIT_TEST(test_scalar_data<Float32>);
        CPPUNIT_TEST(test_scalar_data<Float64>);
        CPPUNIT_TEST(test_scalar_data<Float128>);
        CPPUNIT_TEST(test_scalar_data<Complex32>);
        CPPUNIT_TEST(test_scalar_data<Complex64>);
        CPPUNIT_TEST(test_scalar_data<Complex128>);
        CPPUNIT_TEST(test_scalar_data<Binary>);

        CPPUNIT_TEST(test_array_data<UInt8>);
        CPPUNIT_TEST(test_array_data<Int8>);
        CPPUNIT_TEST(test_array_data<UInt16>);
        CPPUNIT_TEST(test_array_data<Int16>);
        CPPUNIT_TEST(test_array_data<UInt32>);
        CPPUNIT_TEST(test_array_data<Int32>);
        CPPUNIT_TEST(test_array_data<UInt64>);
        CPPUNIT_TEST(test_array_data<Int64>);
        CPPUNIT_TEST(test_array_data<Float32>);
        CPPUNIT_TEST(test_array_data<Float64>);
        CPPUNIT_TEST(test_array_data<Float128>);
        CPPUNIT_TEST(test_array_data<Complex32>);
        CPPUNIT_TEST(test_array_data<Complex64>);
        CPPUNIT_TEST(test_array_data<Complex128>);
        CPPUNIT_TEST(test_array_data<Binary>);
        CPPUNIT_TEST(test_linking);
        CPPUNIT_TEST_SUITE_END();
    private:
        H5File _file;
        H5Group _group;
    public:
        void setUp();
        void tearDown();
        void test_creation();
        void test_assignment();
        void test_inquery();
        void test_resize();
        template<typename T> void test_scalar_data();
        template<typename T> void test_array_data();
        void test_linking();
};

//-----------------------------------------------------------------------------
template<typename T> void H5DatasetTest::test_scalar_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //start with a scalar dataset
    H5Datatype type = H5DatatypeFactory::create_type<T>();
    H5Dataset scalar_ds("scalar_dataset",_group,type,H5Dataspace());
    T write = T(1);
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(&write));
    T read;
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.read(&read));
    check_equality(read,write);
}

//-----------------------------------------------------------------------------
template<typename T> void H5DatasetTest::test_array_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Datatype type=H5DatatypeFactory::create_type<T>();
    shape_t s{3,3};
    shape_t cs{1,3}; 
    H5Dataset ds("array_dataset",_group,type,H5Dataspace(s),cs);
    DArray<T> write(s);
    DArray<T> read(s);
    std::fill(write.begin(),write.end(),T(1));

    CPPUNIT_ASSERT_NO_THROW(ds.write(write.storage().ptr()));
    CPPUNIT_ASSERT_NO_THROW(ds.read(const_cast<T*>(read.storage().ptr())));
    
    //check equality
    for(size_t i=0;i<write.size();i++) check_equality(write[i],read[i]);
}

#endif
