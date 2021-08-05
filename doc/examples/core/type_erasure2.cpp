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

//-----------------------------------------------------------------------------
#include <iostream>
#include <pni/types.hpp>
#include <pni/type_erasures.hpp>

using namespace pni;

int main(int ,char **)
{
    //construction from a number
    float64 number = 10.234;
    value_ref v(std::ref(number));
    std::cout<<v.as<float64>()<<std::endl;

    v = 23.345e+2;

    std::cout<<v.as<float64>()<<std::endl;
    std::cout<<number<<std::endl;

    return 0;
}
