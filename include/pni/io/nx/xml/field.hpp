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
#include "../algorithms/create_attribute.hpp"
#include "../algorithms/write.hpp"
#include "../algorithms/get_name.hpp"
#include "../algorithms/get_unit.hpp"
#include "../algorithms/as_field.hpp"
#include "../algorithms/as_group.hpp"
#include "../algorithms/get_shape.hpp"
#include "../nxobject.hpp"
#include "xml_node.hpp"
#include "dimensions.hpp"
#include "io_object.hpp"



namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_classes
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
        //! information stored in the actual XML node.
        //! 
        //! \throws parser_error if XML parsing operations fail
        //! \throws invalid_object_error if the parent is not valid
        //! \throws type_error if the data type is not supported
        //! \throws io_error if metadata cannot be written 
        //! \throws object_error in case of any other error
        //!
        //! \tparam GTYPE group type
        //! \param parent the parent group for the new field
        //! \param field_node XML node with field information
        //! \param type_error if the data type is not supported
        //! \param invalid_object_error if the parent is not a valid object
        //! \param object_error in case of any other error
        //!
        //! \return field instance
        //!
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE
                >
        static nxobject<GTYPE,FTYPE,ATYPE> 
        object_from_xml(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                        const node &field_node)
        {
            typedef FTYPE field_type;
            typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;

            auto f = create_field(parent,type_id(field_node),
                                  name(field_node),
                                  shape(field_node));

            if(has_attribute(field_node,"long_name"))
                write(create_attribute<string>(f,"long_name"),
                      long_name(field_node));

            if(has_attribute(field_node,"units"))
                write(create_attribute<string>(f,"units"),
                      unit(field_node));

            return f;
        }

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
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE
                >
        static node object_to_xml(const nxobject<GTYPE,FTYPE,ATYPE> &field)
        {
            node field_node;

            //write name and type attributes
            field_node.put("<xmlattr>.name",get_name(field));
            field_node.put("<xmlattr>.type",str_from_type_id(get_type(field)));
            field_node.put("<xmlattr>.units",get_unit(field));

            string buffer;
            read(get_attribute(field,"long_name"),buffer);
            field_node.put("<xmlattr>.long_name",buffer);

            //write the shape if it is not scalar field
            auto s = get_shape<shape_t>(field);
            if(s.size() && (get_size(field)!=1))
                field_node.add_child("dimensions",dimensions::object_to_xml(s));

            return field_node;
        }

    };


//end of namespace
}
}
}
}
