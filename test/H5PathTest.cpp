#include "H5PathTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5PathTest);


void H5PathTest::setUp()
{

}

void H5PathTest::tearDown()
{

}

void H5PathTest::test_creation()
{
    H5Path p;
    H5Path p1("/hello/world/dir/data");
    std::cout<<p1<<std::endl;

    H5Path p2("hello/world/dir");
    std::cout<<p2<<std::endl;
    H5Path p3("/hello");
    std::cout<<p3<<std::endl;
    H5Path p4("/hello/");
    H5Path p5("hello/");
    std::cout<<p4<<std::endl;
    CPPUNIT_ASSERT(p4 == p3);
    CPPUNIT_ASSERT(p4 == p5);
}
