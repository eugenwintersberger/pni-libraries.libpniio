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
#ifdef _MSC_VER
#pragma warning(disable:4348)
#endif
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#ifdef _MSC_VER
#pragma warning(default:4348)
#endif

#include "float_policy.hpp"

namespace pni{
namespace io{

    //!
    //! \ingroup formatter_internal_classes
    //! \brief generator for complex numbers
    //!
    //! This is a karma generator for complex numbers. 
    //!
    //! \tparam OITER output iterator
    //! \tparam T base type for the copmlex type
    template<
             typename OITER,
             typename T
            >
    struct complex_generator : boost::spirit::karma::grammar<OITER,std::complex<T>()>
    {
        //!
        //! \brief get real part
        //! 
        //! This is a lazy function returning the real part of a complex 
        //! number.
        //! 
        struct get_real
        {
            //!
            //! \brief result type of the lazy function
            //! 
            template<typename Sig> struct result
            {
                typedef T type; //!< result type
            };

            //!
            //! \brief get real part
            //!
            //! This function template actually implements the extraction of 
            //! the real part from a complex number.
            //! 
            //! \tparam Arg argument type (must be a complex type)
            //! \param n complex input argument
            //! \return real part of the complex number
            //!
            template<typename Arg>
            T operator()(Arg const &n) const
            {
                return std::real(n);
            }
        };

        //--------------------------------------------------------------------
        //!
        //! \brief get imaginary part
        //! 
        //! Lazy function returning the imaginary part of a complex number.
        //! 
        struct get_imag
        {
            //!
            //! \brief result type of the lazy function
            //! 
            template<typename Sig> struct result
            {
                typedef T type; //!< result type
            };

            //!
            //! \brief get imaginary part
            //! 
            //! This function template actually implements the extraction 
            //! of the imaginary part of the complex number.
            //! 
            //! \tparam Arg argument type
            //! \param n complex input argument
            //! \return imaginary part of input n
            //! 
            template<typename Arg>
            T operator()(Arg const &n) const
            {
                return std::imag(n);
            }

        };

        //-------------------------------------------------------------------
        //! instance of the get_real lazy function
        boost::phoenix::function<get_real> real;
        //! instance of the get_imag lazy function
        boost::phoenix::function<get_imag> imag;

        //! rule to produce the real part
        boost::spirit::karma::real_generator<T,float_policy<T>> float_rule; 
        //! rule to produce the imaginary part
        boost::spirit::karma::real_generator<T,imag_policy<T>>  imag_rule;
        //! total rule for complex numbers
        boost::spirit::karma::rule<OITER,std::complex<T>()>     complex_rule; 

        //!
        //! \brief default constructor
        //! 
        //! Default constructor for the complex number rule. 
        //!
        complex_generator(): complex_generator::base_type(complex_rule)
        {
            using boost::spirit::karma::_1;
            using boost::spirit::karma::_val;

            complex_rule = float_rule[_1 = real(_val)]<<
                           imag_rule[_1 = imag(_val)];
        }
        
    };

}
}
