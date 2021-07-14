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
         typename T,
         bool is_signed = true
        > struct add_ranges
{
    T rhs_min() const { return pni::type_info<T>::min()/T(2); }
    T rhs_max() const { return pni::type_info<T>::max()/T(2); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct add_ranges<std::complex<T>,true>
{
    T rhs_min() const { return pni::type_info<T>::min()/T(2); }
    T rhs_max() const { return pni::type_info<T>::max()/T(2); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct mult_ranges
{
    T rhs_min() const 
    { 
        using namespace boost::math;
        T min = pni::type_info<T>::min();

        return sign(min)*T(std::sqrt(sign(min)*min)); 
    }
    T rhs_max() const { return T(std::sqrt(pni::type_info<T>::max())); }

    T lhs_min() const { return rhs_min(); }
    T lhs_max() const { return rhs_max(); } 
};

template<typename T> struct mult_ranges<std::complex<T>>
{
    mult_ranges<T> base_range;

    T rhs_min() const { return T(0.5)*base_range.rhs_min(); }
    T rhs_max() const { return T(0.5)*base_range.rhs_max(); }

    T lhs_min() const { return T(0.5)*base_range.lhs_min(); }
    T lhs_max() const { return T(0.5)*base_range.lhs_max(); } 
};

template<typename T> struct div_ranges
{
    T rhs_min() const { return T(1); }
    T rhs_max() const { return pni::type_info<T>::max()/T(2); }

    T lhs_min() const { return pni::type_info<T>::min()/T(2); }
    T lhs_max() const { return pni::type_info<T>::max()/T(2); } 
};

template<typename T> struct div_ranges<std::complex<T>>
{
    div_ranges<T> base_range;
    
    T rhs_min() const { return base_range.rhs_min(); }
    T rhs_max() const { return base_range.rhs_max(); }

    T lhs_min() const { return base_range.lhs_min(); }
    T lhs_max() const { return base_range.lhs_max(); } 
};

