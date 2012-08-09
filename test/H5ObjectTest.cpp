#include "H5ObjectTest.hpp"
#include "h5/H5Exceptions.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5ObjectTest);

//-----------------------------------------------------------------------------
void H5ObjectTest::setUp()
{
    file = H5Fcreate("test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);



}

//-----------------------------------------------------------------------------
void H5ObjectTest::tearDown()
{
    H5Fclose(file);
}

//-----------------------------------------------------------------------------
void H5ObjectTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    //default constructor
    H5Object o;
    CPPUNIT_ASSERT(!o.is_valid());
    CPPUNIT_ASSERT_THROW(o.object_type(),H5ObjectError);
    CPPUNIT_ASSERT_THROW(H5TestObject(-1),H5ObjectError);
  
    //test constructor from new object
    H5TestObject
        test(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));

    //check the object type
    CPPUNIT_ASSERT(test.object_type() == H5ObjectType::GROUP);
    CPPUNIT_ASSERT(test.is_valid());
    CPPUNIT_ASSERT_NO_THROW(test.close());
    CPPUNIT_ASSERT(!test.is_valid());

    //test copy constructor
    H5TestObject
        t1(H5Gcreate2(file,"group2",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));

    H5Object t2(t1);
    CPPUNIT_ASSERT((t2.is_valid())&&(t1.is_valid()));
    CPPUNIT_ASSERT_NO_THROW(t1.close());
    CPPUNIT_ASSERT(!t1.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    
    //test move construction
    H5Object t3(std::move(t2));
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t3.is_valid());
    CPPUNIT_ASSERT(t3.object_type() == H5ObjectType::GROUP);
    t3.close();
    CPPUNIT_ASSERT(!t3.is_valid());


}

//-----------------------------------------------------------------------------
void H5ObjectTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Object
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));

    CPPUNIT_ASSERT(o1.is_valid());
    H5Object o2;
    o2= o1;
    CPPUNIT_ASSERT(o1.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());

    H5Object o3;
    o3= std::move(o1);
    CPPUNIT_ASSERT(!o1.is_valid());
    CPPUNIT_ASSERT(o3.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());
}

void function(hid_t i)
{
    H5TestObject t(i);
    H5Object object(t);
    CPPUNIT_ASSERT(object.is_valid());
}
//-----------------------------------------------------------------------------
void H5ObjectTest::test_destruction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    hid_t id = H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
    //here the H5Object takes ownership over the id
    function(id);
    CPPUNIT_ASSERT(!(H5Iis_valid(id)>0));

}


//-----------------------------------------------------------------------------
void H5ObjectTest::test_comparison()
{
    H5Object
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));
    H5Object o2(H5TestObject(H5Gcreate2(file,"group2",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));
    H5Object o3(H5TestObject(H5Gopen(file,"group")));
   
    CPPUNIT_ASSERT(o1!=o2);
    CPPUNIT_ASSERT(o1==o3);
}

