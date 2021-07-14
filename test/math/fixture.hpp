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
//  Created on: Oct 22, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/types.hpp>
#include <pni/arrays/scalar.hpp>
#include "../data_generator.hpp"

template<typename AT> struct fixture
{
    typedef AT                      array_type;
    typedef typename AT::value_type value_type;
    typedef scalar<value_type>      scalar_type;
    typedef random_generator<value_type> generator_type; 
        
    generator_type gen_rhs;
    generator_type gen_lhs;
    pni::shape_t shape;
    array_type lhs_orig;
    array_type lhs;
    value_type lhs_scalar;
    value_type rhs_scalar;
    scalar_type lhs_s;
    scalar_type rhs_s;
    array_type rhs;
    pni::type_id_t tid;
    pni::string type_name;

    template<typename RT> fixture(const RT &r):
        gen_rhs(r.rhs_min(),r.rhs_max()),
        gen_lhs(r.lhs_min(),r.lhs_max()),
        shape(pni::shape_t{2,3,4}),
        lhs_orig(array_type::create(shape)),
        lhs(array_type::create(shape)),
        lhs_scalar(gen_lhs()),
        rhs_scalar(gen_rhs()),
        lhs_s(gen_lhs()),
        rhs_s(gen_rhs()),
        rhs(array_type::create(shape)),
        tid(pni::type_id_map<value_type>::type_id),
        type_name(str_from_type_id(tid))
    {
        std::generate(lhs.begin(),lhs.end(),gen_lhs); 
        std::generate(rhs.begin(),rhs.end(),gen_rhs);
        std::copy(lhs.begin(),lhs.end(),lhs_orig.begin());
    }
};
