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
#include <pni/core/error.hpp>
#include <pni/io/nx/algorithms/write.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>
#include <pni/io/nx/nxobject.hpp>
#include <pni/io/nx/nxobject_traits.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/parsers.hpp>

#include <pni/io/nx/xml/node.hpp>
#include <pni/io/nx/xml/data_node.hpp>
#include <pni/io/nx/xml/group.hpp>
#include <pni/io/nx/xml/attribute.hpp>
#include <pni/io/nx/xml/field.hpp>
#include <pni/io/nx/xml/default.hpp>
#include <pni/io/nx/xml/link.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief write data from buffer 
    //! 
    //! Read data from the CDATA section of an XML tag and store it in an 
    //! NeXus object. The data type used for reading the data is determined 
    //! by the user supplied template parameter.
    //! 
    //! \throws type_error if the data type cannot be read or handled by the 
    //!                    write function
    //! \throws parser_error if the data could not be read from the CDATA
    //!                      section of the tag
    //! \throws invalid_object_error if the target object is not valid
    //! \throws io_error if writing the data fails       
    //! \throws size_mismatch_error if the amount of data read from CDATA
    //!                             does not match the size of the NeXus
    //!                             object
    //! \throws object_error in case of any other error
    //! 
    //! \tparam T data type to use for writing
    //! \tparam OTYPE object type to which to write the data
    //! \param object the object instance to which to write the data
    //! \param n the node holding the data
    //! 
    template<
             typename T,
             typename OTYPE
            >
    void write_node_data(const OTYPE &object,const node &n)
    {
        typedef std::vector<T> buffer_type;
        
        auto buffer = io_node::data_from_xml<buffer_type>(n);
                
        write(object,buffer);
        
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief write node data 
    //! 
    //! Write the data stored in an XML tag to a NeXus object. This is 
    //! a utilty function which calles an appropriate instantiation of the 
    //! write_node_data function template for every particular data type. 
    //! 
    //! \throws type_error if the data type cannot be read or handled by the 
    //!                    write function
    //! \throws parser_error if the data could not be read from the CDATA
    //!                      section of the tag
    //! \throws invalid_object_error if the target object is not valid
    //! \throws io_error if writing the data fails       
    //! \throws size_mismatch_error if the amount of data read from CDATA
    //!                             does not match the size of the NeXus
    //!                             object
    //! \throws object_error in case of any other error
    //!     
    //! \tparam OTYPE object type to which to write the data
    //! \param object the object instance to which to write the data
    //! \param n the node holding the data
    //! 
    template<typename OTYPE>
    void write_node_data(const OTYPE &object,const node &n)
    { 
        using namespace pni::core;

        switch(get_type(object))
        {   
            case type_id_t::UINT8:
                write_node_data<uint8>(object,n); break;
            case type_id_t::INT8:
                write_node_data<int8>(object,n); break;
            case type_id_t::UINT16:
                write_node_data<uint16>(object,n); break;
            case type_id_t::INT16:
                write_node_data<int16>(object,n); break;
            case type_id_t::UINT32:
                write_node_data<uint32>(object,n); break;
            case type_id_t::INT32:
                write_node_data<int32>(object,n); break;
            case type_id_t::UINT64:
                write_node_data<uint64>(object,n); break;
            case type_id_t::INT64:
                write_node_data<int64>(object,n); break;
            case type_id_t::FLOAT32:
                write_node_data<float32>(object,n); break;
            case type_id_t::FLOAT64:
                write_node_data<float64>(object,n); break;
            case type_id_t::FLOAT128:
                write_node_data<float128>(object,n); break;
            case type_id_t::COMPLEX32:
                write_node_data<complex32>(object,n); break;
            case type_id_t::COMPLEX64:
                write_node_data<complex64>(object,n); break;
            case type_id_t::COMPLEX128:
                write_node_data<complex128>(object,n); break;
            case type_id_t::BOOL:
                write_node_data<bool_t>(object,n); break;
            case type_id_t::STRING:
                //need some special handling for string data - only support
                //scalar strings
                write(object,io_node::data_from_xml<string>(n));                                
                //write_node_data<string>(object,n);
                break;            
            default:
                throw type_error(EXCEPTION_RECORD,
                    "Unrecognized data type!");
        }        
    }


    //--------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create objects from XML
    //!
    //! Recursively creates the objects as described in the XML file below 
    //! parent. The parent is passed as a reference to an instance of nxobject.
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
    //! \tparam LTYPE link type
    //!
    //! \param t ptree instance with the XML data
    //! \param parent instance of nxobject
    //! \param write_data predicate function determining when data should be
    //! written
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE,
             typename PTYPE
            >
    void xml_to_nexus(const node &t,const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &parent,
                      PTYPE write_data)
    {
        //typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;
        for(auto child: t)
        {            
            if(child.first == "group")
            {
                auto g = group::object_from_xml(parent,child.second);
                //recursive call of create_objects
                xml_to_nexus(child.second,g,write_data);
                                
            }
            else if(child.first == "field")
            {
                auto f = field::object_from_xml(parent,child.second);
                
                if(write_data(f) && !data_node::read(child.second).empty()) 
                    write_node_data(f,child.second);
                
                //need to call here xml_to_nexus recursively to add
                //custom attributes
                xml_to_nexus(child.second,f,write_data);                
            }
            else if(child.first == "link")
            {                
                link::object_from_xml(parent,child.second);
            }
            else if(child.first == "attribute")
            {
                //attach attributes to the parent object
                auto a = attribute::object_from_xml(parent,child.second);
                
                if(write_data(a) && !data_node::read(child.second).empty())
                    write_node_data(a,child.second);
            }                                        
        }
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create objects from XML
    //!
    //! A version of xml_to_nexus where no data is written to the file at all.
    //! The parent is passed as a reference to nxobject.
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
    //! \tparam LTYPE link type
    //!
    //! \param t ptree instance with the XML data
    //! \param parent instance of nxobject  
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            >
    void xml_to_nexus(const node &t,const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &parent)
    {
       xml_to_nexus(t,parent,write_no_data());
    }
        
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create objects from XML
    //!
    //! An overload of the xml_to_nexus function template where the parent
    //! is passed as an instance of nxgroup. 
    //! 
    //! \throws parser_error in case of XML parsing problems
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws io_error if data or metadata write failed
    //! \throws type_error if a data type is involved that cannot be handled
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE parent template
    //! \tparam IMPID implementation ID
    //! \tparam PTYPE data writer predicate
    //!
    //! \param t XML node from which to construct the Nexus structure
    //! \param group the parent group below which the structure should be 
    //!              generated
    //! \param write_data predicate to determine whether or tag data 
    //!                   should be written to the file
    //!
    template<
             template<pni::io::nx::nximp_code> class OTYPE,
             pni::io::nx::nximp_code IMPID,
             typename PTYPE
            >
    void xml_to_nexus(const node &t,const OTYPE<IMPID> &group,PTYPE write_data)
    {
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        object_type o = group;
        xml_to_nexus(t,o,write_data);
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create objects from XML
    //!
    //! An overload of the xml_to_nexus function template where the parent
    //! is passed as an instance of nxgroup. 
    //! 
    //! \throws parser_error in case of XML parsing problems
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws io_error if data or metadata write failed
    //! \throws type_error if a data type is involved that cannot be handled
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE parent template
    //! \tparam IMPID implementation ID
    //! \tparam PTYPE data writer predicate
    //!
    //! \param t XML node from which to construct the Nexus structure
    //! \param group the parent group below which the structure should be 
    //!              generated
    //! \param write_data predicate to determine whether or tag data 
    //!                   should be written to the file
    //!
    template<
             template<pni::io::nx::nximp_code> class OTYPE,
             pni::io::nx::nximp_code IMPID
            >
    void xml_to_nexus(const node &t,const OTYPE<IMPID> &group)
    {
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        object_type o=group;
        xml_to_nexus(t,o,write_no_data());
    }

//end of namespace 
}
}
}
}
