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
 * Created on: Jul 2, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "../nxpath_utils.hpp"
#include "../nxvariant_traits.hpp"
#include "get_parent.hpp"
#include "get_attribute.hpp"
#include "get_child.hpp"



namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup variant_code
    \brief get root 

    Return the root group of an object. This is quite usefull in cases where 
    an absolute path is used. 

    This function throws no exceptions.

    \tparam VTYPE variant type
    \param p reference to an instance of VTYPE
    \return an instance of object_types holding the root group
    */
    template<typename VTYPE>
    typename nxvariant_traits<typename nxvariant_member_type<VTYPE,0>::type>::object_types
    get_root(const VTYPE &p)
    {
        typedef typename nxvariant_member_type<VTYPE,0>::type first_type;
        typedef typename nxvariant_traits<first_type>::object_types object_types;

        if(get_name(p)=="/") return p;

        object_types root = p;
        do
        {
            root = get_parent(root);
        }while(get_name(root)!="/");

        return root;

    }

    //----------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief get object by name

    Return an object specified by a Nexus path. From the nature of a nexus file we
    can assume that every object in the path except the last one has to be a group
    as it must hold other objects. The function ignores the filename part of the
    nexus path. 

    It is crucial to understand how the function treates the nexus path. We
    start with the following path structure
    \code
    path = [object section][last object][@ attribute section]
    \endcode
    In the first step the function splits the path in two parts
    \code
    path1 = [object section]
    path2 = [last object][@ attribute section]
    \endcode
    This is done for the following reason: from the first object section we know
    that all of these objects must be groups (as they are containers). path1 is
    thus describing a group path to the last object which is described by path2. 
    The object referred to by path2 can be either a group or a field and the
    requested object can now either be the last object itself or an attribute
    attached to it. 

    If an attribute is requested nxattribute_error is thrown if the attribute
    does not exist.

    \throws attribute_error if the requested attribute was not found
    \throws nxgroup_error if parent object cannot be found
    \tparam VTYPE variant type
    \param p reference to instance of VTYPE
    \param path the nexus path to the object
    \return requested object
    */
    template<typename VTYPE> 
    typename nxvariant_traits<typename nxvariant_member_type<VTYPE,0>::type>::object_types 
    get_object(const VTYPE &p,const nxpath &path)
    {
        typedef typename nxvariant_member_type<VTYPE,0>::type first_type;
        typedef typename nxvariant_traits<first_type>::object_types object_types;
        nxpath group_path;
        nxpath target_path;
        object_types result;

        //split the original path into two sections
        split_last(path,group_path,target_path);

        //---------------------------------------------------------------------
        // Retrieve the group object referred to by group_path
        //---------------------------------------------------------------------
        //get the parent object - if the group_path is an absolute path the
        //parent object passed by the user is ignored and instead the root group
        //of the Nexus tree is used
        object_types parent;
        if(group_path.is_absolute())
            parent = get_root(p);
        else
            parent = p;
        
        //check validity of the parent object
        if(!is_valid(parent))
            throw nxgroup_error(EXCEPTION_RECORD,
                    "Object parent is not a valid Nexus object!");

        //walk through the group_path
        for(auto element: group_path)
        {
            if(element.first == ".") continue;
            if(element.first == "..")
            {
                parent = get_parent(parent);
                continue;
            }

            //check the validity of the newly obtained parent and throw an
            //exception if it is not valid
            if(!is_valid(parent = get_child(parent,element.first,element.second)))
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Cannot find parent object "
                        +string_from_path(group_path)+"!");
        }

        //---------------------------------------------------------------------
        // Retrieve the child object described by target_path from the parent
        // object referred to by group_path
        //---------------------------------------------------------------------

        //retrieve the child object and throw an exception if it cannot be found
        string target_name;
        string target_class;
        if(target_path.size())
        {
            target_name = target_path.begin()->first;
            target_class = target_path.begin()->second;
        }

        if(!is_valid(result = get_child(parent,target_name,target_class)))
            throw nxgroup_error(EXCEPTION_RECORD,
                    "Requested object is not valid!");

        //if target_path points to the attribute attached to the last object we
        //need to grab it - this section of code will throw nxattribute_error if
        //the requested attribute does not exist.
        if(!target_path.attribute().empty())
            result = get_attribute(result,target_path.attribute());

        return result;
    }

//end of namespace
}
}
}
