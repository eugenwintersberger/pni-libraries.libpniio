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
// using STL algorithms
//-----------------------------------------------------------------------------
#include <algorithm>
#include <random>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

typedef uint16                        pixel_type;
typedef fixed_dim_array<pixel_type,2> image_type;

int main(int ,char **)
{
    auto image = image_type::create(shape_t{1024,512});

    std::fill(image.begin(),image.end(),0); //use STL std::fill to initialize

    std::random_device rdev;
    std::mt19937 generator(rdev());
    std::uniform_int_distribution<pixel_type> dist(0,65000);

    std::generate(image.begin(),image.end(),
                  [&generator,&dist](){ return dist(generator); });

    //get min and max
    std::cout<<"Min: "<<*std::min_element(image.begin(),image.end())<<std::endl;
    std::cout<<"Max: "<<*std::max_element(image.begin(),image.end())<<std::endl;
    std::cout<<"Sum: ";
    std::cout<<std::accumulate(image.begin(),image.end(),pixel_type(0));
    std::cout<<std::endl;
                               
    return 0;
}

