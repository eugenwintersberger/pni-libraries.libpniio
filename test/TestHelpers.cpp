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
