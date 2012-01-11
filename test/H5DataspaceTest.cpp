#include "H5DataspaceTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5DataspaceTest);


void H5DataspaceTest::setUp(){
}

void H5DataspaceTest::tearDown(){
}

void H5DataspaceTest::test_creation(){
    std::cout<<"void NXDataspaceTest::test_creation()-------------------------";
    std::cout<<std::endl;
    H5Dataspace s1;

    //per default a scalar data space is created
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.is_scalar());
    CPPUNIT_ASSERT(s1.rank()==0);

    //create a dataspace from a shape object
    Shape s(3);
    s.dim(0,10);s.dim(1,3);s.dim(2,45);

    H5Dataspace s2(s);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.rank() == s.rank());


}

void H5DataspaceTest::test_assignment(){

}

void H5DataspaceTest::test_inquery(){

}
