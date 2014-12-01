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

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>

#include "../algorithms/create_attribute.hpp"
#include "xml_node.hpp"
#include "dimensions.hpp"
#include "io_object.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief read and write attributes
    struct attribute : public io_object
    {
        //!
        //! \brief create attribute from XML description
        //!
        //! \tparam PTYPE parent type
        //! \param parent reference to parent instance
        //! \param attr_node XML node with attribute description
        //! \return instance of an attribute type
        //!
        template<typename PTYPE>
        static typename PTYPE::attribute_type 
        object_from_xml(const PTYPE &parent,const node &attr_node)
        {
            typedef typename PTYPE::attribute_type  attribute_type;

            //create the attribute object
            attribute_type attr = create_attribute(object_type(parent),
                                                   type_id(attr_node),
                                                   name(attr_node),
                                                   shape(attr_node));
            
            return attr;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief write attribute to XML
        //!
        //! \tparam ATYPE attribute type
        //! \param attr attribute instance
        //! \return XML node with the attribute metadata
        //!
        template<typename ATYPE>
        static node object_to_xml(const ATYPE &attr)
        {
            node attr_node;

            //write name and type attributes
            attr_node.put("<xmlattr>.name",get_name(attr));
            attr_node.put("<xmlattr>.type",get_type(attr));

            //if the attribute has more than one element we have to add its
            //shape - otherwise the attribute is scalar
            if(get_size(attr)>1)
            {
                auto shape = attr.template shape<shape_t>();
                attr_node.add_child("dimensions", 
                                    dimensions::object_to_xml(shape));
            }
            
            return attr_node;
        }

    };

//end of namespace
}
}
}
}
