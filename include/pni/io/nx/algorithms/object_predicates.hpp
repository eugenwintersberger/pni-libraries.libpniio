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
    //! \ingroup algorithm_code
    //! \brief search for object by name
    //! 
    //! Search for an object stored below its parent by name. The parent must
    //! be an instance of nxgroup or nxobject wrapping a group instance. 
    //! IF the object could not be found a key_error exception is thrown. 
    //!
    //! \throws key_error if no object with the requested name exists
    //! \throws invalid_object_error if the parent is not a valid object
    //! \throws io_error in case of errors during object meta data retrieval 
    //! \throws object_error in case of any object construction or destruction
    //!                      problem
    //! 
    //! \param parent the parent object 
    //! \param name the name of the requested object
    //! 
    //! \return the requested object as an instance of nxobject
    template<typename OTYPE> 
    OTYPE get_object_by_name(const OTYPE &parent,const string &name)
    {
        auto group = as_group(parent);
        
        if(!group.has_child(name))
            throw key_error(EXCEPTION_RECORD,
                "Group has no child ["+name+"]!");
        
        return group[name];
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief search for object by name and class
    //! 
    //! This function searches for an object by its name and class. Obviously
    //! such an object can only be a group as fields do not have a class 
    //! attribute. 
    //!
    //! The function first tries to find an object with a matching name. 
    //! If it finds such an object it checks if it is a group and throws a 
    //! type_error exception if it is not. In the case of a group the 
    //! function continues to check if the group type matches. 
    //!
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws io_error in case of errors during retrieving object metadata
    //! \throws type_error if the object found by name is not a group
    //! \throws key_error if no object of the requested name and class 
    //!                   could be found
    //! \throws object_error in any case of errors during object creation,
    //!                      destruction, or copying 
    //!
    //! \tparam OTYPE object type
    //! \param parent the parent object
    //! \param name the name of the requested group
    //! \param c the class of the requested group
    //! \return a group object of matching name and class
    //!
    template<typename OTYPE>
    OTYPE get_object_by_name_and_class(const OTYPE &parent,
                                       const string &name,
                                       const string &c)
    {
        auto result = get_object_by_name(parent,name);
        
        if(is_field(result))
            throw type_error(EXCEPTION_RECORD,
                "Object is a field and thus does not have a class!");
        
        if(!is_class(result,c))
            throw key_error(EXCEPTION_RECORD,
                "No object ["+name+":"+c+"] found!");
                
        return result;        
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief find object by class
    //! 
    //! 
    template<typename OTYPE>
    OTYPE get_object_by_class(const OTYPE &parent,string c)
    {
        auto iter = std::find_if(begin(parent),end(parent),
                    [&c](const OTYPE &o) { 
                        if(is_field(o)) return false;
                        
                        return is_class(o,c);
                    });
                    
        if(iter == end(parent))
            throw key_error(EXCEPTION_RECORD,
                "No group of class ["+c+"] found!");
                
        return *iter;
    }


//end of namespace
}
}
}
