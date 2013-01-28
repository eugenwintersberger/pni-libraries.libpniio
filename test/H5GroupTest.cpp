
#include <pni/core/arrays.hpp>
#include "H5GroupTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5GroupTest);


//-----------------------------------------------------------------------------
void H5GroupTest::setUp()
{
    file = H5File::create_file("H5GroupTest.h5",true,0);
}

//-----------------------------------------------------------------------------
void H5GroupTest::tearDown()
{
    file.close();
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Group g; //default constructor

    CPPUNIT_ASSERT(!g.is_valid());

    //create directly using the constructor
    H5Group g1("group1",file);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g1.name()=="group1");
    CPPUNIT_ASSERT(g1.path()=="/group1");
    CPPUNIT_ASSERT(g1.base()=="/");

    //create a group from another group
    H5Group g2("group12",g1);
    CPPUNIT_ASSERT(g2.is_valid());

    //using the copy constructor
    H5Group g3 = g2;
    CPPUNIT_ASSERT(g3.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());

    //using the move constructor
    H5Group g4 = std::move(g2);
    CPPUNIT_ASSERT(g4.is_valid());
    CPPUNIT_ASSERT(!g2.is_valid());

    //testing creation of a full path
    H5Group g5("group5/test/directory",file);
    CPPUNIT_ASSERT(g5.is_valid());

    CPPUNIT_ASSERT(g5.name() == "directory");
    CPPUNIT_ASSERT(g5.path() == "/group5/test/directory");
    CPPUNIT_ASSERT(g5.base() == "/group5/test");
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group g("group1",file);
    H5Group g1,g2;
    
    //test copy assignment
    CPPUNIT_ASSERT_NO_THROW(g1 = g);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g.is_valid());

    //test move assignment
    CPPUNIT_ASSERT_NO_THROW(g2 = std::move(g));
    CPPUNIT_ASSERT(g2.is_valid());
    CPPUNIT_ASSERT(!g.is_valid());

    g.close();
    g1.close();
    g2.close();
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_linking()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //checking internal links
    H5Group g("/data/test/dir",file);
    CPPUNIT_ASSERT_NO_THROW(g.link("/collection/dir"));
    CPPUNIT_ASSERT(file.exists("/collection/dir"));

    H5Group ref = file.open("/data/test");
    CPPUNIT_ASSERT_NO_THROW(g.link(ref,"whatever"));
    CPPUNIT_ASSERT(file.exists("/data/test/whatever"));


    //check external links
    H5File file2 = H5File::create_file("H5GroupTest2.h5",true,0);
    H5Group("/detector/data",file2);
        
    CPPUNIT_ASSERT_NO_THROW(file.link("H5GroupTest2.h5:/detector/data",
                "external/detector/data"));
    CPPUNIT_ASSERT(file.exists("/external/detector/data"));

    
}

//------------------------------------------------------------------------------
void H5GroupTest::test_openobjects()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    H5Group g("/test/data/detector",file);

    H5Group det;

    CPPUNIT_ASSERT_NO_THROW(det = file.open("/test/data/detector"));
    CPPUNIT_ASSERT(det.is_valid());
    CPPUNIT_ASSERT(det.path() == "/test/data/detector");
    CPPUNIT_ASSERT(det.base() == "/test/data");
    CPPUNIT_ASSERT(det.name() == "detector");

    H5Group p;
    CPPUNIT_ASSERT_NO_THROW(p = det.parent());
    CPPUNIT_ASSERT(p.path() == "/test/data");
    CPPUNIT_ASSERT(p.base() == "/test");
    CPPUNIT_ASSERT(p.name() == "data");

    H5Group test;
    CPPUNIT_ASSERT_NO_THROW(test = file["test"]);
    CPPUNIT_ASSERT(test.is_valid());
    H5Group data;
    CPPUNIT_ASSERT_NO_THROW(data = test["data"]);
    CPPUNIT_ASSERT_NO_THROW(det = test["data/detector"]);
    CPPUNIT_ASSERT(data.is_valid());
    CPPUNIT_ASSERT(det.is_valid());
}



//-----------------------------------------------------------------------------
void H5GroupTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group("group1/data",file);

    H5Group g1 = file["group1/data"];
    H5Group g2 = file["group1/data"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = file["group1"];
    CPPUNIT_ASSERT(g2 != g1);
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group g1("group1/data",file);
    CPPUNIT_ASSERT(g1.parent().name() == "group1");
    H5Group p(g1.parent());

    CPPUNIT_ASSERT(p.parent().name() == "/");
}
