/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Utilty functions and function templates concerning NXField objects.
 *
 * Created on: Jul 9, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/exceptions.hpp>
#include <pni/core/type_id_map.hpp>
#include <pni/core/id_type_map.hpp>
#include "types.hpp"

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check type
    
    Checks wether or not an object providing a type_id() method is of a
    particular type. This function does not throw an exception but rather
    returns true if the types match and false otherise.

    \code{.cpp}
    auto field = ....;

    //check if field is of float64 type
    if(!check_type<float64>(field))
    {
        //do some error handling
    }
    \endcode
    \tparam T type against which to check
    \tparam TT object type
    \param o instance of TT whose type shall be checked
    \return true if the object is of the requested type
    */
    template<typename T,typename TT>
    bool check_type(const TT &o)
    {
        return o.type_id() == type_id_map<T>::type_id;
    }
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check type
    
    Checks whether or not an object providing a type_id() method is of a
    particular type. Here the type to check is not determined by a template
    parameter but rather by its string representation. This allows easy runtime
    checks. This function returns true if the object is of the requested type,
    false otherwise

    \code{.cpp}
    auto field = ....;

    //check if field is of float64 type
    if(!check_type(field,"float64"))
    {
        //do some error handling
    }
    \endcode
    \tparam TT object type
    \param o instance of TT whose type shall be checked
    \param s string representation of the requested type
    \return true if the object is of the requested type
    */
    template<typename TT> 
    bool check_type(const TT &o,const string &s)
    {
        return o.type_id() == str2typeid[s];
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check type
    
    Checks wether or not an object providing a type_id() method is of a
    particular type. If the types do not match an exception is thrown.
    This function is particularly useful in IO routines where a type mismatch at
    a particular location in the code should throw an exception. 
    The last parameter is the exception record at the location in the calling
    function. This shows where in your code the exception was thrown rather than
    the location in check function itself (which is mostly unimportant). 

    \code{.cpp}
    auto field = ....;

    check_type<float64>(field,EXCEPTION_RECORD);
    \endcode

    \tparam T type against which to check
    \tparam TT object type
    \param o instance of TT whose type shall be checked
    \param r exception record of the caller
    \return true if the object is of the requested type
    */
    template<typename T,typename TT>
    void check_type(const TT &o,const exception_record &r)
    {
        type_id_t id = type_id_map<T>::type_id;
        if(!check_type<T>(o))
        {
            std::stringstream ss;
            ss<<"Object is not of type "<<id<<"!";
            throw type_error(r,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check type
    
    Checks wether or not an object providing a type_id() method is of a
    particular type. If the types do not match an exception is thrown.
    This function is particularly useful in IO routines where a type mismatch at
    a particular location in the code should throw an exception. 
    The last parameter is the exception record at the location in the calling
    function. This shows where in your code the exception was thrown rather than
    the location in check function itself (which is mostly unimportant). 
    The type is passed in its string representation. 

    \code{.cpp}
    auto field = ....;

    check_type(field,"float64",EXCEPTION_RECORD);
    \endcode

    \tparam TT object type
    \param o instance of TT whose type shall be checked
    \param s string representation of the type
    \param r exception record of the caller
    \return true if the object is of the requested type
    */
    template<typename TT>
    void check_type(const TT &o,const string &s,const exception_record &r)
    {
        if(!check_type(o,s))
        {
            std::stringstream ss;
            ss<<"Object is not of type "<<str2typeid[s]<<"!";
            throw type_error(r,ss.str());
        }
    }

//end of namespace
}
}
}
