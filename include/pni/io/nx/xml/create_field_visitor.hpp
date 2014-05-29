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
// ==========================================================================
// Created on: Jul 17, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../nexus_utils.hpp"
#include "../nxvariant.hpp"
#include "xml_node.hpp"
#include "node_data.hpp"
#include "attribute_data.hpp"
#include "dim2shape.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{
    
    using namespace pni::core;
    using namespace pni::io::nx;

    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief visitor for field creation 
    //! 
    //! This visitor creates a group from an XML object.
    //!
    template<typename VTYPE> 
    class create_field_visitor : public boost::static_visitor<VTYPE>
    {
        private: 
            node _xml_node; //!< XML node data

            //-----------------------------------------------------------------
            //!
            //! \brief copy typed data to a field
            //! 
            //! This template takes the data stored in a field and copies it 
            //! to an to a field. If the size of the field is 1 we assume the 
            //! data to be scalar and read only one element. If the size is 
            //! larger than one an array is used to write the data.
            //!
            //! \throws parser_error in case of parsing issues
            //! \throws nxfield_error if case of IO problems
            //! \tparam T data type
            //! \tparam FTYPE field type
            //! \param n the XML node with the data
            //! \param f instance of a Nexus field
            //!
            template<
                     typename T,
                     typename FTYPE
                    >
            void copy_node_to_field(const node &n,const FTYPE &f) const
            {
                if(f.size() == 1)
                {
                    T buffer = node_data<T>::read(n);
                    f.write(buffer);
                }
                else
                {
                    //manage multidimensional data
                    auto buffer = node_data<array>::read(n,',');
                    f.write(buffer);
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief dispatch copy process
            //!
            //! This template takes a field instance and dispatches the copy 
            //! process according to the data type of the field. This 
            //! certainly requires that the data stored in the node can be 
            //! converted to this very data type.
            //! 
            //! \throws parser_error if the data cannot be parsed properly
            //! \throws nxfield_error  if there are some other IO problems
            //! \tparam FTYPE field tyep
            //! \param n XML node from which to read the data
            //! \param f instance of FTYPE to where the data shall be writen 
            //!
            template<typename FTYPE>
            void copy_node_to_field(const node &n,const FTYPE &f) const
            {
                if(f.type_id() == type_id_t::UINT8)
                    copy_node_to_field<uint8>(n,f);
                else if(f.type_id() == type_id_t::INT8)
                    copy_node_to_field<int8>(n,f);
                
                else if(f.type_id() == type_id_t::UINT8)
                    copy_node_to_field<uint16>(n,f);
                else if(f.type_id() == type_id_t::INT8)
                    copy_node_to_field<int16>(n,f);

                else if(f.type_id() == type_id_t::UINT32)
                    copy_node_to_field<uint32>(n,f);
                else if(f.type_id() == type_id_t::INT32)
                    copy_node_to_field<int32>(n,f);
                
                else if(f.type_id() == type_id_t::UINT64)
                    copy_node_to_field<uint64>(n,f);
                else if(f.type_id() == type_id_t::INT64)
                    copy_node_to_field<int64>(n,f);

                else if(f.type_id() == type_id_t::FLOAT32)
                    copy_node_to_field<float32>(n,f);
                else if(f.type_id() == type_id_t::FLOAT64)
                    copy_node_to_field<float64>(n,f);
                else if(f.type_id() == type_id_t::FLOAT128)
                    copy_node_to_field<float128>(n,f);

                else if(f.type_id() == type_id_t::STRING)
                    copy_node_to_field<string>(n,f);
            }

        public:
            //! result type
            typedef VTYPE result_type;
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! \param n xml node from which to create the group
            //!
            create_field_visitor(const node &n):
                _xml_node(n)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Create a new group according to the XML data below the parent 
            //! group passed by the user. If the XML node contains data it 
            //! will be written to the field. 
            //! 
            //! \throws parser_error in case of any parsing issues
            //! \throws nxfield_error in case of data IO problems
            //! \throws nxgroup_error in case of errors
            //! \param g group instance
            //! \return the new group instance as a variant
            //!
            result_type operator()(const group_type &g) const
            {
                //obtain the name and the type of the field
                auto name = attribute_data<string>::read(_xml_node,"name");
                auto type = attribute_data<string>::read(_xml_node,"type");

                //read the shape of the field if it got one
                //All exceptions will be cought as this is not a mandatory
                //information. By default we assume a single scalar field.
                shape_t shape{1};
                try
                {
                    node dim_node = _xml_node.get_child("dimensions");
                    shape = dim2shape(dim_node);
                }
                catch(...)
                {}

                //at this point we should have gathered enough information in order to
                //create the field.
                type_id_t type_id = type_id_from_str(type);
                auto f = pni::io::nx::create_field(g,name,type_id,shape);


                //OK - in the next step we try to gather some optional information that
                //might be stored in the field.
                //------------------try to write units attribute--------------------
                if(has_attribute(_xml_node,"units"))
                {
                    auto units = attribute_data<string>::read(_xml_node,"units");
                    f.template attr<string>("units").write(units);
                }

                //-------------------try to write long_name attribute--------------
                if(has_attribute(_xml_node,"long_name"))
                {
                    auto lname = attribute_data<string>::read(_xml_node,"long_name");
                    f.template attr<string>("long_name").write(lname);
                }

                //now we read the data from the field  and write it
                if(has_data(_xml_node))
                    copy_node_to_field(_xml_node,f);

                create_attributes(f,_xml_node);

                return result_type(f);      
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as a field cannot create a new field. 
            //! \throws nxfield_error field cannot create a new field
            //! \param f field instance
            //! \return nothin
            //!
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Cannot create a field below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Throw an exception as we cannot create a field from an 
            //! attribute.
            //! 
            //! \throws nxattribute_error
            //! \param a attribute instance
            //! \return size of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Cannot create a field below an attribute!");
                return result_type();
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_lowlevel_utils
    //! \brief create_field wrapper function
    //! 
    //! Creates a field from an XML node. In XML fields are written as 
    //! follows 
    /*!
    \code{.xml}
    <field name="data" type="float64" unit="m" long_name="detector data">
        <dimensions ....>

        </dimensions>
    </field>
    \endcode
    */
    //! The \c name and the \c type attribute are mandatory. Thus, a 
    //! parser_error is thrown if they do not exist. The \c dimensions tag 
    //! is optional and must be used only when a multidimensional field is 
    //! created.
    //! 
    //! The \c field tag itself has two optional attributes \c unit and \c
    //! long_name. The former one is a string attribute with the string
    //! representation of the physical unit of the data. The latter one is a 
    //! string attribute too with a more detailed description of the data. 
    //!
    //! \throws parser_error in case of missing attributes
    //! \throws nxattribute_error if the parent object is an attribute
    //! \throws nxfield_error if the parent is a field or in case of IO 
    //! problems
    //! \throws nxgroup_error in case of problems during field creation
    //! \tparam VTYPE variant type with the parent object
    //! \param o the parent object
    //! \param n the XML node
    //! \return a field instancen as a variant
    //!
    template<typename VTYPE> 
    typename create_field_visitor<VTYPE>::result_type 
    create_field(const VTYPE &o,const node &n)
    {
        return boost::apply_visitor(create_field_visitor<VTYPE>(n),o);
    }

//end of namespace
}
}
}
}
