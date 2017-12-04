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

#include "../nxobject_traits.hpp"
#include "object_predicates.hpp"
#include "iterators.hpp"

namespace pni{
namespace io{
namespace nx{
    
    
    template<
             typename CTYPE,
             typename OTYPE
            >
    void get_children(const OTYPE &p,const string &c,CTYPE &container)
    {
        typedef decltype(get_parent(p)) object_type; 
        
        object_type parent(p); //whatever OTYPE is we go here for an object 
                               //type
                               
        //check if the parent is a group instance and throw an exception
        //if otherwise
        if(!is_group(parent))
            throw type_error(EXCEPTION_RECORD,
                "The parent object must be a group!");
                
        //iterate over all children
        for(auto iter = begin(parent); iter!=end(parent);++iter)
        {
            //shortcut evaluation - if is_group is false the class 
            //is not checked
            if(is_group(*iter) && is_class(*iter,c))
                container.push_back(*iter);
        }
        
    }

    //!
    //! \ingroup algorithm_code
    //! \brief get children with a common class
    //!
    //! Returns all children of a parent group which share a common class 
    //! type. The results will be stored in a container type provided by the
    //! user as a template paremeter.
    //! It is important to note that the only parameter we can search for here 
    //! is the base class type. As we are searching only within a single parent
    //! all names must be distinct.  Unlike the \c get_cild function template
    //! this template does not throw if no object matches the class type. 
    //! Instead, an empty container is returned.
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the object is not an nxgroup instance or the
    //! nxobject instance does not store a group 
    //! \throws object_error in case of any other error
    //!
    //! \tparam CTYPE container type to hold the results
    //! \tparam OTYPE group or nxobject instance
    //! 
    //! \param o nxgroup or nxobject instance
    //! \param c class of the object
    //!
    //! \return child as instance of nxobject
    //!
    template<
             typename CTYPE,
             typename OTYPE
            > 
    CTYPE get_children(const OTYPE &parent,const string &c)
    {
        CTYPE container;
        
        get_children(parent,c,container);
        
        return container;
    }


//end of namespace
}
}
}
