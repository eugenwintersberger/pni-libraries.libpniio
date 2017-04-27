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
// Created on: Nov 25, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

#include "../algorithms/create_field.hpp"
#include "../algorithms/create_attribute.hpp"
#include "../algorithms/write.hpp"
#include "../algorithms/get_name.hpp"
#include "../algorithms/get_unit.hpp"
#include "../algorithms/as_field.hpp"
#include "../algorithms/as_group.hpp"
#include "../algorithms/get_size.hpp"
#include "../algorithms/get_shape.hpp"
#include "../nxobject.hpp"
#include "node.hpp"
#include "dimensions.hpp"
#include "io_node.hpp"
#include "../../windows.hpp"



namespace pni{
namespace io{
namespace nx{
namespace xml{

    //!
    //! \ingroup xml_classes
    //! \brief read and write field data
    struct PNIIO_EXPORT field : public io_node
    {

        //--------------------------------------------------------------------
        //!
        //! \brief return field unit
        //! 
        //! \throws parser_error in case of an error
        //!
        //! \param field_node XML node with field information
        //! \return string with the unit
        //! 
        static pni::core::string unit(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return long name
        //! 
        //! Obtain the long name from the XML node.
        //!
        //! \throws parser_error in case of an error
        //! \param field_node the XML node with the field information
        //! \return string with long name information
        //!
        static pni::core::string long_name(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief get chunk shape
        //! 
        //! Retrieve the chunk shape from the field tag. If the field has 
        //! no chunk tag an empty shape_t instance will be returned. 
        //! 
        //! \throws parser_error in case of an error
        //! \pararm field_node the XML node with the field specification
        //! \return an instance of shape_t with the chunk shape
        //! 
        static pni::core::shape_t chunk(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief create field from XML
        //! 
        //! Creates a new field object below parent according to the 
        //! information stored in the actual XML node. The data stored 
        //! in the XML node is not copied to the field automatically.
        //! 
        //! \throws parser_error if XML parsing operations fail
        //! \throws invalid_object_error if the parent is not valid
        //! \throws type_error if the data type is not supported
        //! \throws io_error if metadata cannot be written 
        //! \throws object_error in case of any other error
        //! \throws shape_mismatch_error if chunk and dimensions tag rank do
        //!                              not match
        //!
        //! \tparam GTYPE group type
        //! \param parent the parent group for the new field
        //! \param field_node XML node with field information
        //!
        //! \return field instance
        //!
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE,
                 typename LTYPE
                >
        static nxobject<GTYPE,FTYPE,ATYPE,LTYPE> 
        object_from_xml(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &parent,
                        const node &field_node)                                            
        {
            using namespace pni::core;

            typedef nxobject<GTYPE,FTYPE,ATYPE,LTYPE> object_type;
            //determine basic field parameters
            string    field_name  = name(field_node);
            shape_t   field_shape = shape(field_node);
            type_id_t tid         = type_id(field_node);               
            shape_t   chunk_shape = chunk(field_node);

            if(chunk_shape.empty())
            {
                chunk_shape = field_shape;
                chunk_shape[0] = 1;

                //if we have only a scalar field we set the chunk size to 1K
                if(field_shape.size()==1)
                    chunk_shape[0] = 1024;
            }
            else
            {
                if(chunk_shape.size() != field_shape.size())
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                            "Rank of chunk and dimensions tag do not match!");
            }
            
            //if the field tag contains a strategy tag we have to check
            //for possible compression attributes
            bool use_compression = false;
            bool use_shuffle = false;
            size_t compression_rate = 0;
            auto strategy = field_node.get_child_optional("strategy");
            if(strategy)
            {                             
                if(has_attribute(*strategy,"compression"))
                    use_compression = data_from_xml<bool>(
                    get_attribute(*strategy,"compression"));
                    
                if(has_attribute(*strategy,"shuffle"))
                    use_shuffle = data_from_xml<bool>(
                    get_attribute(*strategy,"shuffle"));
                    
                if(has_attribute(*strategy,"rate"))
                    compression_rate = data_from_xml<size_t>(
                    get_attribute(*strategy,"rate"));
                    
            }
            
            //construct the field object
            object_type f;
            if(use_compression)
            {
                typedef nximp_code_map<GTYPE> map_type;
                typedef nxobject_trait<map_type::icode> trait_type;
                typedef typename trait_type::deflate_type deflate_type;
                
                deflate_type comp(compression_rate,use_shuffle);
                f = create_field(parent,tid,field_name,field_shape,chunk_shape,comp);
            }
            else
                f = create_field(parent,tid,field_name,field_shape,chunk_shape);
                                  
            //add long name if requested by XML
            if(has_attribute(field_node,"long_name"))
                write(create_attribute<string>(f,"long_name"),
                      long_name(field_node));

            //add units if requested by XML
            if(has_attribute(field_node,"units"))
                write(create_attribute<string>(f,"units"),
                      unit(field_node));

            return f;
        }

        //-----------------------------------------------------------------
        //!
        //! \brief create XML object from field
        //!
        //! Create an XML object from a field. No data is included in the
        //! XML output. But it could easily be added with the data_to_xml
        //! function. No data is copied from the field instance to the 
        //! XML node.
        //!
        //! \throws parser_error in case of IO errors on the XML side
        //! \throws invalid_object_error if the field is not valid
        //! \throws io_error in case of metadata retrieval fails
        //! \throws type_error if data type of the field cannot be handled
        //! \throws object_error in case of any other error
        //!
        //! \tparam FTYPE field type
        //! \param field reference to the field instance
        //! \return XML node object with field information
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE,
                 typename LTYPE
                >
        static node object_to_xml(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &f)
        {
            using namespace pni::core;

            node field_node;            
            FTYPE fo = as_field(f); //throw type_error if f is not a field
            string buffer;

            //write name and type attributes
            field_node.put("<xmlattr>.name",fo.name());
            field_node.put("<xmlattr>.type",str_from_type_id(fo.type_id()));
            
            //add a units attribute if the original field has one
            if(fo.attributes.exists("units"))
            {                
                fo.attributes["units"].read(buffer);
                field_node.put("<xmlattr>.units",buffer);
            }
            
            //add a long_name attributes if the original field has one
            if(fo.attributes.exists("long_name"))
            {                
                fo.attributes["long_name"].read(buffer);
                field_node.put("<xmlattr>.long_name",buffer);
            }

            //write the shape if it is not scalar field
            auto s = get_shape<shape_t>(f);
            if(s.size() && (get_size(f)!=1))
                field_node.add_child("dimensions",dimensions::object_to_xml(s));

            return field_node;
        }

    };


//end of namespace
}
}
}
}
