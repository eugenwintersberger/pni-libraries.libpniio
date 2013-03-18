/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Feb 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <pni/core/types.hpp>
using namespace pni::core;

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<complex>
#include<string>

template<typename T> void init_values(T &a,T &b)
{
    a = 100;
    b = 0;
}

template<typename T> void init_values(std::complex<T> &a,std::complex<T> &b)
{
    a = std::complex<T>(1.293761,-9.83762);
    b = std::complex<T>(0,0);
}

template<> void init_values(string &a,string &b);

template<typename T> void compare_values(T a,T b)
{
    CPPUNIT_ASSERT(a == b);
}

template<typename T> void compare_values(std::complex<T> a,std::complex<T> b)
{
    compare_values(a.real(),b.real());
    compare_values(a.imag(),b.imag());
}

