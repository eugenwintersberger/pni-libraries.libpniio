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
    PRINT_TEST_FUNC_SIG;

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
void H5AttributeTest::test_comparison()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a1 = group.attr<String>("a1");
    H5Attribute a2 = group.attr("a1");
    H5Attribute a3 = group.attr<String>("a2");
   
    CPPUNIT_ASSERT(a1!=a3);
    CPPUNIT_ASSERT(a1==a2);
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

//-----------------------------------------------------------------------------
void H5AttributeTest::test_string_attribute()
{
    PRINT_TEST_FUNCTION_SIG;
    
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

