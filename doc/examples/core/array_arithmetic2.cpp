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
typedef fixed_dim_array<number_type,3> stack_type;
typedef fixed_dim_array<number_type,2> image_type;
typedef fixed_dim_array<number_type,1> data_type;

int main(int ,char **)
{
    shape_t frame_shape{1024,512};
    shape_t data_shape{100};
    shape_t stack_shape{100,1024,512};
    auto image_stack = stack_type::create(stack_shape);
    auto background  = image_type::create(frame_shape);
    auto exp_time    = data_type::create(data_shape);
    auto current     = data_type::create(data_shape);

    for(size_t i = 0;i<data_shape[0];++i)
    {
        std::cout<<"Processing frame "<<i<<" ..."<<std::endl;
        auto curr_frame = image_stack(i,slice(0,1024),slice(0,512));
        curr_frame = (curr_frame - background)/exp_time[i]/current[i];
    }
                               
    return 0;
}

