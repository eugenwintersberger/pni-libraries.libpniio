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
   
    template<typename T>
    struct float_policy : boost::spirit::karma::real_policies<T>
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int floatfield(T n)
        {
            return 0;
        }
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int precision(T n)
        {
            return std::numeric_limits<T>::digits10;
        }
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static bool trailing_zeros(T n)
        {
            return false;
        }
#pragma GCC diagnostic pop
    };

    //------------------------------------------------------------------------
    template<typename T> 
    struct imag_policy : boost::spirit::karma::real_policies<T>
    {
        typedef boost::spirit::karma::real_policies<T> base_type;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int floatfield(T n)
        {
            return 0;
        }
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static int precision(T n)
        {
            return std::numeric_limits<T>::digits10;
        }
#pragma GCC diagnostic pop

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
