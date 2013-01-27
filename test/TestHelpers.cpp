#include "TestHelpers.hpp"


//--------------------------------------------------
template<> void compare_values(float32 a,float32 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}

//--------------------------------------------------
template<> void compare_values(float64 a,float64 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}

//--------------------------------------------------
template<> void compare_values(float128 a,float128 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}


template<> void init_values(string &a,string &b)
{
    a = "hello world";
    b = "";
}
