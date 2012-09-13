#include "EqualityCheck.hpp"

//-----------------------------------------------------------------------------
void check_equality(const String &a,const String &b)
{
    CPPUNIT_ASSERT(a == b);
}

//-----------------------------------------------------------------------------
void check_equality(const Bool &a,const Bool &b)
{
    CPPUNIT_ASSERT(a == b);
}
