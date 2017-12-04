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

#include <pni/io/nx/xml/node.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/nx/nxobject.hpp>
#include <pni/io/nx/xml/field.hpp>
#include <pni/io/nx/xml/group.hpp>
#include <pni/io/nx/xml/attribute.hpp>
#include <pni/io/nx/xml/dimensions.hpp>
#include <pni/io/nx/xml/default.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{


    using namespace pni::core;
    using namespace pni::io::nx;
    
    //!
    //! \ingroup xml_classes
    //! \brief write data from Nexus to XML
    //! 
    //! This function template writes data from a Nexus object to the CDATA
    //! section of an XML tag. 
    //! 
    //! \tparam T data type to use
    //! \tparam OTYPE Nexus object type
    //! 
    //! \param o Nexus object from which to read the data
    //! \param n XML tag where to store the data
    //! 
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
    //!
    //! \ingroup xml_classes
    //! \brief write data from a Nexus object to XML
    //! 
    //! Read data from a Nexus object and store it to the CDATA section 
    //! of an XML tag. This function template only does type dispatching. 
    //! 
    //! \tparam OTYPE Nexus object type
    //! \param p the Nexus object from which to read the data
    //! \param n the XML node where to store the data
    //! 
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
                throw type_error(EXCEPTION_RECORD,
                "Cannot handle Nexus data type!");
        }
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief append attributes from a nexus type to XML
    //!
    //! Reads all attribtues from a Nexus node and append them to an 
    //! XML node. There are several attribute which are omitted as they 
    //! are part of the XML tag 
    //! \li NX_class whose content is written in the type attribute
    //! \li units which goes to the units attribute
    //! \li long_name which goes to the long_name tag attribute
    //!
    //! Whether or not data form the Nexus object is written to the XML output
    //! depends on the write_predicate. This is a callable which takes the 
    //! Nexus object as its only argument and returns true if the 
    //! data should be written or false otherwise. 
    //! 
    //! \tparam OTYPE Nexus object type
    //! \tparam PTYPE write predicate type    
    //! \param parent the object with the attributes
    //! \param p XML node to which attribute tags should be appended
    //! \param write_predicate function object determinig when to write data
    //!                        to the XML output
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
    //! Converts the structure of a Nexus tree stored below p into an XML 
    //! tree below n. The Nexus parent object p is provided as an instance of
    //! nxobject.
    //! Which data from the Nexus file goes to the XML output is determined 
    //! by the write_predicate, a functor taking a single Nexus object 
    //! as its argument and returns true if the data should be written and 
    //! false otherwise.
    //! 
    //! \tparam GTYPE Nexus group type
    //! \tparam FTYPE Nexus field type
    //! \tparam ATYPE Nexus attribute type
    //! \tparam LTYPE link type
    //! \tparam PTYPE write predicate type
    //! \param p parent object 
    //! \param n XML node
    //! \param write_data functor determining which data to write
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE,
             typename PTYPE
            > 
    void nexus_to_xml(nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &p,node &n,
                      PTYPE write_predicate)
    {
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
    //!
    //! \ingroup xml_classes
    //! \brief nexus to XML conversion
    //! 
    //! Converts the content of Nexus object to XML. Here the Nexus object is 
    //! is passed as an instance of nxattribute, nxgroup, or nxfield. 
    //! The write_predicate functor determines which data is written to the 
    //! XML output. 
    //! 
    //! \tparam OTYPE Nexus object type
    //! \tparam IMPID implementation ID
    //! \tparam PTYPE predicate type
    //! \param o parent object 
    //! \param n XML node
    //! \param write_predicate the functor determining which data to write
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename PTYPE
            >
    void nexus_to_xml(OTYPE<IMPID> &o,node &n,PTYPE write_predicate)
    {
        typedef decltype(get_parent(o)) object_type;
        object_type obj = o;
        nexus_to_xml(obj,n,write_predicate);
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief nexus to XML conversion
    //! 
    //! Converts the structure of a Nexus tree stored below p into an XML 
    //! tree below n. The Nexus parent object p is provided as an instance of
    //! nxobject.
    //! This template function takes no write predicate and thus no data 
    //! from the Nexus file is written to the XML output.
    //! 
    //! \tparam GTYPE Nexus group type
    //! \tparam FTYPE Nexus field type
    //! \tparam ATYPE Nexus attribute type    
    //! \tparam LTYPE link type
    //! \param p parent object 
    //! \param n XML node
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    void nexus_to_xml(nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &p,node &n)
    {
        nexus_to_xml(p,n,write_no_data());
    }
    
    //-------------------------------------------------------------------------
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    void nexus_to_xml(OTYPE<IMPID> &o,node &n)
    {
        typedef decltype(get_parent(o)) object_type;
        object_type obj = o;
        
        nexus_to_xml(o,n);
    }

//end of namespace
}
}
}
}
