//implementation of H5Selection tests

#include "H5SelectionTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5SelectionTest);

//-----------------------------------------------------------------------------
void H5SelectionTest::setUp(){
    s.rank(3);
    s.dim(0,100); 
    s.dim(1,12); 
    s.dim(2,57);

}

//-----------------------------------------------------------------------------
void H5SelectionTest::tearDown(){

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_creation(){
    std::cout<<"H5SelectionTest::test_creation-------------------------------";
    std::cout<<std::endl;

    H5Selection s1;
    CPPUNIT_ASSERT(s1.rank() == 0);
    CPPUNIT_ASSERT(s1.size() == 0);
    H5Selection s2(3);
    CPPUNIT_ASSERT(s2.rank() == 3);
    CPPUNIT_ASSERT(s2.size() == 0);

    Shape sl(3);
    CPPUNIT_ASSERT(s2.shape() == sl);

    //create selection from shape 
    H5Selection s3(s);
    CPPUNIT_ASSERT(s3.shape() == s);
    CPPUNIT_ASSERT(s3.size() == s.size());
    for(size_t i=0;i<s.rank();i++){
        CPPUNIT_ASSERT(s3.offset(i) == 0);
        CPPUNIT_ASSERT(s3.stride(i) == 1);
        CPPUNIT_ASSERT(s3.count(i) == s[i]);
    }
    
    //using copy constructor
    H5Selection s4 = s3;
    CPPUNIT_ASSERT(s4.shape() == s3.shape());

    //using move constructor
    H5Selection s5 = std::move(s3);
    CPPUNIT_ASSERT(s5.shape() == s4.shape());
    CPPUNIT_ASSERT(s4.shape() != s3.shape());

    //check now if the dataspace is ok
    CPPUNIT_ASSERT(s5.space().rank() == s.rank());
    CPPUNIT_ASSERT(s5.shape().size() == s.size());

}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_assignment(){
    std::cout<<"H5SelectionTest::test_assignment-----------------------------";
    std::cout<<std::endl;
    
    H5Selection s1(s);
    H5Selection s2;

    //copy assignment
    s2 = s1;
    CPPUNIT_ASSERT(s2.shape() == s1.shape());

    //move assignment
    H5Selection s3;
    s3 = std::move(s1);
    CPPUNIT_ASSERT(s3.shape() == s2.shape());
    CPPUNIT_ASSERT(s3.shape() != s1.shape());

    //check dataspaces
    CPPUNIT_ASSERT(s3.space().rank() == s.rank());
    CPPUNIT_ASSERT(s3.space().size() == s.size());
}

//-----------------------------------------------------------------------------
void H5SelectionTest::test_setup(){
    std::cout<<"H5SelectionTest::test_setup-----------------------------------";
    std::cout<<std::endl;
    
    H5Selection s1(s,1,2);

    CPPUNIT_ASSERT(s1.offset(0) == 1);
    CPPUNIT_ASSERT(s1.stride(0) == 2);

    s1.offset(1)=5;
    CPPUNIT_ASSERT(s1.offset(1) == 5);
    s1.stride(2)=10;
    CPPUNIT_ASSERT(s1.stride(2) == 10);


}

