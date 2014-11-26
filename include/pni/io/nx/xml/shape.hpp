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

#include "xml_node.hpp"
#include "attribute_data.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief reading and writing dimensions
    //!
    //! This structure provides two static methods to read and write the 
    //! dimensions of a field or attribute to an XML tag. 
    //!
    struct shape
    {
        //! a pair type to store the index and the value of a dimension
        typedef std::pair<size_t,size_t> iv_type;
        //! vector of index/value pairs
        typedef std::vector<iv_type>     iv_vector;

        //--------------------------------------------------------------------
        //! 
        //! \brief compare index/value pairs
        //! 
        //! This comperator is used to order index/value pairs. These pairs
        //! are ordered by their index. 
        //!
        //! \param a LHS of the operation
        //! \param b RHS of the operation
        //! \return true if the LHS is smaller than the RHS
        //!
        static bool iv_comp(const iv_type &a,const iv_type &b)
        {
            return a.first < b.first; 
        }

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
        static node iv_to_node(size_t index,size_t value)
        {
            node dim;
            dim.put("<xmlattr>.index",index);
            dim.put("<xmlattr>.value",value);
            return dim;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief read dim information
        //! 
        //! Reads the dimension information from a dim tag. A index/value pair
        //! is returned.
        //! 
        //! \param n node which should be a dim type
        //! \return index value pair for the dim entry
        //!
        static iv_type iv_from_node(const node &n)
        {
            return iv_type{attribute_data<size_t>::read(n,"index"),
                           attribute_data<size_t>::read(n,"value")};
        }

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
            iv_vector buffer;

            //read all index value pairs
            for(auto dim: dims)
                if(dim.first == "dim")
                    buffer.push_back(iv_from_node(dim.second));

            if(buffer.size()!=attribute_data<size_t>::read(dims,"rank"))
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        "Rank in dimensions tag does not match number of dim values!");

            std::sort(buffer.begin(),buffer.end(),iv_comp);

            DTYPE result;
            auto iter = buffer.begin();
            std::generate_n(std::back_inserter(result),buffer.size(),
                          [&iter](){ return (iter++)->second; });
            return result;

        }

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
            node dimensions;

            dimensions.put("<xmlattr>.rank",dim.size());

            size_t index = 1;
            for(auto s: dim) 
                dimensions.push_back(make_pair("dim",iv_to_node(index++,s)));

            return dimensions;
        }

    };

//end of namespace
}
}
}
}
