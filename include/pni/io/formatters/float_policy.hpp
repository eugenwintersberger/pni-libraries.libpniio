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
#include <boost/spirit/include/karma_real.hpp>

namespace pni{
namespace io{
  
    //!
    //! \ingroup formatter_classes
    //! \brief policy for real numbers
    //!
    //! Formatting policy for real numbers. The current policy differs 
    //! from the C++ default in two ways
    //! \li by default always the scientific format is used
    //! \li if required the ouput precision is the full precision of the type
    //!
    template<typename T>
    struct float_policy : boost::spirit::karma::real_policies<T>
    {
        //--------------------------------------------------------------------
        //!
        //! \brief use scientific format by default
        //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int floatfield(T n)
        {
            return 0;
        }
#pragma GCC diagnostic pop

        //--------------------------------------------------------------------
        //! 
        //! \brief set output to full number precision
        //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int precision(T n)
        {
            return std::numeric_limits<T>::digits10;
        }
#pragma GCC diagnostic pop

    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief real policy for imaginary part 
    //! 
    //! This is a special policy for real numbers which represent the imaginary 
    //! part of a complex number. It shares all the properties of the default
    //! float_policy but always adds the sign in front of the integer part
    //! and seperates the sign by an 'I' to indicate the imaginary part of a
    //! complex number
    template<typename T> 
    struct imag_policy : boost::spirit::karma::real_policies<T>
    {
        //! policy to parse the base type
        typedef boost::spirit::karma::real_policies<T> base_type;

        //--------------------------------------------------------------------
        //!
        //! \brief use scientific format by default
        //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int floatfield(T n)
        {
            return 0;
        }
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        //--------------------------------------------------------------------
        //!
        //! \brief always use maximum precision of required
        //!
        static int precision(T n)
        {
            return std::numeric_limits<T>::digits10;
        }
#pragma GCC diagnostic pop

        //--------------------------------------------------------------------
        //!
        //! \brief add sign and I in front of the output
        //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        template<typename OITER>
        static bool integer_part(OITER &sink,T n,bool sign,bool force_sign) 
        {
            if(sign)
                *(sink++) = '-';
            else
                *(sink++) = '+';

            *(sink++) = 'I';

            return base_type::integer_part(sink,n,false,false);
        }
#pragma GCC diagnostic pop

    };


//end of namespace
}
}
