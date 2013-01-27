#include "EqualityCheck.hpp"

//-----------------------------------------------------------------------------
void check_equality(const string &a,const string &b)
{
    CPPUNIT_ASSERT(a == b);
}

//-----------------------------------------------------------------------------
void check_equality(const bool &a,const bool &b)
{
    CPPUNIT_ASSERT(a == b);
}
