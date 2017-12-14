//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/link.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{
    
    pni::core::string link::get_link_name(const node &link_node)
    {
        using namespace pni::core;
        if(!has_attribute(link_node,"name"))
            throw key_error(EXCEPTION_RECORD,
            "'link' node does not provide a 'name' attribute!");
            
        return data_node::read(get_attribute(link_node,"name"));
    }
            
    //-------------------------------------------------------------------------         
    pni::core::string link::get_link_target(const node &link_node)
    {       
        using namespace pni::core; 
        if(!has_attribute(link_node,"target"))
            throw key_error(EXCEPTION_RECORD,
            "'link' node does not provide a 'target' attribute!");
            
        return data_node::read(get_attribute(link_node,"target"));
    }
 
//end of namespace
}
}
}
}
