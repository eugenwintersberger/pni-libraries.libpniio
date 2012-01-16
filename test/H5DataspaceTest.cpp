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

    //check copy process
    H5Dataspace s3 = s2;
    CPPUNIT_ASSERT(s3.is_valid());
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s3.is_scalar());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.shape() == s3.shape());
    
    
    //check move constructor
    H5Dataspace s4 = std::move(s2);
    CPPUNIT_ASSERT(s4.is_valid());
    CPPUNIT_ASSERT(!s2.is_valid());
    CPPUNIT_ASSERT(s4.shape() == s3.shape());


    Shape ms(s.rank());
    for(size_t i=0; i<ms.rank(); i++) ms.dim(i,100);
    H5Dataspace s6(s,ms);
    CPPUNIT_ASSERT(s6.is_valid());
    CPPUNIT_ASSERT(!s6.is_scalar());
    for(size_t i=0;i<s6.rank();i++){
        CPPUNIT_ASSERT(s6.dim(i) == s[i]);
        CPPUNIT_ASSERT(s6.max_dim(i) == ms[i]);
    }

}

void H5DataspaceTest::test_assignment(){
    std::cout<<"void H5Dataspace::test_assignment()---------------------------";
    std::cout<<std::endl;

    H5Dataspace s1;

    Shape s(3);
    s.dim(0,10);s.dim(1,3);s.dim(2,45);

    //copy assignment
    s1 = H5Dataspace(s);
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(s1.shape() == s);

    //move assignment
    H5Dataspace s2;

    s2 = std::move(s1);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s1.is_valid());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.shape() == s);

}

void H5DataspaceTest::test_inquery(){
    Shape s(2);
    s.dim(1,100); s.dim(0,50);
    H5Dataspace s1(s);

    CPPUNIT_ASSERT(s1.shape() == s);
    CPPUNIT_ASSERT(s1.rank() == 2);
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s.size() == 50*100);

}

void H5DataspaceTest::test_resize(){
    H5Dataspace space;
    CPPUNIT_ASSERT(space.is_scalar());
    
    Shape s(3); s.dim(0,10); s.dim(1,4); s.dim(2,17);
    Shape ms(s);
    CPPUNIT_ASSERT_NO_THROW(space.resize(s));
    CPPUNIT_ASSERT(!space.is_scalar());
    CPPUNIT_ASSERT(space.shape() == s);

}
