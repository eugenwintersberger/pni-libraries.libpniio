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

#include <pni/io/nx/xml/io_object.hpp>
#include <pni/io/nx/xml/dimensions.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{


    size_t io_object::size(const node &io_node)
    {
        if(io_node.count("dimensions"))
            return dimensions::size(io_node.get_child("dimensions"));
        else
            return 1;
    }

    //------------------------------------------------------------------------
    size_t io_object::rank(const node &io_node)
    {
        if(io_node.count("dimensions"))
            return dimensions::rank(io_node.get_child("dimensions"));
        else 
            return 0;
    }

    //------------------------------------------------------------------------
    string io_object::name(const node &io_node)
    {
        return string_attribute::read(io_node,"name");
    }
    
    //------------------------------------------------------------------------
    shape_t io_object::shape(const node &io_node)
    {
        shape_t shape{1};
        if(io_node.count("dimensions"))
            shape = dimensions::object_from_xml(io_node.get_child("dimensions"));

        return shape;
    }

    //------------------------------------------------------------------------
    type_id_t io_object::type_id(const node &io_node)
    {
        return type_id_from_str(string_attribute::read(io_node,"type"));
    }
    
    //--------------------------------------------------------------------
    array io_object::data_from_xml(const node &io_node,char separator)
    {
        array data = make_array(type_id(io_node),shape(io_node));

        if(has_data(io_node))
        {
            if(data.size() == 1)
                data[0] = read_node(type_id(io_node),io_node);
            else 
                data = node_data<array>::read(io_node,separator);
        }

        return data;
    }

    //------------------------------------------------------------------------
    void io_object::data_to_xml(const array &data,node &io_node)
    {
        if(data.size()!=size(io_node))
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Array size and field size do not match!");

        std::stringstream ss;
        ss<<data;
        io_node.put_value(ss.str());
    }
//end of namespace
}
}
}
}
