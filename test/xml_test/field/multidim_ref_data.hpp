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
#include <vector>

template<typename T> struct mdim_ref_data
{
    static const std::vector<T> data;
};

#define GENERATE_MDIM_REFERENCE_DATA(type,...)\
    template<> struct mdim_ref_data<type>\
    {\
        static const std::vector<type> data;\
    };\
    const std::vector<type> mdim_ref_data<type>::data = {__VA_ARGS__}

GENERATE_MDIM_REFERENCE_DATA(pni::core::uint8,1, 2, 3);
GENERATE_MDIM_REFERENCE_DATA(pni::core::int8,-4, 3, -10);
GENERATE_MDIM_REFERENCE_DATA(pni::core::uint16,200, 300, 400);
GENERATE_MDIM_REFERENCE_DATA(pni::core::int16,-234, 500, -34);
GENERATE_MDIM_REFERENCE_DATA(pni::core::uint32,4000, 2000, 345);
GENERATE_MDIM_REFERENCE_DATA(pni::core::int32,23456, -3453, 40392);
GENERATE_MDIM_REFERENCE_DATA(pni::core::uint64,4013945,39458,14056);
GENERATE_MDIM_REFERENCE_DATA(pni::core::int64,-4013945, 304213, -405982);
GENERATE_MDIM_REFERENCE_DATA(pni::core::float32,2.3455, -34.e+2, -42.e-5);
GENERATE_MDIM_REFERENCE_DATA(pni::core::float64,-1.233e+4, 239e-3, 30495.e-8);
GENERATE_MDIM_REFERENCE_DATA(pni::core::float128,123.24354e-4, 40394.e-4, 1.23e+5);
GENERATE_MDIM_REFERENCE_DATA(pni::core::complex32,{34.,123.e-3},{34.e-2,98.3},{453.98,-743.29});
GENERATE_MDIM_REFERENCE_DATA(pni::core::complex64,{-23.,-8.203},{893e+4,-23.12},{9.e-8,732e+3});
GENERATE_MDIM_REFERENCE_DATA(pni::core::complex128,{123,340},{0.,-34.9},{345.2,0.});
GENERATE_MDIM_REFERENCE_DATA(pni::core::bool_t,true,true,false);


