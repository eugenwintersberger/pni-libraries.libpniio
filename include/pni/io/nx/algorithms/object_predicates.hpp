//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 12, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject_traits.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include <type_traits>
#include <functional>

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_internal_code
    //! \brief object predicates 
    //! 
    //! This template class provides predicate methods for object selection. 
    //! 
    //! \tparam OTYPE object type
    //!
    template<typename OTYPE> struct object_predicates
    {
        typedef OTYPE object_type;
        typedef std::function<bool(const object_type &o)> function_type;
        typedef object_predicates<OTYPE> predicate_type;

        //--------------------------------------------------------------------
        //!
        //! \brief name predicate
        //!
        //! This predicate function returns true for a name match. This
        //! predicate can be applied to fields as well as groups.
        //!
        //! \throws invalid_object_error if the object is not valid
        //! \throws type_error if the type does not support name retrieval
        //! \throws io_error if name retrieval fails
        //! \throws object_error in case of any other error
        //!
        //! \param o object to check
        //! \param name the name to match
        //! \return true of o's name matches name
        //!
        static
        bool by_name(const OTYPE &o,const string &name)
        {
            return get_name(o) == name;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief class match
        //!
        //! This predicate function returns true for a class match. If the 
        //! object is a field type the predicate returns false in any case.
        //! Naturally this predicate makes only sense for groups.
        //!
        //! \throws invalid_object_error if the object is not valid
        //! \throws shape_mismatch_error if the NX_class attribute is not 
        //! scalar
        //! \throws type_error if NX_class is of inappropriate type
        //! \throws io_error if attribute retrieval failed
        //! \throws object_error in case of any other error
        //! 
        //! \param o object to check
        //! \param c Nexus class name
        //! \return true if o's NX_class attribute matches c
        //!
        static
        bool by_class(const OTYPE &o,const string &c)
        { 
            if(is_field(o)) return false;
            return is_class(o,c);
        }

        //--------------------------------------------------------------------
        //!
        //! \brief name and class match
        //!
        //! This function returns true in the case of a name and class match.
        //! like the has_class predicate it makes only sense for groups.
        //!
        //! \throws invalid_object_error if the group is not valid
        //! \throws shape_mismatch_error if the NX_class attribute is not a 
        //! scalar
        //! \throws type_error if the NX_class attribute is not of string type
        //! \throws io_error if name or class retrieval fails
        //! \throws object_error in case of any other error
        //!
        //! \param o object to check
        //! \param n object name to match
        //! \param c object class to match
        //! \return true if o's class and name match n and c, false otherwise
        //!
        static
        bool by_name_and_class(const OTYPE &o,const string &n,const string &c)
        {
            if(is_field(o)) return false;
            return by_name(o,n) && by_class(o,c);
        }

        //--------------------------------------------------------------------
        //!
        //! \brief create predicate function
        //!
        //! Static function creating a predicate function which can be used 
        //! in an STL algorithm. 
        //!
        //! \throws key_error value_error if n and c are empty
        //! \throws object_error if the predicate creation fails for some 
        //! other reason.
        //! 
        //! \param n name to look for 
        //! \param c Nexus type to look for
        //! \return predicate function
        //!
        static function_type create(const string &n,const string &c)
        {
            using std::placeholders::_1;

            if(n.empty() && c.empty())
                throw key_error(EXCEPTION_RECORD,"'name' and 'class' field are"
                        "emtpy - do not know what to search for!");
            else if((!n.empty()) && (!c.empty()))
                //search for name and class
                return std::bind(&predicate_type::by_name_and_class,_1,n,c);
            else if((!n.empty()) && (c.empty()))
                return std::bind(&predicate_type::by_name,_1,n);
            else if((n.empty()) && (!c.empty()))
                return std::bind(&predicate_type::by_class,_1,c);
            else
                throw value_error(EXCEPTION_RECORD,
                        "Could not create predicate function!");
        }

    };



//end of namespace
}
}
}
