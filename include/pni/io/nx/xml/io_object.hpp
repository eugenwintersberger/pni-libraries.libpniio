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
// Created on: Nov 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "node.hpp"
#include "attribute_data.hpp"
#include "decoder.hpp"
#include "attribute_data.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief general IO objects
    //!
    //! This class provides functions common for field and attribute nodes. 
    //!
    struct io_object
    {

        //! type to retrieve string attributes
        static attribute_data name_attribute;
        static attribute_data type_attribute;
        static string_decoder_type string_decoder;

        //--------------------------------------------------------------------
        //!
        //! \brief return object size
        //! 
        //! Returns the number of elements a field or attribute can store. 
        //! If the node contains a dimensions tag the number of elements is 
        //! computed from the shape described by the dimensions tag. If no
        //! dimensions tag is provided the node is assumed to describe a scalar
        //! object with a size of 1.
        //!
        //! \throws parser_error in case of an error
        //! \param io_node XML node with IO object metadata
        //! \return number of elements stored in the object
        //! 
        static size_t size(const node &io_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return object rank
        //! 
        //! This function returns the number of dimensions an IO object has. 
        //! For nodes with an dimensions child this number is provided by the 
        //! rank attribute of the dimensions tag. For scalar objects the rank
        //! is 0.
        //!
        //! \throws parser_error in case of an error
        //! \param io_node XML node with IO object metadata
        //! \return number of dimensions
        //! 
        static size_t rank(const node &io_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return object name
        //!
        //! Returns the name of the object which is determined by the name 
        //! attribute of the node.
        //! 
        //! \throws parser_error in case of an error
        //! \param io_node XML node with object metadata
        //! \return name of the object
        //! 
        static string name(const node &io_node);
        
        //--------------------------------------------------------------------
        //!
        //! \brief return object shape
        //! 
        //! \throws parser_error in case of an error
        //! \param io_node XML node with object metadata
        //! \return shape information
        //! 
        static shape_t shape(const node &io_node);
        
        //--------------------------------------------------------------------
        //!
        //! \brief get type id
        //! 
        //! Retrieves the type id of the field described by the XML node.
        //! 
        //! \throws parser_error if attribute cannot be read
        //! \throws type_error if type cannot be translated 
        //! 
        //! \param io_node the node with field information
        //! \return type id of the field
        //!
        static type_id_t type_id(const node &io_node);
        
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

    };

//end of namespace
}
}
}
}

