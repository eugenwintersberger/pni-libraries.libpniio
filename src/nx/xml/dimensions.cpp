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

#include <pni/io/nx/xml/data_node.hpp>
#include <pni/io/nx/xml/dimensions.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    bool operator<(const index_value_type &lhs,const index_value_type &rhs)
    {
        return lhs.first<rhs.first;
    }

    //------------------------------------------------------------------------
    node dimensions::index_value_to_node(size_t index,size_t value)
    {
        node dim_node;
        dim_node.put("<xmlattr>.index",index);
        dim_node.put("<xmlattr>.value",value);

        return dim_node;
    }

    //------------------------------------------------------------------------
     index_value_type dimensions::index_value_from_node(const node &dim_node)
    {
        size_t_parser_type p;
        node index_attribute = get_attribute(dim_node,"index");
        node value_attribute = get_attribute(dim_node,"value");

        return {p(data_node::read(index_attribute)),
                p(data_node::read(value_attribute))};
    }

     //-----------------------------------------------------------------------
     size_t dimensions::rank(const node &dim)
     {
        node type_attribute = get_attribute(dim,"rank");
        return size_t_parser_type()(data_node::read(type_attribute));
     }

     //-----------------------------------------------------------------------
     size_t dimensions::size(const node &dim)
     {
         shape_t shape = object_from_xml(dim);

         return std::accumulate(shape.begin(),shape.end(),size_t(1),
                                std::multiplies<size_t>());

     }

     //-----------------------------------------------------------------------
     shape_t dimensions::object_from_xml(const node &dims) 
     {
        iv_vector buffer;
        size_t_parser_type p;

        //read all index value pairs
        for(auto dim: dims)
            if(dim.first == "dim")
                buffer.push_back(index_value_from_node(dim.second));

        if(buffer.size()!=rank(dims))
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Rank in dimensions tag does not match number of dim values!");

        std::sort(buffer.begin(),buffer.end());

        shape_t result;
        auto iter = buffer.begin();
        std::generate_n(std::back_inserter(result),buffer.size(),
                      [&iter](){ return (iter++)->second; });
        return result;
     }
    
     //-----------------------------------------------------------------------
     node dimensions::object_to_xml(const shape_t &shape) 
     {
        node dim;

        dim.put("<xmlattr>.rank",shape.size());

        size_t index = 1;
        for(auto s: shape) 
        {
            auto iv = make_pair("dim",index_value_to_node(index++,s));
            dim.push_back(iv);
        }

        return dim;
     }



//end of namespace
}
}
}
}
