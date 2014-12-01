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
#include "../nxobject.hpp"
#include "../../exceptions.hpp"
#include "../../parsers/array_parser.hpp"

#include "xml_node.hpp"
#include "node_data.hpp"
#include "attribute_data.hpp"
#include "group.hpp"
#include "attribute.hpp"
#include "field.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
    
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void append_attributes(node &p,const nxobject<GTYPE,FTYPE,ATYPE> &parent)
    {
        for(auto child: p)
        {
            if(child.first=="attribute")
                attribute::object_from_xml(parent,child.second);
        }
    }

    //--------------------------------------------------------------------------
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief create objects from XML
    //!
    //! Recursively creates the objects as described in the XML file below 
    //! parent.
    //! 
    //! \throws parser_error in case of XML parsing problems
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws io_error if data or metadata write failed
    //! \throws type_error if a data type is involved that cannot be handled
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param t ptree instance with the XML data
    //! \param parent instance of nxobject
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void xml_to_nexus(node &t,const nxobject<GTYPE,FTYPE,ATYPE> parent)
    {
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;
        for(auto child: t)
        {
            object_type object;

            if(child.first == "group")
            {
                object = group::object_from_xml(parent,child.second);
                //recursive call of create_objects
                xml_to_nexus(child.second,object);
            }
            else if(child.first == "field")
            {
                auto f = field::object_from_xml(parent,child.second);
            }
            else if(child.first == "link")
            {
                //NEED TO IMPLEMENT THIS
            }
                
            //append all attributes tagged in this child
            append_attributes(child.second,object);
        }
    }

//end of namespace 
}
}
}
}
