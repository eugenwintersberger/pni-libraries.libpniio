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

#include "xml_node.hpp"
#include "attribute_data.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief index-value type
    //!
    //! This type describes an index value pair used in NXDL to describe a 
    //! single dimension. The first component is the index of the particular 
    //! dimensions while the second one denotes the number of elements 
    //! along this dimension.
    //! 
    typedef std::pair<size_t,size_t> index_value_type;

    //!
    //! \ingroup xml_lowlevel_utils
    //! 
    //! Operator required to sort containers using index_value_type as their
    //! element type. index-value pairs are ordered by their dimension index.
    //! This operator returns true if the index component of the LHS is 
    //! smaller than the index component of the RHS.
    //1
    bool operator<(const index_value_type &lhs,const index_value_type &rhs);


    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief reading and writing dimensions
    //!
    //! This structure provides two static methods to read and write the 
    //! dimensions of a field or attribute to an XML tag. 
    //!
    struct dimensions
    {
        typedef std::vector<index_value_type>  iv_vector;


        //--------------------------------------------------------------------
        //!
        //! \brief generate dim node
        //! 
        //! Generate the content of a 'dim' node. This funtion basically 
        //! adds two attributes: the index of the dim and its value.
        //! 
        //! \param index dimension index 
        //! \param value number of elements along this dimension
        //! \return node with dim attributes
        //!
        static node index_value_to_node(size_t index,size_t value);

        //--------------------------------------------------------------------
        //!
        //! \brief read dim information
        //! 
        //! Reads the dimension information from a dim tag. A index/value pair
        //! is returned.
        //! 
        //! \param dim_node node which should be a dim type
        //! \return index value pair for the dim entry
        //!
        static index_value_type index_value_from_node(const node &dim_node);

        static shape_t from_xml(const node &dims);

        //--------------------------------------------------------------------
        //!
        //! \brief get dimension information from node
        //! 
        //! Create a shape container from a 'dim' node. The resulting 
        //! container holds the number of elements along each dimension
        //! of the field. 
        //! 
        //! \throws parser_error  in case of parsing errors
        //! \tparam DTYPE container type
        //! \param node a dim node
        //! \return instance of DTYPE with the shape information
        //! 
        template<typename DTYPE>
        static DTYPE from_xml(const node &dims)
        {
            shape_t s = from_xml(dims);
            return DTYPE(s.begin(),s.end());
        }

        static node to_xml(const shape_t &s);

        //--------------------------------------------------------------------
        //!
        //! \brief write shape information
        //! 
        //! Write the shape information from a container of type DTYPE to 
        //! an XML node (which should be named dim). 
        //! 
        //! \tparam DTYPE container type
        //! \param dim container instance with the data
        //! \return node instance with shape information
        //!
        template<typename DTYPE>
        static node to_xml(const DTYPE &dim)
        {
            shape_t s(dim.begin(),dim.end());
            return to_xml(s);
        }

    };

//end of namespace
}
}
}
}
