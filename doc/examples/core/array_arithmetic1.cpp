//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Mar 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// using views with STL algorithms
//-----------------------------------------------------------------------------
#include <algorithm>
#include <random>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

typedef float64                        number_type;
typedef fixed_dim_array<number_type,2> image_type;

int main(int ,char **)
{
    shape_t s{1024,512};
    auto image      = image_type::create(s);
    auto background = image_type::create(s);
    number_type exp_time = 1.234;
    number_type current  = 98.3445;

    //compute the corrected image
    image = (image-background)/exp_time/current;
                               
    return 0;
}

