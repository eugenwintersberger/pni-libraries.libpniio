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

#include <limits>
#include <iostream>
#ifdef _MSC_VER
#pragma warning(disable:4348)
#endif
#include <boost/spirit/include/karma_real.hpp>
#ifdef _MSC_VER
#pragma warning(default:4348)
#endif

namespace pni{
namespace io{
  
    //!
    //! \ingroup formatter_internal_classes
    //! \brief policy for real numbers
    //!
    //! Formatting policy for real numbers. The current policy differs 
    //! from the C++ default in two ways
    //! 
    //! * by default always the scientific format is used
    //! * if required the ouput precision is the full precision of the type
    //! 
    //! The idea behind this policy is to avoid accidental truncations of 
    //! floating point numbers during ASCII output.
    //! This policy is used in all cases where a floating point type should 
    //! be converted to a character string.
    //! 
    //! \tparam T floating point type 
    //! 
    template<typename T>
    struct float_policy : boost::spirit::karma::real_policies<T>
    {
        //--------------------------------------------------------------------
        //!
        //! \brief use scientific format by default
        //!
        static int floatfield(T)
        {
            return 0;
        }

        //--------------------------------------------------------------------
        //! 
        //! \brief set output to full number precision
        //!
        static int precision(T)
        {
            return std::numeric_limits<T>::digits10;
        }

    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_internal_classes
    //! \brief real policy for imaginary part 
    //! 
    //! This is a special policy for real numbers representing the imaginary 
    //! part of a complex number. It shares all the properties of the default
    //! float_policy but adds the sign in front of the integer part
    //! and separates the sign by an 'I' from the residual floating point
    //! number.
    //! 
    //! \tparam T floating point type
    //! 
    template<typename T> 
    struct imag_policy : boost::spirit::karma::real_policies<T>
    {
        //! policy to parse the base type
        typedef boost::spirit::karma::real_policies<T> base_type;

        //--------------------------------------------------------------------
        //!
        //! \brief use scientific format by default
        //!
        static int floatfield(T)
        {
            return 0;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief always use maximum precision of required
        //!
        static int precision(T)
        {
            return std::numeric_limits<T>::digits10;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief add sign and I in front of the output
        //! 
        //! Adds the leading sign and the `I` to the output.
        //!
        //! \tparam OITER output iterator type
        //! \param sink output iterator
        //! \param n number 
        //! \param sign true if a sign is set 
        //! \return true if writting the output was successful, false
        //!         otherwise
        //! 
        template<typename OITER>
        static bool integer_part(OITER &sink,T n,bool sign,bool ) 
        {
            if(sign)
                *(sink++) = '-';
            else
                *(sink++) = '+';

            *(sink++) = 'I';

            return base_type::integer_part(sink,n,false,false);
        }
    };


//end of namespace
}
}
