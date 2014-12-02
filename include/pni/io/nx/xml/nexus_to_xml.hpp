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
// ===========================================================================
// Created on: Jul 19, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "node.hpp"
#include "../algorithms.hpp"
#include "../nxobject.hpp"
#include "field.hpp"
#include "group.hpp"
#include "attribute.hpp"
#include "dimensions.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{


    using namespace pni::core;
    using namespace pni::io::nx;

   
    //!
    //! \ingroup xml_classes
    //! \brief append attributes from a nexus type to XML
    //!
    //! Reads all attribtues from a Nexus node and append them to an 
    //! XML node. 
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param parent the object with the attributes
    //! \param p XML node to which attribute tags should be appended
    //! 
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void append_attributes(const nxobject<GTYPE,FTYPE,ATYPE> &parent,node &p)
    {
        for(auto a: parent.attributes)
        {
            if(get_name(a) == "NX_class") continue;
            p.add_child("attribute",attribute::object_to_xml(a));
        }
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief nexus to XML conversion
    //! 
    //! Converts the structure of a Nexus tree as stored below p into a XML 
    //! tree strucure and stores it below n. 
    //! \tparam VTYPE variant type with the root object
    //! \param p parent object 
    //! \param n XML node
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void nexus_to_xml(const nxobject<GTYPE,FTYPE,ATYPE> &p,node &n)
    {
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;

        node child;
        string key;
        if(is_field(p))
        {
            key = "field";
            child = field::object_to_xml(p);
            append_attributes(as_field(p),child);
        }
        else if(is_group(p))
        {
            key = "group";

            //add the actual group to the parent node
            child =  group::object_to_xml(p);
            append_attributes(as_group(p),child);

            //iterate over the children 
            for(auto o: as_group(p)) nexus_to_xml(o,child);
        }
            
        //now everything is done and we have to 
        n.add_child(key,child);
    }

//end of namespace
}
}
}
}
