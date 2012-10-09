#include "H5DataspaceTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5DataspaceTest);


void H5DataspaceTest::setUp(){
}

void H5DataspaceTest::tearDown(){
}

void H5DataspaceTest::test_creation(){
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Dataspace s1;

    //per default a scalar data space is created
    //by default this is a scalar dataspace
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.is_scalar());
    CPPUNIT_ASSERT(s1.rank()==0);
    CPPUNIT_ASSERT(s1.size()==1);

    //create a dataspace from a shape object
    //this should lead to a constant dataspace which cannot be extended
    shape_t s({10,3,45});
    shape_t
        uls({H5Dataspace::UNLIMITED,H5Dataspace::UNLIMITED,H5Dataspace::UNLIMITED});
    size_t s_size = 10*3*45;
    H5Dataspace s2(s);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.rank() == s.size());
    CPPUNIT_ASSERT(s2.size() == s_size);

    //check copy process
    H5Dataspace s3(s2);
    CPPUNIT_ASSERT(s3.is_valid());
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s3.is_scalar());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.shape() == s3.shape());
    CPPUNIT_ASSERT(s3.size() == s_size);
    
    
    //check move constructor
    H5Dataspace s4(std::move(s2));
    CPPUNIT_ASSERT(s4.is_valid());
    CPPUNIT_ASSERT(!s2.is_valid());
    CPPUNIT_ASSERT(s4.shape() == s3.shape());


    //create a dataspace with a minimum and maximum size.
    shape_t ms(std::vector<size_t>(s.size(),100));
    H5Dataspace s6(s,ms);
    CPPUNIT_ASSERT(s6.is_valid());
    CPPUNIT_ASSERT(!s6.is_scalar());
    CPPUNIT_ASSERT(s6.size() == s_size);
    for(size_t i=0;i<s6.rank();i++)
    {
        CPPUNIT_ASSERT(s6.dim(i) == s[i]);
        CPPUNIT_ASSERT(s6.max_dim(i) == ms[i]);
    }

    //create a dataspace from a initializer list
    H5Dataspace s7{10,3,45};
    CPPUNIT_ASSERT(!s7.is_scalar());
    CPPUNIT_ASSERT(s7.is_valid());
    CPPUNIT_ASSERT(std::equal(s7.shape().begin(),s7.shape().end(),s.begin()));
    CPPUNIT_ASSERT(std::equal(s7.shape().begin(),s7.shape().end(),s7.maxshape().begin()));


    //create a dataspace wiht minimum and maximum size
    H5Dataspace s8({10,3,45},{30,9,100});
    shape_t maxshape{30,9,100};
    CPPUNIT_ASSERT(!s8.is_scalar());
    CPPUNIT_ASSERT(s8.is_valid());
    CPPUNIT_ASSERT(std::equal(s8.shape().begin(),s8.shape().end(),s.begin()));
    CPPUNIT_ASSERT(std::equal(s8.maxshape().begin(),s8.maxshape().end(),maxshape.begin()));
    
}

//------------------------------------------------------------------------------
void H5DataspaceTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Dataspace s1;

    shape_t s{10,3,45};

    //copy assignment
    s1 = H5Dataspace(s);
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(std::equal(s1.shape().begin(),s1.shape().end(),s.begin()));

    //move assignment
    H5Dataspace s2;

    s2 = std::move(s1);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s1.is_valid());
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(std::equal(s2.shape().begin(),s2.shape().end(),s.begin()));

}

//------------------------------------------------------------------------------
void H5DataspaceTest::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{100,50};
    H5Dataspace s1(s);

    CPPUNIT_ASSERT(std::equal(s1.shape().begin(),s1.shape().end(),s.begin()));
    CPPUNIT_ASSERT(std::equal(s1.maxshape().begin(),s1.maxshape().end(),s.begin()));
    CPPUNIT_ASSERT(s1.rank() == 2);
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.size() == 50*100);

    //request shapes
    std::list<size_t> slist(s1.rank());
    CPPUNIT_ASSERT_NO_THROW(s1.shape(slist));
    CPPUNIT_ASSERT(std::equal(s1.shape().begin(),s1.shape().end(),slist.begin()));
    CPPUNIT_ASSERT_NO_THROW(s1.maxshape(slist));
    CPPUNIT_ASSERT(std::equal(s1.maxshape().begin(),s1.maxshape().end(),slist.begin()));

    slist = std::list<size_t>(s1.rank()+1);
    CPPUNIT_ASSERT_THROW(s1.shape(slist),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(s1.maxshape(slist),ShapeMissmatchError);

    auto list = s1.shape<std::list<size_t> >();
    auto mlist = s1.maxshape<std::list<size_t> >();
    CPPUNIT_ASSERT(std::equal(s1.shape().begin(),s1.shape().end(),list.begin()));
    CPPUNIT_ASSERT(std::equal(s1.maxshape().begin(),s1.maxshape().end(),mlist.begin()));
}

//------------------------------------------------------------------------------
void H5DataspaceTest::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Dataspace space;
    CPPUNIT_ASSERT(space.is_scalar());
   
    shape_t s{10,4,17};
    shape_t ms(s);
    CPPUNIT_ASSERT_NO_THROW(space.resize(s));
    CPPUNIT_ASSERT(!space.is_scalar());

    shape_t s2{100,3};
    CPPUNIT_ASSERT_NO_THROW(space.resize(s2));
    CPPUNIT_ASSERT(!space.is_scalar());
    CPPUNIT_ASSERT(std::equal(space.shape().begin(),space.shape().end(),s2.begin()));
    CPPUNIT_ASSERT(std::equal(space.maxshape().begin(),space.maxshape().end(),s2.begin()));

    shape_t maxshape{100,2,12};
    CPPUNIT_ASSERT_THROW(space.resize(s2,maxshape),ShapeMissmatchError);
    maxshape = shape_t{100,20};
    CPPUNIT_ASSERT_NO_THROW(space.resize(s2,maxshape));
    CPPUNIT_ASSERT(std::equal(space.shape().begin(),space.shape().end(),s2.begin()));
    CPPUNIT_ASSERT(std::equal(space.maxshape().begin(),space.maxshape().end(),maxshape.begin()));

}
