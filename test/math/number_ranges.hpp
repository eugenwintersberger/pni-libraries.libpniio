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
#include <boost/math/special_functions/sign.hpp>
#include <pni/types.hpp>
#include <cmath>

template<
         typename GeneralT,
         bool is_signed = true
        > struct add_ranges
{
    GeneralT rhs_min() const { return pni::type_info<GeneralT>::min()/GeneralT(2); }
    GeneralT rhs_max() const { return pni::type_info<GeneralT>::max()/GeneralT(2); }

    GeneralT lhs_min() const { return rhs_min(); }
    GeneralT lhs_max() const { return rhs_max(); } 
};

template<typename GeneralT> struct add_ranges<std::complex<GeneralT>,true>
{
    GeneralT rhs_min() const { return pni::type_info<GeneralT>::min()/GeneralT(2); }
    GeneralT rhs_max() const { return pni::type_info<GeneralT>::max()/GeneralT(2); }

    GeneralT lhs_min() const { return rhs_min(); }
    GeneralT lhs_max() const { return rhs_max(); } 
};

template<typename GeneralT> struct mult_ranges
{
    GeneralT rhs_min() const 
    { 
        using namespace boost::math;
        GeneralT min = pni::type_info<GeneralT>::min();

        return sign(min)*GeneralT(std::sqrt(sign(min)*min)); 
    }
    GeneralT rhs_max() const { return GeneralT(std::sqrt(pni::type_info<GeneralT>::max())); }

    GeneralT lhs_min() const { return rhs_min(); }
    GeneralT lhs_max() const { return rhs_max(); } 
};

template<typename GeneralT> struct mult_ranges<std::complex<GeneralT>>
{
    mult_ranges<GeneralT> base_range;

    GeneralT rhs_min() const { return GeneralT(0.5)*base_range.rhs_min(); }
    GeneralT rhs_max() const { return GeneralT(0.5)*base_range.rhs_max(); }

    GeneralT lhs_min() const { return GeneralT(0.5)*base_range.lhs_min(); }
    GeneralT lhs_max() const { return GeneralT(0.5)*base_range.lhs_max(); } 
};

template<typename GeneralT> struct div_ranges
{
    GeneralT rhs_min() const { return GeneralT(1); }
    GeneralT rhs_max() const { return pni::type_info<GeneralT>::max()/GeneralT(2); }

    GeneralT lhs_min() const { return pni::type_info<GeneralT>::min()/GeneralT(2); }
    GeneralT lhs_max() const { return pni::type_info<GeneralT>::max()/GeneralT(2); } 
};

template<typename GeneralT> struct div_ranges<std::complex<GeneralT>>
{
    div_ranges<GeneralT> base_range;
    
    GeneralT rhs_min() const { return base_range.rhs_min(); }
    GeneralT rhs_max() const { return base_range.rhs_max(); }

    GeneralT lhs_min() const { return base_range.lhs_min(); }
    GeneralT lhs_max() const { return base_range.lhs_max(); } 
};

