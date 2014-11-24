//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Aug 15, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <pni/core/types.hpp>

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
void check_equality(const binary &a,const binary &b);

