
#ifndef __H5OBJECTTEST_HPP__
#define __H5OBJECTTEST_HPP__

extern "C" {
#include <hdf5.h>
}


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>
#include<pni/utils/Array.hpp>

#include "h5/H5AttributeObject.hpp"
#include "EqualityCheck.hpp"


using namespace pni::nx::h5;

//cannot construct an H5Object type directly so we need a small helper class
class H5TestObject:public H5AttributeObject
{
    public:
        H5TestObject(hid_t id):H5AttributeObject(id) {};
};

class H5AttributeObjectTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(H5AttributeObjectTest);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_destruction);
        CPPUNIT_TEST(test_comparison);
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
        CPPUNIT_TEST(test_string_attribute);
        
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
        template<typename T>
        void test_scalar_attribute();
        template<typename T>
        void test_array_attribute();
        void test_string_attribute();
        void test_inquery();
};

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeObjectTest::test_scalar_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5AttributeObject
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));

    H5Attribute a = o1.attr<T>("test1");
    CPPUNIT_ASSERT(a.is_valid());
    CPPUNIT_ASSERT(a.base().empty());
    CPPUNIT_ASSERT(a.path().empty());
    CPPUNIT_ASSERT(a.name() == "test1");
    CPPUNIT_ASSERT(a.rank() == 0);
    CPPUNIT_ASSERT(a.size() == 1);

    //write data
    T value = T(1);
    a.write(&value);
    //read data back and check equality
    T value2;
    a.read(&value2);
    check_equality(value,value2);

    //check overwrite
    CPPUNIT_ASSERT_THROW(o1.attr<T>("test1"),H5AttributeError);
    CPPUNIT_ASSERT_NO_THROW(o1.attr<T>("test1",true));
}

//-----------------------------------------------------------------------------
template<typename T> void H5AttributeObjectTest::test_array_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t s{10,20};
    DArray<T> a1(s);
    SArray<T,10,20> a2;

    std::fill(a1.begin(),a1.end(),T(2));

    H5AttributeObject
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));

    H5Attribute a = o1.attr<T>("test1",s);
    CPPUNIT_ASSERT(a.is_valid());
    CPPUNIT_ASSERT(a.base().empty());
    CPPUNIT_ASSERT(a.path().empty());
    CPPUNIT_ASSERT(a.name() == "test1");
    CPPUNIT_ASSERT(a.rank() == s.size());
    CPPUNIT_ASSERT(a.size() == 10*20);

    //write data
    a.write(a1.storage().ptr());
    //read data back
    a.read(const_cast<T*>(a2.storage().ptr()));

    //compare data
    for(size_t i=0;i<a1.size();i++) check_equality(a1[i],a2[i]);
    

}

#endif
