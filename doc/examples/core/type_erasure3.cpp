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
// Created on: Apr 2, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <vector>
#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <pni/type_erasures.hpp>

using namespace pni;

//some usefull type definitions
typedef dynamic_array<float64> darray_type;
typedef static_array<float64,3,3> sarray_type;
typedef fixed_dim_array<float64,2> farray_type;

void show_info(const array &a)
{
    std::cout<<"Data type: "<<type_id(a)<<std::endl;
    std::cout<<"Rank     : "<<a.rank()<<std::endl;
    std::cout<<"Shape    : (";
    auto s = a.shape<shape_t>();
    for(auto n: s) std::cout<<" "<<n<<" ";
    std::cout<<")"<<std::endl;
    std::cout<<"Size     : "<<a.size()<<std::endl;
}

int main(int ,char **)
{
    auto a1 = darray_type::create(shape_t{1024,2048});
    auto a2 = farray_type::create(shape_t{1024,2048});
    sarray_type a3;

    std::cout<<"--------------------------------"<<std::endl;
    show_info(array(a1));
    std::cout<<std::endl<<"--------------------------------"<<std::endl;
    show_info(array(a2));
    std::cout<<std::endl<<"--------------------------------"<<std::endl;
    show_info(array(a3));

    return 0;
}

