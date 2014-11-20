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
// Created on: Sep 13, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include "data.hpp"


//-----------------------------------------------------------------------------
template<> string create_scalar_data<string>()
{
    return "hello world";
}

//-----------------------------------------------------------------------------
template<> bool create_scalar_data<bool>()
{
    return true;
}

//-----------------------------------------------------------------------------
template<> std::vector<string> create_array_data(size_t n)
{
    std::vector<string> v;

    std::stringstream ss;
    for(size_t i=0;i<n;i++)
    {
        ss<<i;
        v.push_back(ss.str());
    }

    return v;
}

//-----------------------------------------------------------------------------
template<> std::vector<bool> create_array_data(size_t n)
{
    std::vector<bool> v(n);

    for(size_t i=0;i<n;i++)
    {
        if(i%2) v[i] = true;
        else v[i] = false;
    }

    return v;
}

