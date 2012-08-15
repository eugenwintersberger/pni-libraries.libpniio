#include "H5AttributeObjectTest.hpp"
#include "h5/H5Exceptions.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5AttributeObjectTest);

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::setUp()
{
    file = H5Fcreate("test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);



}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::tearDown()
{
    H5Fclose(file);
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    //default constructor
    H5AttributeObject o;
    CPPUNIT_ASSERT(!o.is_valid());
    CPPUNIT_ASSERT_THROW(o.object_type(),H5ObjectError);
    CPPUNIT_ASSERT_THROW(H5TestObject(-1),H5ObjectError);
  
    //test constructor from new object
    H5TestObject
        test(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));

    //check the object type
    CPPUNIT_ASSERT(test.object_type() == H5ObjectType::GROUP);
    CPPUNIT_ASSERT(test.is_valid());
    CPPUNIT_ASSERT(test.path() == "/group");
    CPPUNIT_ASSERT(test.name() == "group");
    CPPUNIT_ASSERT(test.base() == "/");
    CPPUNIT_ASSERT_NO_THROW(test.close());
    CPPUNIT_ASSERT(!test.is_valid());

    //test copy constructor
    H5TestObject
        t1(H5Gcreate2(file,"group2",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));

    H5AttributeObject t2(t1);
    CPPUNIT_ASSERT((t2.is_valid())&&(t1.is_valid()));
    CPPUNIT_ASSERT_NO_THROW(t1.close());
    CPPUNIT_ASSERT(!t1.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    
    //test move construction
    H5AttributeObject t3(std::move(t2));
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t3.is_valid());
    CPPUNIT_ASSERT(t3.object_type() == H5ObjectType::GROUP);
    t3.close();
    CPPUNIT_ASSERT(!t3.is_valid());


}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5AttributeObject
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));

    CPPUNIT_ASSERT(o1.is_valid());
    H5AttributeObject o2;
    o2= o1;
    CPPUNIT_ASSERT(o1.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());


    H5AttributeObject o3;
    o3= std::move(o1);
    CPPUNIT_ASSERT(!o1.is_valid());
    CPPUNIT_ASSERT(o3.is_valid());
    CPPUNIT_ASSERT(o2.is_valid());
}

//-----------------------------------------------------------------------------
void attribute_object_test_function(hid_t i)
{
    H5TestObject t(i);
    H5AttributeObject object(t);
    CPPUNIT_ASSERT(object.is_valid());
}
//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_destruction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    hid_t id = H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
    //here the H5Object takes ownership over the id
    attribute_object_test_function(id);
    CPPUNIT_ASSERT(!(H5Iis_valid(id)>0));

}


//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_comparison()
{
    H5AttributeObject
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));
    H5AttributeObject o2(H5TestObject(H5Gcreate2(file,"group2",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));
    H5AttributeObject o3(H5TestObject(H5Gopen2(file,"group",H5P_DEFAULT)));
   
    CPPUNIT_ASSERT(o1!=o2);
    CPPUNIT_ASSERT(o1==o3);
}

//-----------------------------------------------------------------------------
void H5AttributeObjectTest::test_string_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5AttributeObject
        o1(H5TestObject(H5Gcreate2(file,"group",H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT)));

    H5Attribute a = o1.attr<String>("test1");
    CPPUNIT_ASSERT(a.is_valid());
    CPPUNIT_ASSERT(a.base().empty());
    CPPUNIT_ASSERT(a.path().empty());
    CPPUNIT_ASSERT(a.name() == "test1");
    CPPUNIT_ASSERT(a.rank() == 0);
    CPPUNIT_ASSERT(a.size() == 1);

    //write data
    String value = "Hello world";
    a.write("Hello world");
    //read data back and check equality
    String value2;
    a.read(value2);
    CPPUNIT_ASSERT(value2 == "Hello world");

    //attribute copy construction
    H5Attribute a2(a);
    CPPUNIT_ASSERT((a2.is_valid())&&(a.is_valid()));
    CPPUNIT_ASSERT(a2.name() == a.name());
    CPPUNIT_ASSERT(a2.type_id() == a.type_id());
    CPPUNIT_ASSERT(a2.rank() == a.rank());
    CPPUNIT_ASSERT(a2.size() == a.size());

    //move construction
    H5Attribute a3(std::move(a2));
    CPPUNIT_ASSERT(!a2.is_valid());
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(a3.name() == a.name());
    CPPUNIT_ASSERT(a3.type_id() == a.type_id());
    CPPUNIT_ASSERT(a3.rank() == a.rank());
    CPPUNIT_ASSERT(a3.size() == a.size());

    //copy assignment
    H5Attribute a4 = a3;
    CPPUNIT_ASSERT((a4.is_valid())&&(a3.is_valid()));
    CPPUNIT_ASSERT(a4.name() == a3.name());
    CPPUNIT_ASSERT(a4.type_id() == a3.type_id());
    CPPUNIT_ASSERT(a4.rank() == a3.rank());
    CPPUNIT_ASSERT(a4.size() == a3.size());
    
    //now close one of the objects
    a4.close();
    CPPUNIT_ASSERT(!a4.is_valid());
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(a.is_valid());

    //test move assignment
    H5Attribute a5 = std::move(a3);
    CPPUNIT_ASSERT(!a3.is_valid());
    CPPUNIT_ASSERT(a5.is_valid());
    CPPUNIT_ASSERT(a5.name() == a.name());
    CPPUNIT_ASSERT(a5.type_id() == a.type_id());
    CPPUNIT_ASSERT(a5.rank() == a.rank());
    CPPUNIT_ASSERT(a5.size() == a.size());


}

