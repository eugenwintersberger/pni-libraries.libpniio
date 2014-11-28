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
#include "dimensions.hpp"
#include "io_object.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief read and write field data
    struct field : public io_object
    {

        //--------------------------------------------------------------------
        //!
        //! \brief return field unit
        //! 
        //! \throws parser_error in case of an error
        //!
        //! \param field_node XML node with field information
        //! \return string with the unit
        //! 
        static string unit(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return long name
        //! 
        //! Obtain the long name from the XML node.
        //!
        //! \throws parser_error in case of an error
        //! \param field_node the XML node with the field information
        //! \return string with long name information
        //!
        static string long_name(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief create field from XML
        //! 
        //! Creates a new field object below parent according to the 
        //! information storde in the actual XML node.
        //! 
        //! \throws parser_error if XML parsing operations fail
        //!
        //! \param parent the parent object for the new field
        //! \param field_node XML node with field information
        //! \param type_error if the data type is not supported
        //! \param invalid_object_error if the parent is not a valid object
        //! \param object_error in case of any other error
        //!
        //! \return field instance
        //!
        template<typename GTYPE>
        static typename GTYPE::field_type 
        object_from_xml(const GTYPE &parent,const node &field_node)
        {
            typedef typename GTYPE::field_type field_type;
            typedef typename GTYPE::value_type object_type;


            field_type f = create_field(object_type(parent),
                                        type_id(field_node),
                                        name(field_node),
                                        shape(field_node));
            
            string ln    = long_name(field_node);
            string units = unit(field_node);

            //set mandatory attributes
            f.attributes.template create<string>("units").write(units);
            f.attributes.template create<string>("long_name").write(ln);
        
            return f;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief get data from XML
        //! 
        //! Reads the data stored with the XML field node. 
        //!
        //! \throws type_error if the fields data type is not supported
        //! \throws parser_error in case of errors during parsing data text
        //!
        //! \param field_node the XML node with the data
        //! \param separator the separator character used to separate array 
        //! items
        //! \return instance of array with the data
        //! 
        static array data_from_xml(const node &field_node,char separator=' ');

        //--------------------------------------------------------------------
        //!
        //! \brief write data to a node
        //! 
        //! Write data from an array to a field node. 
        //!
        //! \throws size_mismatch_error if field and data size do not match
        //!
        //! \param array the container with data
        //! \param field_node node with field data
        //!
        static void data_to_xml(const array &data, node &field_node);

        //-----------------------------------------------------------------
        //!
        //! \brief create XML object from field
        //!
        //! Create an XML object from a field. No data is included in the
        //! XML output. But it could easily be added with the data_to_xml
        //! function. 
        //!
        //! \throws parser_error in case of IO errors on the XML side
        //! \throws invalid_object_error if the field is not valid
        //! \throws io_error in case of metadata retrieval fails
        //! \throws type_error if data type of the field cannot be handled
        //! \throws object_error in case of any other error
        //!
        //! \tparam FTYPE field type
        //! \param field reference to the field instance
        //! \return XML node object with field information
        template<typename FTYPE>
        static node object_to_xml(const FTYPE &field)
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
                field_node.add_child("dimensions",dimensions::object_to_xml(s));

            return field_node;
        }
    };


//end of namespace
}
}
}
}
