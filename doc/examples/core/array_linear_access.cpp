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
// Linear data access
//-----------------------------------------------------------------------------
#include <random>
#include <pni/types.hpp>
#include <pni/arrays.hpp>

using namespace pni;

typedef uint16                          channel_type;
typedef fixed_dim_array<channel_type,1> mca_type;

int main(int ,char **)
{
    auto mca = mca_type::create(shape_t{128}); 

    //initialize
    std::random_device rdev;
    std::mt19937 generator(rdev());
    std::uniform_int_distribution<channel_type> dist(0,65000);

    //generate data
    for(auto &channel: mca)  channel = dist(generator);

    //subtract some number 
    for(size_t i=0;i<mca.size();++i) if(mca[i]>=10) mca[i] -= 10;

    //set the first and last element to 0 
    mca.front() = 0;
    mca.back()  = 0;
    
    //output data
    for(auto channel: mca) std::cout<<channel<<std::endl;

    return 0;
}

