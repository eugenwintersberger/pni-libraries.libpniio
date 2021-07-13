//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 9, 2011
//     Author: Eugen Wintersberger
//
//
#pragma once

#include <limits>

#include <pni/types/types.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup type_classes
    //! \brief get minimum and maximum
    //! 
    //! This struct provides static methods to determine the minimum 
    //! and maximum provided by a type. This implementation provides 
    //! min and max functions for integer types. A specialized version for 
    //! floating point types exists too.
    //! 
    //! \tparam T data type
    //! \tparam is_float true if the type is a float type
    //!
    template<
             typename T,
             bool is_float=false
            >
    struct min_max
    {
        //!
        //! \brief return minimum
        //!
        //! Return the minimum possible value for an integer type.
        //! This function returns std::numeric_limits<T>::min().
        //!
        //! \return minimum value of a type
        //!
        static constexpr T min()
        {
            return std::numeric_limits<T>::min();
        }

        //--------------------------------------------------------------------
        //!
        //! \brief return maximum
        //!
        //! Return the maximum value of an integer point type. This function
        //! returns std::numeric_limits<T>::max().
        //!
        //! \return maximum value of a type
        //!
        static constexpr T max()
        {
            return std::numeric_limits<T>::max();
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get minimum and maximum for floats
    //! 
    //! Specialized version of the min_max template for determining the 
    //! minimum and maximum value of a floating point type.
    //! 
    //! \tparam T data type
    //!
    template<typename T> struct min_max<T,true>
    {
        //! 
        //! \brief get minimum
        //! 
        //! For floating point numbers this function returns -max() which is 
        //! different from the std::numerics_<T> template implemented in the
        //! STL.
        //! 
        //! \return minimum value of a float type
        //!
        static constexpr T min()
        {
            return -std::numeric_limits<T>::max(); 
        }

        //--------------------------------------------------------------------
        //!
        //! \brief get maximum
        //! 
        //! Returns the maximum value for a floating point type. This function
        //! simply returns std::numeric_limits<T>::max().
        //!
        //! \return maximum value of a float type
        //!
        static constexpr T max()
        {
            return std::numeric_limits<T>::max();
        }
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief type information class
    //! 
    //! class that describes properties of a  PNI type as defined in types.hpp.
    //! This template is used to obtain information about types in other 
    //! classes like arrays and scalars. Special overloads for complex and bool 
    //! types exist.
    //! 
    //! \tparam T data type for which information is required
    //!
    template<typename T> 
    struct type_info
    {
        //==================public types=======================================
        //! the type of T
        typedef T type;        
       
        //! the base type (only interesting for complex types)
        typedef T base_type;    
        
        //=================static members======================================
        //! size of the type in bytes
        static const size_t size = sizeof(T); 

        //! true if the type is an integer, false otherwise
        static const bool is_integer = std::numeric_limits<T>::is_integer; 

        //! true if the type is signed, false otherwise
        static const bool is_signed = std::numeric_limits<T>::is_signed; 
        
        //! true if the type represents a complex number, false otherwise
        static const bool is_complex = false; 

        //======================static member methods==========================
        //! 
        //! \brief sign check
        //!
        //! Method returns true if value is negative, false otherwise.
        //! \param value value for which to check the sign
        //! \return true if value<0, false otherwise
        //!
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif 
        static bool is_negative(T value) { return value<0; }
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif

        //-----------------------------------------------------------------
        //! 
        //! \brief minimum limit
        //!
        //! returns the smallest value that can be represented by type T.
        //! \return lower limit of T
        //!
        static constexpr T min()
        {
            return min_max<T,std::is_floating_point<T>::value>::min();
        }

        //-----------------------------------------------------------------
        //! 
        //! \brief maximum limit
        //!
        //! Returns the largest value that can be represented by T.
        //!
        //! \return upper limit of T
        //!
        static constexpr T max() 
        { 
            return min_max<T,std::is_floating_point<T>::value>::max();
        }

    };


    //! \cond NO_API_DOC
    template<typename T> 
    struct type_info<std::complex<T>>
    {
        typedef std::complex<T> type;
        typedef T base_type;

        static const size_t size = sizeof(std::complex<T>);
        static const bool is_integer = type_info<T>::is_integer;
        static const bool is_signed = type_info<T>::is_signed;
        static const bool is_complex = true;

        //---------------------------------------------------------------------
        static bool is_negative(type ){ return false; }

        //---------------------------------------------------------------------
        //! return the minimum value of the Complex32 type
        static constexpr T min() { return type_info<T>::min(); }

        //---------------------------------------------------------------------
        //! return the maximum value of the Complex32 type
        static constexpr T max() { return type_info<T>::max(); }

    };

    template<> struct type_info<binary>
    {
        typedef binary type;
        typedef binary base_type;

        static const size_t size = sizeof(binary);
        static const bool is_integer = true;
        static const bool is_signed = false;
        static const bool is_complex = false;

        static bool is_negative(type ) { return false; }

        static type min() { return 0; }
        static type max() { return 255; }

    };


    template<> struct type_info<bool_t>
    {
        typedef bool_t type;
        typedef bool_t base_type;

        static const size_t size = sizeof(bool);
        static const bool is_integer = true;
        static const bool is_signed = false;
        static const bool is_complex = false;

        static bool is_negative(type) { return false; }

        static type min() { return false; }

        static type max() { return true; }

    };
    //! \endcond

//end of namespace
}
}
