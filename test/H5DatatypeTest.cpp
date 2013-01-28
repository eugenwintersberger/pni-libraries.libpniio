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

    H5Datatype t2 = H5DatatypeFactory::create_type<uint8>();
    CPPUNIT_ASSERT(t2.is_valid());

    //create a datatype using a type and the factory method
    H5Datatype t3 = H5DatatypeFactory::create_type<float32>();
    
    //copy constructor
    H5Datatype t4 = t2;
    CPPUNIT_ASSERT(t4.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    CPPUNIT_ASSERT(t2.type_id() == t4.type_id());

    //move constructor
    H5Datatype t5 = std::move(t2);
    CPPUNIT_ASSERT(t5.is_valid());
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t5.type_id() == type_id_t::UINT8);
    

}

void H5DatatypeTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Datatype t1 = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();
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

    type = H5DatatypeFactory::create_type<type_id_t::UINT8>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::UINT8);
    type = H5DatatypeFactory::create_type<type_id_t::INT8>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::INT8);
    
    type = H5DatatypeFactory::create_type<type_id_t::INT16>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::INT16);
    type = H5DatatypeFactory::create_type<type_id_t::UINT16>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::UINT16);
    
    type = H5DatatypeFactory::create_type<type_id_t::INT32>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::INT32);
    type = H5DatatypeFactory::create_type<type_id_t::UINT32>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::UINT32);
    
    type = H5DatatypeFactory::create_type<type_id_t::INT64>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::INT64);
    type = H5DatatypeFactory::create_type<type_id_t::UINT64>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::UINT64);
    
    type = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::FLOAT32);
    
    type = H5DatatypeFactory::create_type<type_id_t::FLOAT64>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::FLOAT64);
    
    type = H5DatatypeFactory::create_type<type_id_t::FLOAT128>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::FLOAT128);
    
    type = H5DatatypeFactory::create_type<type_id_t::COMPLEX32>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::COMPLEX32);
    
    type = H5DatatypeFactory::create_type<type_id_t::COMPLEX64>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::COMPLEX64);
    
    type = H5DatatypeFactory::create_type<type_id_t::COMPLEX128>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::COMPLEX128);

    type = H5DatatypeFactory::create_type<type_id_t::STRING>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::STRING);

    type = H5DatatypeFactory::create_type<type_id_t::BINARY>();
    CPPUNIT_ASSERT(type.type_id() == type_id_t::BINARY);

    type = H5DatatypeFactory::create_type<type_id_t::BOOL>();
    std::cout<<type.type_id()<<std::endl;
    CPPUNIT_ASSERT(type.type_id() == type_id_t::BOOL);

}

void H5DatatypeTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Datatype t1 = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();
    H5Datatype t2 = H5DatatypeFactory::create_type<type_id_t::INT32>();

    CPPUNIT_ASSERT(t1 != t2);
    CPPUNIT_ASSERT(!(t1 == t2));

    t2 = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();
    CPPUNIT_ASSERT(!(t1 != t2));
    CPPUNIT_ASSERT(t1 == t2);
}

void H5DatatypeTest::test_global_factory()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(H5TFactory.get_type<bool>().type_id()==type_id_t::BOOL);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::BOOL>().type_id()==type_id_t::BOOL);

    CPPUNIT_ASSERT(H5TFactory.get_type<uint8>().type_id()==type_id_t::UINT8);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::UINT8>().type_id()==type_id_t::UINT8);
    CPPUNIT_ASSERT(H5TFactory.get_type<uint16>().type_id()==type_id_t::UINT16);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::UINT16>().type_id()==type_id_t::UINT16);
    CPPUNIT_ASSERT(H5TFactory.get_type<uint32>().type_id()==type_id_t::UINT32);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::UINT32>().type_id()==type_id_t::UINT32);
    CPPUNIT_ASSERT(H5TFactory.get_type<uint64>().type_id()==type_id_t::UINT64);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::UINT64>().type_id()==type_id_t::UINT64);

    CPPUNIT_ASSERT(H5TFactory.get_type<float32>().type_id()==type_id_t::FLOAT32);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::FLOAT32>().type_id()==type_id_t::FLOAT32);
    CPPUNIT_ASSERT(H5TFactory.get_type<float64>().type_id()==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::FLOAT64>().type_id()==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(H5TFactory.get_type<float128>().type_id()==type_id_t::FLOAT128);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::FLOAT128>().type_id()==type_id_t::FLOAT128);

    CPPUNIT_ASSERT(H5TFactory.get_type<complex32>().type_id()==type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::COMPLEX32>().type_id()==type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(H5TFactory.get_type<complex64>().type_id()==type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::COMPLEX64>().type_id()==type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(H5TFactory.get_type<complex128>().type_id()==type_id_t::COMPLEX128);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::COMPLEX128>().type_id()==type_id_t::COMPLEX128);

    CPPUNIT_ASSERT(H5TFactory.get_type<string>().type_id() == type_id_t::STRING);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::STRING>().type_id()==type_id_t::STRING);
    CPPUNIT_ASSERT(H5TFactory.get_type<binary>().type_id() == type_id_t::BINARY);
    CPPUNIT_ASSERT(H5TFactory.get_type<type_id_t::BINARY>().type_id()==type_id_t::BINARY);
}
