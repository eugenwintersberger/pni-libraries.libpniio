//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jan 15, 2016
//      Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//               Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <boost/test/unit_test.hpp>
#include <pni/types.hpp>

template<typename GeneralT>
using is_float = pni::is_float_type<GeneralT>;

//-----------------------------------------------------------------------------
template<
         typename GeneralT,
         typename std::enable_if<!is_float<GeneralT>::value>::type* = nullptr
        > 
void check_equal(const GeneralT &a,const GeneralT &b)
{
    BOOST_CHECK(a == b);
}

//-----------------------------------------------------------------------------
template<
         typename GeneralT,
         typename std::enable_if<is_float<GeneralT>::value>::type* = nullptr
        > 
void check_equal(const GeneralT &a,const GeneralT &b)
{
    BOOST_CHECK_CLOSE_FRACTION(a,b,1.e-8); 
}

//-----------------------------------------------------------------------------
template<typename GeneralT> 
void check_equal(const std::complex<GeneralT> &a,const std::complex<GeneralT> &b)
{
    BOOST_CHECK_CLOSE_FRACTION(a.real(),b.real(),1.e-8);
    BOOST_CHECK_CLOSE_FRACTION(a.imag(),b.imag(),1.e-8);
}
