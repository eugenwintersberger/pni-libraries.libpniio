#include "TestHelpers.hpp"


//--------------------------------------------------
template<> void compare_values(Float32 a,Float32 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}

//--------------------------------------------------
template<> void compare_values(Float64 a,Float64 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}

//--------------------------------------------------
template<> void compare_values(Float128 a,Float128 b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-6);
}


template<> void init_values(String &a,String &b)
{
    a = "hello world";
    b = "";
}
