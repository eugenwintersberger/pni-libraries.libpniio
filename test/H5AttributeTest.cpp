#include "H5AttributeTest.hpp"
#include "h5/H5Exceptions.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5AttributeTest);

//-----------------------------------------------------------------------------
void H5AttributeTest::setUp()
{
    file = H5File::create_file("H5AttributeTest.h5",true,0);
    group = H5Group("group",file);
}

//-----------------------------------------------------------------------------
void H5AttributeTest::tearDown()
{
    group.close();
    file.close();
}

//-----------------------------------------------------------------------------
void H5AttributeTest::test_creation()
{
    PRINT_TEST_FUNCTION_SIG;

    //default constructor
    H5Attribute a;
    CPPUNIT_ASSERT(!a.is_valid());
  
    //test constructor from new object
    H5Attribute a1 = group.attr<String>("a1");
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");

    
    //test construction from copy constructor
    H5Attribute a2(a1);
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == a1.name());
    
    //test move construction
    H5Attribute a3(std::move(a2));
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(!a2.is_valid());
}

//-----------------------------------------------------------------------------
void H5AttributeTest::test_assignment()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a1 = group.attr<String>("a1");
    CPPUNIT_ASSERT(a1.is_valid());

    H5Attribute a2;
    a2 = a1;
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a2.is_valid());

    H5Attribute a3;
    a3= std::move(a2);
    CPPUNIT_ASSERT(!a2.is_valid());
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a3.is_valid());
}



//-----------------------------------------------------------------------------
void H5AttributeTest::test_inquery()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a1 = group.attr<Float32>("a1");
    shape_t shape{10,2};
    H5Attribute a2 = group.attr<Float32>("a2",shape);

    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");
    CPPUNIT_ASSERT(a1.size() == 1);
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.type_id() == TypeID::FLOAT32);
    CPPUNIT_ASSERT(a1.shape<shape_t>().size() == 0);


    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == "a2");
    CPPUNIT_ASSERT(a2.size() == 20);
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.type_id() == TypeID::FLOAT32);
    auto ashape = a2.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),ashape.begin()));
}


