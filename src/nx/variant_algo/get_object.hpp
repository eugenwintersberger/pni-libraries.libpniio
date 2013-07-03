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
        }while(get_name(root)=="/");

        return root;

    }

    //----------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief get object by name

    Return an object specified by a Nexus path. From the nature of a nexus file we
    can assume that every object in the path except the last one has to be a group
    as it must hold other objects 
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

        split_last(path,group_path,target_path);

        //get the parent object 
        object_types parent;
        if(group_path.is_absolute())
            parent = get_root(p);
        else
            parent = p;

        for(auto element: group_path)
        {
            if(element.first == ".") continue;
            if(element.first == "..")
            {
                parent = get_parent(parent);
                continue;
            }

            parent = get_child(parent,element.first,element.second);
        }

        //having obtained the parent object we have to look now into it
        result = get_child(parent,target_path.begin()->first,
                                  target_path.begin()->second);

        if(!target_path.attribute().empty())
            result = get_attribute(result,target_path.attribute());

        return result;
    }

//end of namespace
}
}
}
