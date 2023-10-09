//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
//
// Created on: Mar 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// using views with STL algorithms and containers
//-----------------------------------------------------------------------------
#include <algorithm>
#include <random>
#include <pni/types.hpp>
#include <pni/arrays.hpp>

using namespace pni;

typedef uint16                        pixel_type;
typedef std::array<size_t,2>          index_type;
typedef fixed_dim_array<pixel_type,2> image_type;
typedef image_type::view_type         roi_type;
typedef std::vector<roi_type>         roi_vector;

int main(int ,char **)
{
    auto image = image_type::create(shape_t{1024,512});

    std::fill(image.begin(),image.end(),0); //use STL std::fill to initialize

    std::random_device rdev;
    std::mt19937 generator(rdev());
    std::uniform_int_distribution<pixel_type> dist(0,65000);

    std::generate(image.begin(),image.end(),
                  [&generator,&dist](){ return dist(generator); });

    roi_vector rois; 
    rois.push_back(image(slice(512,934),slice(128,414)));
    rois.push_back(image(slice(0,128),slice(4,100)));
    rois.push_back(image(200,slice(450,512)));

    for(auto roi: rois)
    {
        auto zero_count = std::count_if(roi.begin(),roi.end(),
                                        [](pixel_type &p){return p==0;});
        auto max_count  = std::count_if(roi.begin(),roi.end(),
                                        [](pixel_type &p){return p>= 10000; });

        std::cout<<std::endl;
        std::cout<<"Found 0 in "<<zero_count<<" pixels!"<<std::endl;
        std::cout<<"Found max in "<<max_count<<" pixels!"<<std::endl;
        std::cout<<std::endl;
    }
                               
    return 0;
}

