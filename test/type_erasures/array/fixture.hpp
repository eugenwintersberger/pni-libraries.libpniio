//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Oct 16, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once 

#include <algorithm>
#include <pni/types.hpp>
#include "../../data_generator.hpp"

template<typename TestArrayT> struct md_array_trait
{
    typedef TestArrayT mdarray_type; 
    typedef typename mdarray_type::value_type value_type;
    typedef random_generator<value_type> generator_type; 
};

template<typename TestArrayT> struct fixture
{
    typename md_array_trait<TestArrayT>::generator_type generator; 
    pni::shape_t shape; 
    TestArrayT mdarray_1;
    TestArrayT mdarray_2; 

    fixture():
        generator(),
        shape(pni::shape_t{3,2}),
        mdarray_1(TestArrayT::create(shape)),
        mdarray_2(TestArrayT::create(shape))
    {
        std::generate(mdarray_1.begin(),mdarray_1.end(),generator); 
        std::generate(mdarray_2.begin(),mdarray_2.end(),generator);
    }
    
};
