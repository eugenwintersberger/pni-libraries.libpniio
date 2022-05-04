//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Sep 9, 2011
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
//
//
#pragma once

#include <limits>

#include <pni/types/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>


namespace pni{

    //!
    //! \ingroup type_classes
    //! \brief get minimum and maximum
    //! 
    //! This struct provides static methods to determine the minimum 
    //! and maximum provided by a type. This implementation provides 
    //! min and max functions for integer types. A specialized version for 
    //! floating point types exists too.
    //! 
    //! \tparam DataT data type
    //! \tparam is_float true if the type is a float type
    //!
    template<
             typename DataT,
             bool is_float=false
            >
    struct min_max
    {
        //!
        //! \brief return minimum
        //!
        //! Return the minimum possible value for an integer type.
        //! This function returns std::numeric_limits<IntegerT>::min().
        //!
        //! \return minimum value of a type
        //!
        static constexpr IntegerT min()
        {
            return std::numeric_limits<IntegerT>::min();
        }

        //--------------------------------------------------------------------
        //!
        //! \brief return maximum
        //!
        //! Return the maximum value of an integer point type. This function
        //! returns std::numeric_limits<IntegerT>::max().
        //!
        //! \return maximum value of a type
        //!
        static constexpr IntegerT max()
        {
            return std::numeric_limits<IntegerT>::max();
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
    //! \tparam FloatT data type
    //!
    template<typename FloatT> struct min_max<FloatT,true>
    {
        //! 
        //! \brief get minimum
        //! 
        //! For floating point numbers this function returns -max() which is 
        //! different from the std::numerics_<FloatT> template implemented in the
        //! STL.
        //! 
        //! \return minimum value of a float type
        //!
        static constexpr FloatT min()
        {
            return -std::numeric_limits<FloatT>::max(); 
        }

        //--------------------------------------------------------------------
        //!
        //! \brief get maximum
        //! 
        //! Returns the maximum value for a floating point type. This function
        //! simply returns std::numeric_limits<FloatT>::max().
        //!
        //! \return maximum value of a float type
        //!
        static constexpr FloatT max()
        {
            return std::numeric_limits<FloatT>::max();
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
    //! \tparam GeneralT data type for which information is required
    //!
    template<typename GeneralT> 
    struct type_info
    {
        //==================public types=======================================
        //! the type of GeneralT
        typedef GeneralT type;        
       
        //! the base type (only interesting for complex types)
        typedef GeneralT base_type;    
        
        //=================static members======================================
        //! size of the type in bytes
        static const size_t size = sizeof(GeneralT); 

        //! true if the type is an integer, false otherwise
        static const bool is_integer = std::numeric_limits<GeneralT>::is_integer; 

        //! true if the type is signed, false otherwise
        static const bool is_signed = std::numeric_limits<GeneralT>::is_signed; 
        
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
        static bool is_negative(GeneralT value) { return value<0; }
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif

        //-----------------------------------------------------------------
        //! 
        //! \brief minimum limit
        //!
        //! returns the smallest value that can be represented by type GeneralT.
        //! \return lower limit of GeneralT
        //!
        static constexpr GeneralT min()
        {
            return min_max<GeneralT,std::is_floating_point<GeneralT>::value>::min();
        }

        //-----------------------------------------------------------------
        //! 
        //! \brief maximum limit
        //!
        //! Returns the largest value that can be represented by GeneralT.
        //!
        //! \return upper limit of GeneralT
        //!
        static constexpr GeneralT max() 
        { 
            return min_max<GeneralT,std::is_floating_point<GeneralT>::value>::max();
        }

    };


    //! \cond NO_API_DOC
    template<typename GeneralT> 
    struct type_info<std::complex<GeneralT>>
    {
        typedef std::complex<GeneralT> type;
        typedef GeneralT base_type;

        static const size_t size = sizeof(std::complex<GeneralT>);
        static const bool is_integer = type_info<GeneralT>::is_integer;
        static const bool is_signed = type_info<GeneralT>::is_signed;
        static const bool is_complex = true;

        //---------------------------------------------------------------------
        static bool is_negative(type ){ return false; }

        //---------------------------------------------------------------------
        //! return the minimum value of the Complex32 type
        static constexpr GeneralT min() { return type_info<GeneralT>::min(); }

        //---------------------------------------------------------------------
        //! return the maximum value of the Complex32 type
        static constexpr GeneralT max() { return type_info<GeneralT>::max(); }

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

    template<> struct type_info<hdf5::datatype::EBool>
    {
        typedef hdf5::datatype::EBool type;
        typedef hdf5::datatype::EBool base_type;

        static const size_t size = sizeof(bool);
        static const bool is_integer = true;
        static const bool is_signed = false;
        static const bool is_complex = false;

        static bool is_negative(type) { return false; }

        static type min() { return hdf5::datatype::EBool::False; }

        static type max() { return hdf5::datatype::EBool::True; }

    };
    //! \endcond

//end of namespace
}
