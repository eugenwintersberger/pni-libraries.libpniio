//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 18, 2013
//     Author: Eugen Wintersberger
//
#pragma once

#include <map>
#include <pni/types/type_id_map.hpp>
#include <pni/utilities/sfinae_macros.hpp>
#include <functional>

#include <pni/windows.hpp>


namespace pni{
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief get_type_id version for complex numbers
    //! 
    //! Overloaded version of get_type_id for complex numbers.
    //!
    //! \tparam T base type for std::complex
    //! \return type ID of the complex type
    //!
    template<typename T> 
    type_id_t get_type_id(const std::complex<T> &)
    {
        return type_id_map<std::complex<T> >::type_id;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief get_type_id overload for binary data
    //! 
    //! Overloaded version of get_type_id for binary data.
    //! 
    //! \param v binary data 
    //! \return type ID for binary 
    //!
    PNINEXUS_EXPORT type_id_t get_type_id(const binary &v);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief get_type_id overload for bool_t data
    //!
    //! \param v boolean data
    //! \return typeID for bool_t
    //!
    PNINEXUS_EXPORT type_id_t get_type_id(const bool_t &v);


    //-------------------------------------------------------------------------
    //call this to obtain the type ID of a string value
    //! 
    //! \ingroup type_classes_internal
    //! \brief get_type_id overload for string data
    //! 
    //! Overloaded version of get_type_id for string data
    //! 
    //! \param v string data
    //! \return type ID for string type
    //! 
    PNINEXUS_EXPORT type_id_t get_type_id(const string &v);


    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes_internal
    //! \brief get_type_id for POD data
    //! 
    //! This version of get_type_id is used for POD (Plain Old Data). 
    //! 
    //! \tparam T data type
    //! \return type ID of T
    //!
    template<typename T > 
    type_id_t get_type_id(const T &,enable_if<is_pod<T>>* = 0)
    {
        return type_id_map<T>::type_id;
    }

    //-------------------------------------------------------------------------
    // if T is a container type use this function
    //! 
    //! \ingroup type_classes_internal
    //! \brief get_type_id for containers
    //! 
    //! In the case of continaer types get_type_id returns the type ID of 
    //! of the value_type. 
    //! 
    //! \tparam T container type
    //! \return type ID of T::value_type
    //!
    template<typename T> 
    type_id_t get_type_id(const T &,enable_if<not_t<is_pod<T>>>* = 0)
    {
        return type_id_map<typename T::value_type>::type_id;
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get type id of an object
    //!
    //! This function returns the type ID of an instance of an object. In the 
    //! case of scalar data the type if a variable is returned. If the 
    //! argument passed is a container the type id of the element type 
    //! is returned.
    //!
    //! \tparam T type if the object
    //! \return type ID 
    //!
    template<typename T> 
    type_id_t type_id(const T &)
    {
        typedef typename std::remove_const<
            typename std::remove_pointer<T>::type
            >::type  type;
        return get_type_id(type());
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get a type ID from a string
    //! 
    //! Returns the type ID for a particular string representation of a type. 
    //! If the string passed is not a valid type representation an exception 
    //! will be thrown.
    //!
    //! \throws key_error if the string does not describe a type
    //! \param s string representation of the type
    //! \return corresponding type ID
    //!
    PNINEXUS_EXPORT type_id_t type_id_from_str(const string &s);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get the string rep. for a type
    //!
    //! Returns the string representation for a type determined by its type 
    //! id. If the type determined by the ID does not have a string 
    //! representation an exception will be thrown. 
    //! 
    //! \throws key_error if the type has no string representation
    //! \param id type ID of the type
    //! \return string representation of the type
    //!
    PNINEXUS_EXPORT string str_from_type_id(type_id_t id);
   
//end of namespace
}
