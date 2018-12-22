//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 15, 2016
//      Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//               Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>

template<typename T>
using is_float = pni::core::is_float_type<T>;

//-----------------------------------------------------------------------------
template<
         typename T,
         typename std::enable_if<!is_float<T>::value>::type* = nullptr
        > 
void check_equal(const T &a,const T &b)
{
    BOOST_CHECK(a == b);
}

//-----------------------------------------------------------------------------
template<
         typename T,
         typename std::enable_if<is_float<T>::value>::type* = nullptr
        > 
void check_equal(const T &a,const T &b)
{
    BOOST_CHECK_CLOSE_FRACTION(a,b,1.e-8); 
}

//-----------------------------------------------------------------------------
template<typename T> 
void check_equal(const std::complex<T> &a,const std::complex<T> &b)
{
    BOOST_CHECK_CLOSE_FRACTION(a.real(),b.real(),1.e-8);
    BOOST_CHECK_CLOSE_FRACTION(a.imag(),b.imag(),1.e-8);
}
