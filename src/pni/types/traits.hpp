//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 29, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types/types.hpp>
#include <boost/mpl/contains.hpp>

#include <pni/windows.hpp>

namespace pni{

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check integer type
    //! 
    //! Set the value member to true if T is an integer type, otherwise value
    //! will be false.
    //!
    //! \tparam T type to check
    //!
    template<typename T> struct is_integer_type
    {
        //! true if T is an integer, false otherwise
        static const bool value = boost::mpl::contains<integer_types,T>::value;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check float type
    //!
    //! Set the value member to true if T is a float type, otherwise value 
    //! will be false.
    //!
    //! \tparam T type to check
    //!
    template<typename T> struct is_float_type
    {
        //! true if T is a floating point type, false otherwise
        static const bool value = boost::mpl::contains<float_types,T>::value;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check complex type
    //! 
    //! Set the value  member to true if T is a complex number type, otherwise
    //! value will be false.
    //!
    //! \tparam T type to check. 
    //!
    template<typename T> struct is_complex_type
    {
        //! true if T is a complex type, false otherwise 
        static const bool value = boost::mpl::contains<complex_types,T>::value;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check numeric type
    //!
    //! Set the value member to true if T is a numeric type, otherwise value
    //! will be false. Numeric types are either integer, float, or complex
    //! types.
    //!
    //! \tparam T type to check
    //!
    template<typename T> struct is_numeric_type
    {
        //! true if T is a numeric type, false otherwise
        static const bool value = boost::mpl::contains<numeric_types,T>::value;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check non numeric type
    //! 
    //! Set the value member to true if T is one of the non numeric types.
    //! For all other types value will be false. Non numeric types are 
    //! bool, binary, and none. 
    //!
    //! \tparam T type to check
    //! 
    template<typename T> struct is_non_numeric_type
    {
        //! true if T is not a numeric type, false otherwise 
        static const bool value =
            boost::mpl::contains<non_numeric_types,T>::value;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check primitive type
    //!
    //! Set the value member to true if T belongs to the primitive types 
    //! provided by libpninexus. For all other types value will be false. 
    //!
    //! \tparam T type to check
    //!
    template<typename T> struct is_primitive_type
    {
        //! true if T is a primitive type, false otherwise 
        static const bool value =  
            boost::mpl::contains<primitive_types,T>::value;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check numeric type
    //!
    //! Returns true if the type associated with tid belongs to the numeric 
    //! types. 
    //! 
    //! \param tid type ID of the type to check
    //! \return true if tid refers to a numeric type, false otherwise
    //!
    PNINEXUS_EXPORT bool is_numeric(type_id_t tid);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check integer type
    //! 
    //! Returns true if the type associated with tid belongs to the integer 
    //! types. 
    //!
    //! \param tid type ID of the type to check
    //! \return true if tid refers to an integer type, false otherwise
    //!
    PNINEXUS_EXPORT bool is_integer(type_id_t tid);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief check complex type
    //!
    //! Returns true if the type associated with tid belongs to the complex
    //! types. 
    //! 
    //! \param tid type ID of the type to check
    //! \return true if tid refers to a complex type, false otherwise
    //! 
    PNINEXUS_EXPORT bool is_complex(type_id_t tid);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check float type
    //! 
    //! Returns true if the type associated with the tid belongs to the 
    //! float types. 
    //!
    //! \param tid id of the type to check
    //! \return true if tid refers to a float type, false otherwise
    //!
    PNINEXUS_EXPORT bool is_float(type_id_t tid);
    
//end of namespace
}
