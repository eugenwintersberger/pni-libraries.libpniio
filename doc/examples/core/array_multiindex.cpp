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
typedef std::array<size_t,2>          index_type;
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

    
    size_t zero_count = 0;
    size_t max_count  = 0;
    for(size_t i=512;i<934;++i)
    {
        for(size_t j=128;j<414;++j)
        {
            if(image(i,j) == 0) zero_count++;
            if(image(index_type{{i,j}}) >= 10000) max_count++;
                
        }
    }

    std::cout<<"Found 0 in "<<zero_count<<" pixels!"<<std::endl;
    std::cout<<"Found max in "<<max_count<<" pixels!"<<std::endl;
                               
    return 0;
}

