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
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>

#include "../algorithms/create_field.hpp"
#include "../algorithms/get_name.hpp"
#include "../algorithms/get_unit.hpp"
#include "xml_node.hpp"
#include "dimensions.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
   
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief read and write field data
    struct field
    {
        //! type to retrieve string attributes
        typedef attribute_data<string> string_attribute;
        //! type to retrieve size_t attributes
        typedef attribute_data<size_t> size_attribute;

        //--------------------------------------------------------------------
        //!
        //! \brief return field size
        //! 
        //! \throws parser_error in case of an error
        //! 
        static size_t size(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return field rank
        //! 
        //! \throws parser_error in case of an error
        //! 
        static size_t rank(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return field name
        //! 
        //! \throws parser_error in case of an error
        //! 
        static string name(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return field unit
        //! 
        //! \throws parser_error in case of an error
        //! 
        static string unit(const node &field_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return field shape
        //! 
        //! \throws parser_error in case of an error
        //! 
        static shape_t shape(const node &field_node);

        static string long_name(const node &file_node);

        //--------------------------------------------------------------------
        //!
        //! \throws parser_error if attribute cannot be read
        //! \throws type_error if type cannot be translated 
        //!
        static type_id_t type_id(const node &field_node);


        //--------------------------------------------------------------------
        //!
        //! \throws parser_error if XML parsing operations fail
        template<typename GTYPE>
        static typename GTYPE::field_type 
        object_from_xml(const GTYPE &parent,const node &field_node)
        {
            typedef typename GTYPE::field_type field_type;
            typedef typename GTYPE::value_type object_type;


            field_type f = create_field(object_type(parent),
                                        type_id(field_node),
                                        name(field_node),
                                        shape(field_node));
            
            string ln    = long_name(field_node);
            string units = unit(field_node);

            //set mandatory attributes
            f.attributes.template create<string>("units").write(units);
            f.attributes.template create<string>("long_name").write(ln);
        
            return f;
        }

        //--------------------------------------------------------------------
        static array data_from_xml(const node &field_node,char separator=' ');

        //--------------------------------------------------------------------
        static void data_to_xml(const array &data, node &field_node);

        //-----------------------------------------------------------------
        template<typename FTYPE>
        static node object_to_xml(const FTYPE &field,bool with_data=false,
                                  char separator=' ')
        {
            node field_node;

            //write name and type attributes
            field_node.put("<xmlattr>.name",field.name());
            field_node.put("<xmlattr>.type",
                           str_from_type_id(field.type_id()));

            field_node.put("<xmlattr>.units",get_unit(field));

            string buffer;
            field.attributes["long_name"].read(buffer);
            field_node.put("<xmlattr>.long_name",buffer);

            //write the shape if it is not scalar field
            auto s = field.template shape<shape_t>();
            if(s.size() && (field.size()!=1))
                field_node.add_child("dimensions",dimensions::to_xml(s));

            
            return field_node;
        }


    };


//end of namespace
}
}
}
}
