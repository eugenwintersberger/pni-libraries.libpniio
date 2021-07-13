//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ============================================================================
//
//  Created on: Jul 24, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <limits>
#include <functional>

#include <pni/error/exception_utils.hpp>
#include <pni/types.hpp>
#include <pni/utilities/sfinae_macros.hpp>

namespace pni{
namespace core{

#define CHECK_ARITHMETIC_SINGLE(type)\
    static_assert(std::is_arithmetic<typename type::value_type>::value || \
                  is_complex_type<typename type::value_type>::value,\
            "Arithemtic operations can only be used with arithmetic types!")

#define CHECK_ARITHMETIC_DOUBLE(type1,type2)\
    static_assert(\
            (std::is_arithmetic<typename type1::value_type>::value || \
             is_complex_type<typename type1::value_type>::value) && \
            (std::is_arithmetic<typename type2::value_type>::value || \
             is_complex_type<typename type2::value_type>::value), \
            "Arithemtic operations can only be used with arithmetic types!")

    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief single threaded inplace arithmetics
    //!
    //! This class provides static template functions used for inplace 
    //! arithmetics.  The first argument of all functions is the reference to 
    //! the original container (typically an array). 
    //! 
    struct inplace_arithmetics
    {
                 
        //==================inplace addition===================================
        //!
        //! \brief add scalar to array
        //!
        //! Element wise inplace addition of a scalar to an array
        /*!
        \code
        array_type array(...);
        typename array_type::value_type scalar(5);
         
        //performe something like array += scalar
        inplace_arithmetics::add(array,scalar);
        \endcode
        !*/
        //! 
        //! \tparam LTYPE array type
        //! \param a reference to an instance of LTYPE
        //! \param b scalar value of type LTYPE::value_type
        //!
        template<
                 typename LTYPE,
                 typename T,
                 typename = enable_if<or_t<
                           is_pod<T>,is_cmplx<T>
                           >>
                > 
        static void add(LTYPE &a,T b)
        {
            CHECK_ARITHMETIC_SINGLE(LTYPE);

            size_t n = a.size();
            for(size_t i = 0;i<n;++i) a[i] += b;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief add array to array
        //!
        //!  Element wise inplace addition of two arrays
        /*!
        \code
        array_type1 a = ...;
        array_type2 b = ...;
        
        //computes a+=b;
        inplace_arithmetics::add(a,b);
        \endcode
        !*/
        //!
        //! \tparam LTYPE l.h.s. type 
        //! \tparam RTYPE r.h.s. type
        //! \param a reference to an array of type LTYPE 
        //! \param b reference to an array of type RTYPE
        //!
        template<
                 typename LTYPE,
                 typename RTYPE,
                 typename = enable_if<not_t<
                            or_t<is_pod<RTYPE>,is_cmplx<RTYPE>>
                            >>
                >
        static void add(LTYPE &a,const RTYPE &b)
        {
            CHECK_ARITHMETIC_DOUBLE(LTYPE,RTYPE);
            size_t n = a.size();
            for(size_t i=0;i<n;++i) a[i] += b[i];
        }

        //==================inplace subtraction===============================
        //!
        //! \brief subtract scalar from array
        //!
        //! Element wise subtraction of a scalar from an array
        /*!
        \code
        array_type a = ...;
        typename array_type::value_type s(1.);
        
        //compuate a+=scalar;
        inplace_arithmetics::sub(a,s);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b scalar value on the r.h.s.
        //!
        template<
                 typename LTYPE,
                 typename T,
                 typename = enable_if<or_t< 
                            is_pod<T>,is_cmplx<T> 
                            >>
                >
        static void sub(LTYPE &a,T b)
        {
            CHECK_ARITHMETIC_SINGLE(LTYPE);
            size_t n = a.size();
            for(size_t i=0;i<n;++i) a[i] -= b;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief subtract array from array
        //!
        //! Element wise inplace subtraction of a scalar from an array.
        /*!
        \code
        array_type1 a = ...;
        array_type2 b = ...;
        
        //compute a-=b;
        inplace_arithmetics::sub(a,b);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \tparam RTYPE r.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b reference to the r.h.s.
        //!
        template<
                 typename LTYPE,
                 typename RTYPE,
                 typename = enable_if<not_t<
                            or_t<is_pod<RTYPE>,is_cmplx<RTYPE>>
                            >>
                >
        static void sub(LTYPE &a,const RTYPE &b)
        {
            CHECK_ARITHMETIC_DOUBLE(LTYPE,RTYPE);
            size_t n = a.size();
            for(size_t i=0;i<n;++i) a[i] -= b[i];
        }


        //=====================inplace multiplication======================
        //!
        //! \brief multiply array with scalar
        //!
        //! Element wise inplace multiplication of an array with a scalar
        /*!
        \code
        array_type1 a = ...;
        typename array_type1::value_type s(5);
        
        //compute a *= s;
        inplace_arithmetics::mult(array,scalar);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b scalar r.h.s. value
        //!
        template<
                 typename LTYPE,
                 typename T,
                 typename = enable_if<or_t< 
                            is_pod<T>,is_cmplx<T> 
                            >>
                >
        static void mult(LTYPE &a,T b)
        {
            CHECK_ARITHMETIC_SINGLE(LTYPE);
            size_t n=a.size();
            for(size_t i=0;i<n;++i) a[i] *= b;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief multiply array by array
        //!
        //! Element wise inplace multiplication of two arrays
        /*!
        \code
        array_type1 a = ...;
        array_type2 b = ...;
        
        //compuate a *= b;
        inplace_arithemtics::mult(a,b);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \tparam RTYPE r.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b reference to the r.h.s.
        //!
        template<
                 typename LTYPE,
                 typename RTYPE,
                 typename = enable_if<not_t<
                            or_t<is_pod<RTYPE>,is_cmplx<RTYPE>>
                            >>
                >
        static void mult(LTYPE &a,const RTYPE &b)
        {
            CHECK_ARITHMETIC_DOUBLE(LTYPE,RTYPE);
            size_t n=a.size();
            for(size_t i=0;i<n;++i) a[i] *= b[i];
        }
        
        //=====================inplace division============================
        //!
        //! \brief divide array with scalar
        //!
        //! Element wise inplace division of an array with a scalar
        /*!
        \code
        array_type a = ...;
        typename array_type::value_type s(4.);
        
        //compute a /= s;
        inplace_arithmetics::div(a,s);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b scalar r.h.s. value
        //!
        template<
                 typename LTYPE,
                 typename T,
                 typename = enable_if<or_t< 
                            is_pod<T>,is_cmplx<T> 
                            >>
                >
        static void div(LTYPE &a,T b)
        {
            CHECK_ARITHMETIC_SINGLE(LTYPE);
            size_t n = a.size();
            for(size_t i=0;i<n;++i) a[i] /= b;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief divide array by array
        //!
        //! Element wise inplace division of two arrays. 
        /*!
        \code
        array_type1 a = ...;
        array_type2 b = ...;
        
        //compuate a /= b;
        inplace_arithemtics::div(a,b);
        \endcode
        !*/
        //! \tparam LTYPE l.h.s. array type
        //! \tparam RTYPE r.h.s. array type
        //! \param a reference to the l.h.s.
        //! \param b reference to the r.h.s.
        //!
        template<
                 typename LTYPE,
                 typename RTYPE,
                 typename = enable_if<not_t<
                            or_t<is_pod<RTYPE>,is_cmplx<RTYPE>>
                            >>
                >
        static void div(LTYPE &a,const RTYPE &b)
        {
            CHECK_ARITHMETIC_DOUBLE(LTYPE,RTYPE);
            size_t n = a.size();
            for(size_t i=0;i<n;++i) a[i] /= b[i];
        }
    };

//end namespace
}
}
