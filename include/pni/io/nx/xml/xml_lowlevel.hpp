//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Jul 8, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../nx.hpp"
#include "../nxobject_traits.hpp"
#include "../../exceptions.hpp"
#include "../../parsers/array_parser.hpp"

#include "xml_node.hpp"
#include "node_data.hpp"
#include "attribute_data.hpp"
#include "create_group_visitor.hpp"
#include "create_field_visitor.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //--------------------------------------------------------------------------
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief create objects from XML
    //!
    //! Recursively creates the objects as described in the XML file below 
    //! parent.
    //! 
    //! \throws parser_error in case of XML parsing problems
    //! \throws nxgroup_error in case of group creation or access issues
    //! \throws nxfield_error in case of field creation issues
    //! \tparam PTYPE parent type
    //! \param parent instance of PTYPE
    //! \param t ptree instance with the XML data
    //!
    template<typename PTYPE>
    void create_objects(const PTYPE &parent,node &t)
    {
        for(auto child: t)
        {
            if(child.first == "group")
            {
                auto g = pni::io::nx::xml::create_group(parent,child.second);
                //recursive call of create_objects
                create_objects(g,child.second);
            }
            else if(child.first == "field")
            {
                 create_field(parent,child.second);
            }
            else if(child.first == "link")
            {
                auto name = attribute_data<string>::read(child.second,"name");
                auto target = attribute_data<string>::read(child.second,"target");
                //parent.link(name,target);
            }
        }
    }

//end of namespace 
}
}
}
}
