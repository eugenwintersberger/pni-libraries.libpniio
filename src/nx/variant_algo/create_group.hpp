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
 * Created on: Jul 3, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include "../nxvariant_traits.hpp"
#include "get_object.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    /*!
    \ingroup variant_code
    \brief create group visitor

    This visitor creates a group below the group stored in the variant type. 
    If the stored object is not a group an exception will be thrown. 
    \tparam VTYPE variant type
    \sa create_group
    */
    template<typename VTYPE> 
    class create_group_visitor : public boost::static_visitor<VTYPE>
    {
        private:
            string _name;  //!< the name of the group
            string _class; //!< the Nexus class of the group
        public:
            //! result type
            typedef VTYPE result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            create_group_visitor(const string &n,const string &c):
                _name(n),
                _class(c)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Create a new group of name _name and class _class below the parent
            group g. The new group will be stored as object_types variant.
            \throws nxgroup_error in case of errors
            \param g parent group instance
            \return new group stored as object_types
            */ 
            result_type operator()(const group_type &g) const
            {
                group_type group;
                if(!_name.empty())
                {
                    if(!_class.empty())
                        group = g.create_group(_name,_class);
                    else
                        group = g.create_group(_name);
                }
                else
                    //you have to at least provide a name
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "No name provided for the new group!");

                return result_type(group);

            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            A field cannot have a child group. Thus an exception will be thrown. 
            \throws group_error 
            \param f field instance
            \return empty result type
            */
            result_type operator()(const field_type &f) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Cannot create a group below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            An attribute cannot create a group - thus an exception will be
            thrown.
            \throws nxgroup_error 
            \param a attribute instance
            \return an empty result type
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Cannot create a group below an attribute!");
                return result_type();
            }
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_group wrapper

    Wrapper function for the create_group_visitor. This wrapper creates a new
    group of a particular name and class directly below the parent group.
    In order to successfully create a group at least the name argument must be
    non-empty. If an empty string is passed as the groups class then the
    NX_class attribute will not be set.


    \throws nxgroup_error if stored object is a group
    \tparam VTYPE variant type
    \param o instance of VTYPE with the parent group
    \param n name of the new group
    \param c Nexus class of the group
    \return object_types with the newly created group
    */
    template<typename VTYPE> 
    typename create_group_visitor<VTYPE>::result_type 
    create_group(const VTYPE &o,const string &n,const string &c)
    {
        return boost::apply_visitor(create_group_visitor<VTYPE>(n,c),o);
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_group wrapper

    Wrapper for the create_group_visitor. This wrapper creates a new group whose
    location, name, and class is described by a Nexus path. The template assumes
    that all intermediate groups exist. An exception will be thrown if this is
    not the case.

    \throws nxgroup_error in case of errors
    \tparam VTYPE variant type
    \param o instance of VTYPE with the parent group
    \param p path to the new group
    \return instance of object_types with the new group
    */
    template<typename VTYPE>
    typename create_group_visitor<VTYPE>::result_type
    create_group(const VTYPE &o,const nxpath &p)
    {
        typedef typename create_group_visitor<VTYPE>::result_type object_types;
        nxpath parent_path,group_path;
        split_last(p,parent_path,group_path);
   
       
        object_types parent;
        if(parent_path.size())
            parent = get_object(o,parent_path);
        else
            parent = o;

        return create_group(parent,group_path.begin()->first,
                            group_path.begin()->second);
    }
//end of namespace
}
}
}
