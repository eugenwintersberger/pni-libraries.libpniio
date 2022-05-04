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
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

template<typename GeneralT> struct scalar_ref_data
{
    static const GeneralT data;
};

#define GENERATE_SCALAR_REFERENCE_DATA(type,...)\
    template<> struct scalar_ref_data<type>\
    {\
        static const type data;\
    };\
    const type scalar_ref_data<type>::data = {__VA_ARGS__}

GENERATE_SCALAR_REFERENCE_DATA(pni::uint8,1);
GENERATE_SCALAR_REFERENCE_DATA(pni::int8,-4);
GENERATE_SCALAR_REFERENCE_DATA(pni::uint16,200);
GENERATE_SCALAR_REFERENCE_DATA(pni::int16,-234);
GENERATE_SCALAR_REFERENCE_DATA(pni::uint32,4000);
GENERATE_SCALAR_REFERENCE_DATA(pni::int32,23456);
GENERATE_SCALAR_REFERENCE_DATA(pni::uint64,4013945);
GENERATE_SCALAR_REFERENCE_DATA(pni::int64,-4013945);
GENERATE_SCALAR_REFERENCE_DATA(pni::float32,2.3455f);
GENERATE_SCALAR_REFERENCE_DATA(pni::float64,-1.233e+4);
GENERATE_SCALAR_REFERENCE_DATA(pni::float128,123.24354e-4);
#ifdef __clang__
GENERATE_SCALAR_REFERENCE_DATA(pni::complex32,34.f,123.e-3f);
GENERATE_SCALAR_REFERENCE_DATA(pni::complex64,-23.,-8.203);
GENERATE_SCALAR_REFERENCE_DATA(pni::complex128,123,340);
#elif _MSC_VER
GENERATE_SCALAR_REFERENCE_DATA(pni::complex32,34.f,123.e-3f);
GENERATE_SCALAR_REFERENCE_DATA(pni::complex64,-23.,-8.203);
GENERATE_SCALAR_REFERENCE_DATA(pni::complex128,123,340);
#else
GENERATE_SCALAR_REFERENCE_DATA(pni::complex32,{34.f,123.e-3f});
GENERATE_SCALAR_REFERENCE_DATA(pni::complex64,{-23.,-8.203});
GENERATE_SCALAR_REFERENCE_DATA(pni::complex128,{123,340});
#endif
GENERATE_SCALAR_REFERENCE_DATA(pni::string,"hello word a stupid text");
GENERATE_SCALAR_REFERENCE_DATA(pni::bool_t,true);
GENERATE_SCALAR_REFERENCE_DATA(hdf5::datatype::EBool,true);
