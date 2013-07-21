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
 * Created on: Jul 19, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "xml_node.hpp"
#include "../nxvariant.hpp"
#include "../utils/types.hpp"
#include "shape2dim.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
    using namespace pni::io::nx;

    template<typename VTYPE> node  field2xml(VTYPE &field)
    {
        node field_node;
        auto field_name = get_name(field);
        string field_type = typeid2str[get_type(field)];

        
        field_node.put("<xmlattr>.name",field_name);
        field_node.put("<xmlattr>.type",field_type);

        auto shape = get_shape<shape_t>(field);
        if(shape.size())
            field_node.add_child("dimensions",shape2dim(shape));

        if((get_rank(field)==1)&&(get_type(field)==type_id_t::STRING))
        {
            string buffer;
            read(field,buffer);
            field_node.put_value(buffer);
        }

        return field_node;
    }

    //-------------------------------------------------------------------------
    template<typename VTYPE> node group2xml(const VTYPE &group)
    {
        node group_node;
        auto group_name = get_name(group);
        auto group_class = get_class(group);

        group_node.put("<xmlattr>.name",group_name);
        group_node.put("<xmlattr>.type",group_class);

        return group_node;
    }

    //-------------------------------------------------------------------------
    template<typename VTYPE> node attribute2xml(const VTYPE &attr)
    {
        node attr_node;

        auto attr_name = get_name(attr);
        string attr_type = typeid2str[get_type(attr)];

        attr_node.put("<xmlattr>.name",attr_name);
        attr_node.put("<xmlattr>.type",attr_type);

        //read scalar string attributes
        if((get_rank(attr)==0) && 
           (get_type(attr)==type_id_t::STRING))
        {
            string buffer;
            read(attr,buffer);
            std::cout<<buffer<<std::endl;
            attr_node.put_value(buffer);
        }

        return attr_node;
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowleve_utils
    \brief nexus to XML conversion

    Converts the structure of a Nexus tree as stored below p into a XML tree
    strucure and stores it below n. 
    \tparam VTYPE variant type with the root object
    \param p parent object 
    \param n XML node
    */
    template<typename VTYPE> void nexus2xml(const VTYPE &p,node &n)
    {
        typedef std::vector<VTYPE> vector_t;
        node child;
        string key;
        if(is_field(p))
        {
            key = "field";
            child = n.add_child("field",field2xml(p));
        }
        else if(is_group(p))
        {
            key = "group";
            //add the actual group to the parent node
            child =  group2xml(p);

            //obtain al child nodes
            vector_t objects;
            get_children(p,objects);

            //iterate over the children 
            for(auto o: objects) nexus2xml(o,child);
        }

        //in the end we have to add attributes
        vector_t attributes;
        get_attributes(p,attributes);
        for(auto a: attributes)
        {
            if(get_name(a) == "NX_class") continue;
            child.add_child("attribute",attribute2xml(a));
        }
            
        //now everything is done and we have to 
        n.add_child(key,child);
    }

//end of namespace
}
}
}
}
