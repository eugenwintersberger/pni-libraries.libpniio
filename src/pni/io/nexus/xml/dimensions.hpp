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
// Created on: Nov 27, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nexus/xml/node.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/io/windows.hpp>

namespace pni{
namespace io{
namespace nexus{
namespace xml{
//!
//! @ingroup nexus_xml_classes
//! @brief index-value type
//!
//! This type describes an index value pair used in NXDL to describe a
//! single dimension. The first component is the index of the particular
//! dimensions while the second one denotes the number of elements along
//! this dimension.
//!
using IndexValue = std::pair<size_t,size_t>;

//------------------------------------------------------------------------
//!
//! @ingroup nexus_xml_classes
//! @brief comparison operator for index_value_type
//!
//! Operator required to sort containers using index_value_type as their
//! element type. index-value pairs are ordered by their dimension index.
//! This operator returns true if the index component of the LHS is
//! smaller than the index component of the RHS.
//!
//! @param lhs left handside of the operator
//! @param rhs right handside of the operator
//! @return true if index of lhs is small than that of rhs,
//! false otherwise
//!
PNIIO_EXPORT bool operator<(const IndexValue &lhs,
                            const IndexValue &rhs);

//------------------------------------------------------------------------
//!
//! @ingroup nexus_xml_classes
//! @brief reading and writing dimensions
//!
//! This structure provides two static methods to read and write the
//! dimensions of a field or attribute to an XML tag.
//!
class PNIIO_EXPORT Dimensions
{

  private:

    //! vector type to hold index-value pairs
    using IndexValueVector = std::vector<IndexValue>;

    //----------------------------------------------------------------
    //!
    //! @brief generate dim node
    //!
    //! Generate the content of a 'dim' node. This funtion basically
    //! adds two attributes: the index of the dim and its value.
    //!
    //! @param index dimension index
    //! @param value number of elements along this dimension
    //! @return node with dim attributes
    //!
    static Node index_value_to_node(size_t index,size_t value);

    //-----------------------------------------------------------------
    //!
    //! @brief read dim information
    //!
    //! Reads the dimension information from a dim tag. A index/value
    //! pair is returned.
    //! 
    //! @param dim_node node which should be a dim type
    //! @return index value pair for the dim entry
    //!
    static IndexValue index_value_from_node(const Node &dim_node);

  public:
    //-----------------------------------------------------------------
    //!
    //! @brief get number of dimensions
    //!
    //! Return the number of dimensions a particular dimensions tags
    //! spans. If the object is scalar this function returns 0.
    //!
    //! @param dim node with dimension information
    //! @return number of dimensions
    //!
    static size_t rank(const Node &dim);

    //-----------------------------------------------------------------
    //!
    //! @brief get size of an object
    //!
    //! This returns the number of elements which can be stored by an
    //! object of a particular dimension. If the rank of the  object
    //! is 0 this function returns 1 indicating that this is a
    //! scalar object.
    //!
    //! @param dim node with dimension information
    //! @return number of elements
    //!
    static size_t size(const Node &dim);


    //-----------------------------------------------------------------
    //!
    //! @brief return shape
    //!
    //! Returns a container of type shape_t whose elements are the
    //! numbers of elements along each dimension.
    //!
    //! @throws parser_error if a tag cannot be read
    //! @param dims node with dimension information
    //! @return instance of shape_t
    static hdf5::Dimensions object_from_xml(const Node &dims);

    //-----------------------------------------------------------------
    //!
    //! @brief create dimension node
    //!
    //! Create a dimensions node from a container with shape
    //! information.
    //!
    //! @param s reference to the shape container
    //! @return XML node with dimension information
    //!
    static Node object_to_xml(const hdf5::Dimensions &s);

};


//end of namespace
}
}
}
}
