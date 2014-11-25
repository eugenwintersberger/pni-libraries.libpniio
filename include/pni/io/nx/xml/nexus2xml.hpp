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
// Created on: Jul 19, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "xml_node.hpp"
#include "../algorithms.hpp"
#include "shape.hpp"
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    /*
    We need to specify some things here
    .) how do we handle non-Nexus groups? This are groups without an NX_class
    attribute
    .) how do we handle data - read it or not.

       */

    using namespace pni::core;
    using namespace pni::io::nx;

    template<typename VTYPE> node  field2xml(VTYPE &field)
    {
        if(!is_field(field))
            throw pni::core::type_error(EXCEPTION_RECORD,
                    "["+get_path(field)+"] is not a field!");

        node field_node;
        auto field_name = get_name(field);
        string field_type = str_from_type_id(get_type(field));

        
        field_node.put("<xmlattr>.name",field_name);
        field_node.put("<xmlattr>.type",field_type);

        auto s = get_shape<shape_t>(field);
        if(s.size())
            field_node.add_child("dimensions",shape::to_xml(s));

        if((get_rank(field)==1)&&(get_type(field)==type_id_t::STRING))
        {
            string buffer;
            read(field,buffer); 
            boost::algorithm::trim(buffer);
            field_node.put_value(buffer);
        }

        return field_node;
    }

    //-------------------------------------------------------------------------
    //!
    //! \brief convert group to XML
    //! 
    //! Converts a stored Nexus group to its XML representation.
    //! 
    //! \throws invalid_object_error if the group is not valid
    //! \throws io_error if the groups name or class cannot be 
    //! retrieved
    //! \throws type_error if the class attribute is of an 
    //! invalid type
    //! \throws object_error in case of any other error
    //!
    //! \param group variant type with the group to convert
    //! \return XML node
    //!
    template<typename VTYPE> node group2xml(const VTYPE &group)
    {
        node group_node;
        auto group_name = get_name(group);
        string group_class;
        if(get_path(group) == "/") 
            group_class = "NXroot";
        else
            group_class = get_class(group);

        group_node.put("<xmlattr>.name",group_name);
        group_node.put("<xmlattr>.type",group_class);

        return group_node;
    }

    //-------------------------------------------------------------------------
    template<typename VTYPE> node attribute2xml(VTYPE &attr)
    {
        node attr_node;

        auto attr_name = get_name(attr);
        string attr_type = str_from_type_id(get_type(attr));

        attr_node.put("<xmlattr>.name",attr_name);
        attr_node.put("<xmlattr>.type",attr_type);

        //read scalar string attributes
        if((get_rank(attr)==0) && 
           (get_type(attr)==type_id_t::STRING))
        {
            string buffer;
            read(attr,buffer);
            attr_node.put_value(buffer);
        }

        return attr_node;
    }
    
    template<typename OTYPE>
    void create_attribute(const OTYPE &aparent,node &p)
    {
        for(auto a: aparent.attributes)
        {
            if(get_name(a) == "NX_class") continue;
            p.add_child("attribute",attribute2xml(a));
        }
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_lowleve_utils
    //! \brief nexus to XML conversion
    //! 
    //! Converts the structure of a Nexus tree as stored below p into a XML 
    //! tree strucure and stores it below n. 
    //! \tparam VTYPE variant type with the root object
    //! \param p parent object 
    //! \param n XML node
    //!
    template<typename VTYPE> void nexus2xml(const VTYPE &p,node &n)
    {
        node child;
        string key;
        if(is_field(p))
        {
            key = "field";
            child = field2xml(const_cast<VTYPE&>(p));
            create_attribute(as_field(p),child);
        }
        else if(is_group(p))
        {
            key = "group";

            //add the actual group to the parent node
            child =  group2xml(p);

            //iterate over the children 
            for(auto o: as_group(p)) nexus2xml(o,child);

            create_attribute(as_group(p),child);
        }
            
        //now everything is done and we have to 
        n.add_child(key,child);
    }

//end of namespace
}
}
}
}
