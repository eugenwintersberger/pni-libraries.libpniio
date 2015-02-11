//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Feb 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iterator>
#include <complex>
#include <pni/core/types.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "float_policy.hpp"

namespace pni{
namespace io{

    using namespace pni::core;
    using namespace boost::spirit;

    template<
             typename OITER,
             typename T
            >
    struct complex_generator : karma::grammar<OITER,std::complex<T>()>
    {
        struct get_real
        {
            template<typename Sig> struct result
            {
                typedef T type;
            };

            template<typename Arg>
            T operator()(Arg const &n) const
            {
                return std::real(n);
            }
        };

        struct get_imag
        {
            template<typename Sig> struct result
            {
                typedef T type;
            };

            template<typename Arg>
            T operator()(Arg const &n) const
            {
                return std::imag(n);
            }

        };

        boost::phoenix::function<get_real> real;
        boost::phoenix::function<get_imag> imag;

        karma::real_generator<T,float_policy<T>> float_rule; 
        karma::real_generator<T,imag_policy<T>>  imag_rule;
        karma::rule<OITER,std::complex<T>()>     complex_rule; 

        complex_generator(): complex_generator::base_type(complex_rule)
        {
            using karma::_1;
            using karma::_val;

            complex_rule = float_rule[_1 = real(_val)]<<
                           imag_rule[_1 = imag(_val)];
        }
        
    };

}
}
