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
// ==========================================================================
//
// Created on: Sep 13, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<vector>
#include<pni/core/types.hpp>

using namespace pni::core;

//-----------------------------------------------------------------------------
/*!
\brief create scalar test data

Template function creates a scalar test value. This function is used to test
scalar data IO. Specialized functions are available for Bool and String types.
\tparam T data type requested
\return data value
*/
template<typename T> T create_scalar_data()
{
    return T(1);
}

template<> string create_scalar_data<string>();
template<> bool create_scalar_data<bool>();

//-----------------------------------------------------------------------------
/*!
\brief create array test data

Creates array test data. The data is stored in a std::vector container. 
Data can be used for array data IO. Spezialied functions are available for Bool
and String types.
\tparam T requested data type
\param n number of elements to create
\return container with data values
*/
template<typename T> std::vector<T> create_array_data(size_t n)
{
    std::vector<T> v(n);

    std::fill(v.begin(),v.end(),T(1));
    return v;
}

template<> std::vector<string> create_array_data(size_t n);
template<> std::vector<bool> create_array_data(size_t n);

