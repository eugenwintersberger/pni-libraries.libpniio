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

#include <pni/io/nx/xml/io_node.hpp>
#include <pni/io/nx/xml/dimensions.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{

    //------------------------------------------------------------------------
    size_t io_node::size(const node &io_node)
    {
        auto dims = io_node.get_child_optional("dimensions");
        if(dims)
            return dimensions::size(*dims);
        else
            return 1;
    }

    //------------------------------------------------------------------------
    size_t io_node::rank(const node &io_node)
    {
        auto dims = io_node.get_child_optional("dimensions");
        if(dims)
            return dimensions::rank(*dims);
        else 
            return 0;
    }

    //------------------------------------------------------------------------
    pni::core::string io_node::name(const node &io_node)
    {
        node name_attribute = get_attribute(io_node,"name");
        return data_node::read(name_attribute);
    }
    
    //------------------------------------------------------------------------
    pni::core::shape_t io_node::shape(const node &io_node)
    {
        pni::core::shape_t shape{1};
        auto dims = io_node.get_child_optional("dimensions");
        if(dims)
            shape = dimensions::object_from_xml(*dims);

        return shape;
    }

    //------------------------------------------------------------------------
    pni::core::type_id_t io_node::type_id(const node &io_node)
    {
        node type_attribute = get_attribute(io_node,"type");
        pni::core::string type_code = data_node::read(type_attribute);

        //need to handle the special case of a boolean type
        if(type_code == "bool_t") type_code = "bool";

        return pni::core::type_id_from_str(type_code);
    }

    
//end of namespace
}
}
}
}
