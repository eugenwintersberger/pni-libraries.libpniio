#include "H5DatatypeTest.hpp"
#include <boost/current_function.hpp>
#include "../src/h5/H5DatatypeFactory.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5DatatypeTest);


void H5DatatypeTest::setUp(){
}

void H5DatatypeTest::tearDown(){
}

void H5DatatypeTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Datatype t1;

    //per default no type is created
    CPPUNIT_ASSERT(!t1.is_valid());

    H5Datatype t2 = H5DatatypeFactory::create_type<UInt8>();
    CPPUNIT_ASSERT(t2.is_valid());

    //create a datatype using a type and the factory method
    H5Datatype t3 = H5DatatypeFactory::create_type<Float32>();
    
    //copy constructor
    H5Datatype t4 = t2;
    CPPUNIT_ASSERT(t4.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    CPPUNIT_ASSERT(t2.type_id() == t4.type_id());

    //move constructor
    H5Datatype t5 = std::move(t2);
    CPPUNIT_ASSERT(t5.is_valid());
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t5.type_id() == TypeID::UINT8);
    

}

void H5DatatypeTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Datatype t1 = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    CPPUNIT_ASSERT(t1.is_valid());
    H5Datatype t2;
    CPPUNIT_ASSERT(!t2.is_valid());

    //testing copy assignment
    t2 = t1;
    CPPUNIT_ASSERT(t2.is_valid());
    CPPUNIT_ASSERT(t1.is_valid());
    CPPUNIT_ASSERT(t1.type_id() == t2.type_id());

    
    H5Datatype t3;
    CPPUNIT_ASSERT(!t3.is_valid());
    
    t3 = std::move(t2);
    CPPUNIT_ASSERT(t3.is_valid());
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t3.type_id() == t1.type_id());

}

void H5DatatypeTest::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Datatype type;

    type = H5DatatypeFactory::create_type<TypeID::UINT8>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT8);
    type = H5DatatypeFactory::create_type<TypeID::INT8>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT8);
    
    type = H5DatatypeFactory::create_type<TypeID::INT16>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT16);
    type = H5DatatypeFactory::create_type<TypeID::UINT16>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT16);
    
    type = H5DatatypeFactory::create_type<TypeID::INT32>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT32);
    type = H5DatatypeFactory::create_type<TypeID::UINT32>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT32);
    
    type = H5DatatypeFactory::create_type<TypeID::INT64>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT64);
    type = H5DatatypeFactory::create_type<TypeID::UINT64>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT64);
    
    type = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT32);
    
    type = H5DatatypeFactory::create_type<TypeID::FLOAT64>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT64);
    
    type = H5DatatypeFactory::create_type<TypeID::FLOAT128>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT128);
    
    type = H5DatatypeFactory::create_type<TypeID::COMPLEX32>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX32);
    
    type = H5DatatypeFactory::create_type<TypeID::COMPLEX64>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX64);
    
    type = H5DatatypeFactory::create_type<TypeID::COMPLEX128>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX128);

    type = H5DatatypeFactory::create_type<TypeID::STRING>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::STRING);

    type = H5DatatypeFactory::create_type<TypeID::BINARY>();
    CPPUNIT_ASSERT(type.type_id() == TypeID::BINARY);

}

void H5DatatypeTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Datatype t1 = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    H5Datatype t2 = H5DatatypeFactory::create_type<TypeID::INT32>();

    CPPUNIT_ASSERT(t1 != t2);
    CPPUNIT_ASSERT(!(t1 == t2));

    t2 = H5DatatypeFactory::create_type<TypeID::FLOAT32>();
    CPPUNIT_ASSERT(!(t1 != t2));
    CPPUNIT_ASSERT(t1 == t2);
}
