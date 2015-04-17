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
#include "../algorithms/as_attribute.hpp"
#include "../algorithms/get_type.hpp"
#include "../algorithms/get_name.hpp"
#include "../algorithms/get_size.hpp"
#include "../algorithms/get_shape.hpp"
#include "../nxobject.hpp"
#include "node.hpp"
#include "dimensions.hpp"
#include "io_node.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_classes
    //! \brief read and write attributes
    //!
    struct attribute : public io_node
    {
        //!
        //! \brief create attribute from XML description
        //! 
        //! Create an attribute attached to a parent according to the 
        //! information stored in the XML node. The parent must be 
        //! either a field or a group type. No attribute data is 
        //! copied from the Nexus object to the XML node.
        //! 
        //! \throws invalid_object_error if the parent is not valid
        //! \throws type_error if the requested data type does not exist
        //! \throws io_error if the attribute cannot be written 
        //! \throws object_error in case of any other error
        //!
        //! \tparam PTYPE parent type
        //! \param parent reference to parent instance
        //! \param attr_node XML node with attribute description
        //! \return instance of an attribute type
        //!
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE
                >
        static nxobject<GTYPE,FTYPE,ATYPE>
        object_from_xml(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                        const node &attr_node)
        {
            //create the attribute object
            return  create_attribute(parent,type_id(attr_node),
                                            name(attr_node),
                                            shape(attr_node));
        }

        //-----------------------------------------------------------------
        //!
        //! \brief write attribute to XML
        //!
        //! Create an XML attribute from a Nexus attribute. No data will 
        //! be transfered. 
        //!
        //! \tparam ATYPE attribute type
        //! \param attr attribute instance
        //! \return XML node with the attribute metadata
        //!
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE
                >
        static node object_to_xml(const nxobject<GTYPE,FTYPE,ATYPE> &attr)
        {
            node attr_node;

            //write name and type attributes
            attr_node.put("<xmlattr>.name",get_name(attr));
            attr_node.put("<xmlattr>.type",str_from_type_id(get_type(attr)));

            //if the attribute has more than one element we have to add its
            //shape - otherwise the attribute is scalar
            if(get_size(attr)>1)
            {
                auto shape = get_shape<shape_t>(attr);
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
