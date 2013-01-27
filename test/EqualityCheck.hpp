#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <pni/core/type_info.hpp>

using namespace pni::core;

template<typename T,bool is_int,bool is_complex> class EqualityCheck;

template<typename T> class EqualityCheck<T,true,false>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT(a == b);
        }
};

template<typename T> class EqualityCheck<T,false,false>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-8);
        }
};

template<typename T> class EqualityCheck<T,false,true>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.real(),b.real(),1.e-8);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.imag(),b.imag(),1.e-8);
        }
};


template<typename T> void check_equality(const T &a,const T &b)
{
    EqualityCheck<T,type_info<T>::is_integer,type_info<T>::is_complex>::check(a,b);
}

void check_equality(const string &a,const string &b);
void check_equality(const bool &a,const bool &b);

