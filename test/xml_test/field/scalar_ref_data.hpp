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
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/core/types.hpp>

template<typename T> struct scalar_ref_data
{
    static const T data;
};

#define GENERATE_SCALAR_REFERENCE_DATA(type,...)\
    template<> struct scalar_ref_data<type>\
    {\
        static const type data;\
    };\
    const type scalar_ref_data<type>::data = {__VA_ARGS__}

GENERATE_SCALAR_REFERENCE_DATA(pni::core::uint8,1);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::int8,-4);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::uint16,200);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::int16,-234);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::uint32,4000);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::int32,23456);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::uint64,4013945);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::int64,-4013945);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::float32,2.3455);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::float64,-1.233e+4);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::float128,123.24354e-4);
#ifdef __clang__
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex32,34.,123.e-3);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex64,-23.,-8.203);
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex128,123,340);
#else
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex32,{34.,123.e-3});
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex64,{-23.,-8.203});
GENERATE_SCALAR_REFERENCE_DATA(pni::core::complex128,{123,340});
#endif
GENERATE_SCALAR_REFERENCE_DATA(pni::core::string,"hello word a stupid text");
GENERATE_SCALAR_REFERENCE_DATA(pni::core::bool_t,true);
