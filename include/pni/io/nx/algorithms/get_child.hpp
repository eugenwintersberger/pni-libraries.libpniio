//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 1, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nximp_code.hpp"
#include "../nxobject.hpp"
#include "object_predicates.hpp"
#include "iterators.hpp"
#include "is_group.hpp"
#include "get_parent.hpp"
#include "is_valid.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get child by name and/or class
    //!
    //! Returns the child of a group which is determined by its name and/or
    //! group. 
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the object is not an nxgroup instance or the
    //! nxobject instance does not store a group 
    //! \throws key_error if an object which satisifies the requested name
    //! and class could not be found
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE group or nxobject instance
    //! 
    //! \param o nxgroup or nxobject instance
    //! \param n name of the child
    //! \param c class of the object
    //!
    //! \return child as instance of nxobject
    //!
    template<typename OTYPE> 
    auto get_child(const OTYPE &o,const pni::core::string &n,
                   const pni::core::string &c="")
    ->decltype(get_parent(o))
    {
        using namespace pni::core;
        typedef decltype(get_parent(o)) object_type;
        
        object_type object(o); //convert the input always to nxobject
        if(!is_group(object))
            throw type_error(EXCEPTION_RECORD,"Function expects a group!");
            
        if(!n.empty()) //if object name is given
        {
            if(!c.empty()) //if object class is given
                return get_object_by_name_and_class(object,n,c);            
            else  //if no object class is given            
                return get_object_by_name(object,n);                
        }
        else if(!c.empty()) //if only the class is provided by the user        
            return get_object_by_class(object,c);                    
        
        //if the user has neither provided a name or a class there is 
        //something wrong
        throw value_error(EXCEPTION_RECORD,
            "get_child() requires a name or a class for the search!");        
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get child by index
    //! 
    //! Get a child by its numerical index. The parent object is an instance 
    //! of nxgroup. 
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws index_error if index exceeds total number of children
    //! \throws type_error if the type of a child is not supported
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID
    //! 
    //! \param parent instance of the parent object
    //! \param index numerical index of the requested child
    //! 
    //! \return child instance as nxobject
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    auto get_child(const OTYPE<IMPID> &parent,size_t index)
    ->decltype(get_parent(parent))
    {
        using group_type = typename nxobject_trait<IMPID>::group_type;

        static_assert(std::is_same<group_type,OTYPE<IMPID>>::value,
                      "Parent type must be an instance of nxgroup!");

        return parent.at(index);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get child by index 
    //!
    //! This template function takes an instance of nxobject wrapping a group
    //! as a parent. If the wrapped object is not a group a type_error 
    //! exception is thrown. 
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws index_error if the index exceeds the total number of children
    //! \throws type_error if the parent is not a group or the child type is 
    //! not supported
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! 
    //! \param parent instance of nxobject with the parent group
    //! \param index the numerical index of the requested child
    //! 
    //! \return child instance as nxobject
    //! 
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE 
            >
    auto get_child(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &parent,size_t index)
    ->decltype(get_parent(parent))
    {
        using namespace pni::core;
        if(!is_group(parent))
            throw type_error(EXCEPTION_RECORD,"Parent must be a group");

        return get_child(as_group(parent),index);
    }

//end of namespace
}
}
}
