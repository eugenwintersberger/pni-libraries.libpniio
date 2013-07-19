/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 17, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include "../nxvariant.hpp"
#include "xml_node.hpp"
#include "attribute_data.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{
    
    using namespace pni::core;
    using namespace pni::io::nx;

    /*!
    \ingroup xml_lowlevel_utils
    \brief visitor for group creation 

    This visitor creates a group from an XML object.
    */
    template<typename VTYPE> 
    class create_group_visitor : public boost::static_visitor<VTYPE>
    {
        private: 
            node _xml_node;
        public:
            //! result type
            typedef VTYPE result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param n xml node from which to create the group
            */
            create_group_visitor(const node &n):
                _xml_node(n)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Create a new group according to the XML data below the parent group
            passed by the user.
            \throws nxgroup_error in case of errors
            \param g group instance
            \return the new group instance as a variant
            */ 
            result_type operator()(const group_type &g) const
            {

                //this attribute is absolutely mandatory - an exception will be
                //thrown if it does not exist
                auto name = attribute_data<string>::read(_xml_node,"name");

                string type;
                if(has_attribute(_xml_node,"type"))
                    type = attribute_data<string>::read(_xml_node,"type");

                /* create the gruop
                   This will throw an exception in case of any IO error. One possibility
                   would be that a group with this name already exists.
                */
                return result_type(g.create_group(name,type));
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Throw an instance as a field cannot create a new group. 
            \throws nxfield_error field cannot create a new group
            \param f field instance
            \return nothin
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Cannot create a group below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            Throw an exception as we cannot create a group from an attribute.
            \throws nxattribute_error
            \param a attribute instance
            \return size of the attribute
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Cannot create a group below an attribute!");
                return result_type();
            }
    };

    /*!
    \ingroup xml_lowlevel_utils
    \brief create_group wrapper function

    This function is a wrapper around the create_group_visitor template. It
    returns a new group as a variant object created below its parent group.

    \code{.cpp}
    object_types parent = get_object(root,path_to_field);
    xml::node root_node = xml::create_from_string("<group name="data"/>); 
    xml::node child     = root_node.get_child("group");
    object_types group  = xml::create_group(parent,child);
    \endcode

    All the information about the new group is drawn from XML data which is of
    form 
    \code{.xml}
    <group name="entry" type="NXentry"> </group>
    \endcode
    Wile the \c type attribute is optional the \c name attribute is absolutely
    mandatory as you cannot create a group without a name. The content of the \c
    type attribute goes to the \c NX_class attribute of the newly create group
    and determines the Nexus base class the new gruop belongs too. 

    \throws nxgroup_error in case of group creation errors
    \throws nxfield_error if the parent object is a field
    \throws nxattribute_error if the parent object is an attribute
    \tparam VTYPE variant type
    \param o instance of VTYPE
    \return size of the object
    */
    template<typename VTYPE> 
    typename create_group_visitor<VTYPE>::result_type 
    create_group(const VTYPE &o,const node &n)
    {
        return boost::apply_visitor(create_group_visitor<VTYPE>(n),o);
    }

//end of namespace
}
}
}
}
