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

#include <pni/core/error.hpp>
#include <pni/io/nx/xml/field.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;


    //------------------------------------------------------------------------
    string field::unit(const node &field_node)
    {
        string unit;
        
        if(has_attribute(field_node,"units"))
        {
            node attr_node = get_attribute(field_node,"units");
            unit = data_node::read(attr_node);
        }
        
        return unit;
    }

    //------------------------------------------------------------------------
    string field::long_name(const node &field_node)
    {
        string long_name;
        
        if(has_attribute(field_node,"long_name"))
        {
            node attr_node = get_attribute(field_node,"long_name");
            long_name = data_node::read(attr_node);
        }
        
        return long_name;
    }


//end of namespace
}
}
}
}
