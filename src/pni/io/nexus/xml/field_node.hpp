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
#include <pni/core/type_erasures.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/io/nexus/xml/io_node.hpp>
#include <pni/io/windows.hpp>



namespace pni{
namespace io{
namespace nexus{
namespace xml{

//!
//! @ingroup nexus_xml_classes
//! @brief read and write field data
struct PNIIO_EXPORT FieldNode : public IONode
{

    //--------------------------------------------------------------------
    //!
    //! @brief return field unit
    //!
    //! @throws parser_error in case of an error
    //!
    //! @param field_node XML node with field information
    //! @return string with the unit
    //!
    static std::string unit(const Node &field_node);

    //--------------------------------------------------------------------
    //!
    //! @brief return long name
    //!
    //! Obtain the long name from the XML node.
    //!
    //! @throws parser_error in case of an error
    //! @param field_node the XML node with the field information
    //! @return string with long name information
    //!
    static std::string long_name(const Node &field_node);

    //--------------------------------------------------------------------
    //!
    //! @brief get chunk shape
    //!
    //! Retrieve the chunk shape from the field tag. If the field has
    //! no chunk tag an empty shape_t instance will be returned.
    //!
    //! @throws parser_error in case of an error
    //! @param field_node the XML node with the field specification
    //! @return an instance of shape_t with the chunk shape
    //!
    static hdf5::Dimensions chunk(const Node &field_node);

    //-----------------------------------------------------------------
    //!
    //! \brief create XML object from field
    //!
    //! Create an XML object from a field. No data is included in the
    //! XML output. But it could easily be added with the data_to_xml
    //! function. No data is copied from the field instance to the
    //! XML node.
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
//    template<
//    typename GTYPE,
//    typename FTYPE,
//    typename ATYPE,
//    typename LTYPE
//    >
//    static node object_to_xml(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &f)
//    {
//      using namespace pni::core;
//
//      node field_node;
//      FTYPE fo = as_field(f); //throw type_error if f is not a field
//      string buffer;
//
//      //write name and type attributes
//      field_node.put("<xmlattr>.name",fo.name());
//      field_node.put("<xmlattr>.type",str_from_type_id(fo.type_id()));
//
//      //add a units attribute if the original field has one
//      if(fo.attributes.exists("units"))
//      {
//        fo.attributes["units"].read(buffer);
//        field_node.put("<xmlattr>.units",buffer);
//      }
//
//      //add a long_name attributes if the original field has one
//      if(fo.attributes.exists("long_name"))
//      {
//        fo.attributes["long_name"].read(buffer);
//        field_node.put("<xmlattr>.long_name",buffer);
//      }
//
//      //write the shape if it is not scalar field
//      auto s = get_shape<shape_t>(f);
//      if(s.size() && (get_size(f)!=1))
//        field_node.add_child("dimensions",dimensions::object_to_xml(s));
//
//      return field_node;
//    }

};


//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
