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

#include "node.hpp"
#include "data_node.hpp"
#include "attribute_data.hpp"
#include "group.hpp"
#include "attribute.hpp"
#include "field.hpp"
#include "default.hpp"
#include "link.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_classes
    //! \brief append xml attributes to Nexus object
    //!
    //! Function template appends the attributes described by the attribute
    //! tags with in an XML node to a Nexus object. By default, the attributes 
    //! are only created according to their XML definitions. No data is
    //! transfered from the attribute tags to the corresponding attributes.
    //! Data transfer can be triggered for particular attributes by passing a 
    //! predicate function as the last argument to this template. 
    //!
    //! \throws parser_error if XML parsing fails
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the datatype requested by XML cannot be handled
    //! \throws io_error in case of metadata or data IO fails
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! 
    //! \param p XML node from which to read the attributes
    //! \param parent the nexus object to which the attributes shall be attached
    //! \param write_data predicate which decides if data should be written
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void append_attributes(node &p,const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                           const nxobject_predicate<GTYPE,FTYPE,ATYPE> &write_data)
    {
        for(auto child: p)
        {
            if(child.first=="attribute")
            {
                auto a = attribute::object_from_xml(parent,child.second);
                if(write_data(a))
                    write(a,io_node::data_from_xml(child.second));
            }
        }
    }


    //--------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
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
    //! \param write_data predicate function determining when data should be
    //! written
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void xml_to_nexus(node &t,const nxobject<GTYPE,FTYPE,ATYPE> parent,
                      const nxobject_predicate<GTYPE,FTYPE,ATYPE> &write_data =
                      write_no_data())
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
                link::object_from_xml(parent,child.second);
            }
                
            //append all attributes tagged in this child
            append_attributes(child.second,object,write_data);

            if(write_data(object))
                write(object,io_node::data_from_xml(child.second));
        }
    }

//end of namespace 
}
}
}
}
