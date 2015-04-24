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
#include "default.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{


    using namespace pni::core;
    using namespace pni::io::nx;
    
    template<
             typename T,
             typename OTYPE
            > 
    void write_object_data(OTYPE &o,node &n)
    {
        std::vector<T> buffer(get_size(o));
        
        read(o,buffer);
        io_node::data_to_xml(n,buffer);
    }
    
    //-------------------------------------------------------------------------
    template<typename OTYPE> void write_object_data(OTYPE &p,node &n)
    {
        switch(get_type(p))
        {
            case type_id_t::UINT8:
                write_object_data<uint8>(p,n); break;
            case type_id_t::INT8:
                write_object_data<int8>(p,n); break;
            case type_id_t::UINT16:
                write_object_data<uint16>(p,n); break;
            case type_id_t::INT16:
                write_object_data<int16>(p,n); break;
            case type_id_t::UINT32:
                write_object_data<uint32>(p,n); break;
            case type_id_t::INT32:
                write_object_data<int32>(p,n); break;
            case type_id_t::UINT64:
                write_object_data<uint64>(p,n); break;
            case type_id_t::INT64:
                write_object_data<int64>(p,n); break;
            case type_id_t::FLOAT32:
                write_object_data<float32>(p,n); break;
            case type_id_t::FLOAT64:
                write_object_data<float64>(p,n); break;
            case type_id_t::FLOAT128:
                write_object_data<float128>(p,n); break;
            case type_id_t::COMPLEX32:
                write_object_data<complex32>(p,n); break;
            case type_id_t::COMPLEX64:
                write_object_data<complex64>(p,n); break;
            case type_id_t::COMPLEX128:
                write_object_data<complex128>(p,n); break;
            case type_id_t::STRING:
                write_object_data<string>(p,n); break;
            default:
                std::cout<<"do nothing"<<std::endl;
        }
    }

    //-------------------------------------------------------------------------
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
             typename OTYPE,
             typename PTYPE
            >
    void append_attributes(const OTYPE &parent,node &p,PTYPE &write_predicate)
    {
        typedef decltype(get_parent(parent)) object_type;
        
        for(object_type a: parent.attributes)
        {
            string name = get_name(a);
            if(name == "NX_class") continue;
            if(name == "units") continue;
            if(name == "long_name") continue;
            
            node attribute_node = attribute::object_to_xml(a);
            
            if(write_predicate(a))
                write_object_data(a,attribute_node);                
            
            p.add_child("attribute",attribute_node);
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
             typename ATYPE,
             typename PTYPE
            > 
    void nexus_to_xml(nxobject<GTYPE,FTYPE,ATYPE> &p,node &n,
                      PTYPE write_predicate)
    {
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;

        node child;
        string key;
        if(is_field(p))
        {
            key = "field";
            child = field::object_to_xml(p);
            append_attributes(as_field(p),child,write_predicate);
            
            if(write_predicate(p))
                write_object_data(p,child);                
        }
        else if(is_group(p))
        {
            key = "group";

            //add the actual group to the parent node
            child =  group::object_to_xml(p);
            append_attributes(as_group(p),child,write_predicate);

            //iterate over the children 
            for(auto o: as_group(p)) nexus_to_xml(o,child,write_predicate);
        }
            
        //now everything is done and we have to 
        n.add_child(key,child);
    }
    
    //-------------------------------------------------------------------------
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void nexus_to_xml(nxobject<GTYPE,FTYPE,ATYPE> &p,node &n)
    {
        nexus_to_xml(p,n,write_no_data());
    }

//end of namespace
}
}
}
}
