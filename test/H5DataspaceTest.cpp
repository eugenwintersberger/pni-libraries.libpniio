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
    //by default this is a scalar dataspace
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.is_scalar());
    CPPUNIT_ASSERT(s1.rank()==0);
    CPPUNIT_ASSERT(s1.size()==1);

    //create a dataspace from a shape object
    //this should lead to a constant dataspace which cannot be extended
    Shape s{10,3,45};

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


    //create a dataspace with a minimum and maximum size.
    Shape ms = std::vector<size_t>(s.rank(),100);
    H5Dataspace s6(s,ms);
    CPPUNIT_ASSERT(s6.is_valid());
    CPPUNIT_ASSERT(!s6.is_scalar());
    for(size_t i=0;i<s6.rank();i++){
        CPPUNIT_ASSERT(s6.dim(i) == s[i]);
        CPPUNIT_ASSERT(s6.max_dim(i) == ms[i]);
    }

    //create a dataspace from a initializer list
    H5Dataspace s7 = {10,3,45};
    CPPUNIT_ASSERT(!s7.is_scalar());
    CPPUNIT_ASSERT(s7.is_valid());
    CPPUNIT_ASSERT(s7.shape() == s);
    CPPUNIT_ASSERT(s7.shape() == s7.maxshape());


    //create a dataspace wiht minimum and maximum size
    H5Dataspace s8({10,3,45},{30,9,100});
    Shape maxshape = {30,9,100};
    CPPUNIT_ASSERT(!s8.is_scalar());
    CPPUNIT_ASSERT(s8.is_valid());
    CPPUNIT_ASSERT(s8.shape() == s);
    CPPUNIT_ASSERT(s8.maxshape() == maxshape);

}

//------------------------------------------------------------------------------
void H5DataspaceTest::test_assignment(){
    std::cout<<"void H5Dataspace::test_assignment()---------------------------";
    std::cout<<std::endl;

    H5Dataspace s1;

    Shape s{10,3,45};

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

//------------------------------------------------------------------------------
void H5DataspaceTest::test_inquery(){
    Shape s{100,50};
    H5Dataspace s1(s);

    CPPUNIT_ASSERT(s1.shape() == s);
    CPPUNIT_ASSERT(s1.maxshape() == s);
    CPPUNIT_ASSERT(s1.rank() == 2);
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s.size() == 50*100);

}

//------------------------------------------------------------------------------
void H5DataspaceTest::test_resize(){
    H5Dataspace space;
    CPPUNIT_ASSERT(space.is_scalar());
   
    Shape s{10,4,17};
    Shape ms(s);
    CPPUNIT_ASSERT_NO_THROW(space.resize(s));
    CPPUNIT_ASSERT(!space.is_scalar());
    CPPUNIT_ASSERT(space.shape() == s);
    CPPUNIT_ASSERT(space.maxshape() == s);

    Shape s2 = {100,3};
    CPPUNIT_ASSERT_NO_THROW(space.resize(s2));
    CPPUNIT_ASSERT(!space.is_scalar());
    CPPUNIT_ASSERT(space.shape() == s2);
    CPPUNIT_ASSERT(space.maxshape() == s2);

    Shape maxshape = {100,2,12};
    CPPUNIT_ASSERT_THROW(space.resize(s2,maxshape),ShapeMissmatchError);
    maxshape = {100,20};
    CPPUNIT_ASSERT_NO_THROW(space.resize(s2,maxshape));
    CPPUNIT_ASSERT(space.shape() == s2);
    CPPUNIT_ASSERT(space.maxshape() == maxshape);

}
