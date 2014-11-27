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
//
// Created on: Nov 25, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>

#include "../algorithms/create_field.hpp"
#include "../algorithms/get_name.hpp"
#include "../algorithms/get_unit.hpp"
#include "xml_node.hpp"
#include "shape.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{
   
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief read and write field data
    struct field
    {

        template<typename GTYPE>
        static typename GTYPE::field_type 
        from_xml(const GTYPE &parent,const node &field_node, 
                 bool with_data=false,char separator=' ')
        {
            typedef attribute_data<string> attr_data;
            typedef typename GTYPE::field_type field_type;
            typedef typename GTYPE::value_type object_type;

            type_id_t tid  = type_id_from_str(attr_data::read(field_node,"type"));
            auto name      = attr_data::read(field_node,"name");
            auto long_name = attr_data::read(field_node,"long_name");
            auto units     = attr_data::read(field_node,"units");

            shape_t s{1}; 
            if(field_node.count("dimensions"))
                s = shape::from_xml<shape_t>(field_node.get_child("dimensions"));

            field_type field = create_field(object_type(parent),tid,name,s);
            field.attributes.template create<string>("units").write(units);
            field.attributes.template create<string>("long_name").write(long_name);

            if(with_data && has_data(field_node))
            {
                array data = make_array(tid,s);
                if(data.size() == 1)
                    data[0] = read_node(tid,field_node);
                else 
                    data = node_data<array>::read(field_node,separator);

                field.write(data);
            }

        
            return field;
        }

        //--------------------------------------------------------------------
        template<typename DTYPE> 
        static DTYPE data_from_xml(const node &field_node)
        {

        }

        //--------------------------------------------------------------------
        template<typename DTYPE>
        static void data_to_xml(const DTYPE &data,const node &field_node)
        {

        }

        //-----------------------------------------------------------------
        template<typename FTYPE>
        static node to_xml(const FTYPE &field,bool with_data=false,
                                  char separator=' ')
        {
            node field_node;

            //write name and type attributes
            field_node.put("<xmlattr>.name",field.name());
            field_node.put("<xmlattr>.type",
                           str_from_type_id(field.type_id()));

            field_node.put("<xmlattr>.units",get_unit(field));

            string buffer;
            field.attributes["long_name"].read(buffer);
            field_node.put("<xmlattr>.long_name",buffer);

            //write the shape if it is not scalar field
            auto s = field.template shape<shape_t>();
            if(s.size() && (field.size()!=1))
                field_node.add_child("dimensions",shape::to_xml(s));

            //write data if requested by the user
            if(with_data)
            {
                if(s.empty()) s = shape_t{1};
                array data = make_array(field.type_id(),s);
                field.read(data);
                std::stringstream ss;
                ss<<data;
                field_node.put_value(ss.str());
            }
            
            return field_node;
        }


    };


//end of namespace
}
}
}
}
