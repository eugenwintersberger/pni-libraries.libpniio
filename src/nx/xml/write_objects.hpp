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

#include <vector>
#include "xml_node.hpp"
#include "../nxvariants.hpp"
#include "../utils/types.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
    using namespace pni::io::nx;

    template<typename VTYPE> node  field2xml(const VTYPE &field)
    {
        node field_node;
        auto field_name = get_name(field);
        string field_type = typeid2str[get_type(field)];

        
        field_node.put("<xmlattr>.name",field_name);
        field_node.put("<xmlattr>.type",field_type);

        auto shape = get_shape(field);
        if(shape.size())
            field_node.add_child("dimensions",shape2dim(shape));

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

        return node;
    }

    //-------------------------------------------------------------------------
    template<typename VTYPE> node attribute2xml(const VTYPE &attr)
    {

    }

    //-------------------------------------------------------------------------
    template<typename VTYPE> void write_objects(const VTYPE &p,node &n)
    {
        typedef std::vector<VTYPE> vector_t;
        node child;
        if(is_field(p))
        {
            child = n.add_child("field",field2xml(p));
        }
        else if(is_group(p))
        {
            //add the actual group to the parent node
           child =  n.add_child("group",group2xml(p));

           //obtain al child nodes
           vector_t objects;
           get_children(p,objects);

           //iterate over the children 
           for(auto o: objects) write_objects(o,child);
        }

        //in the end we have to add attributes
        vector_t attributes;
        get_attributes(p,attributes);
        for(auto a: attributes)
            child.add_child("attribute",attribute2xml(a));
        

    }

//end of namespace
}
}
}
}
