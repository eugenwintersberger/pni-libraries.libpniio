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
 * Created on: Jul 18, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <type_traits>
#include "../nxvariant_traits.hpp"
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"

namespace pni{
namespace io{
namespace nx{


    /*!
    \ingroup variant_code
    \brief get children visitor
   
    Returns a container with children of a group stored in a variant type.
    \tparam VTYPE variant type
    \tparam CTEMP container template
    */
    template<typename VTYPE,typename CTYPE> 
    class get_children_visitor : public boost::static_visitor<void>
    {
        private:
            CTYPE &_container; //!< container holding the children
        public:
            //! first type of the variant type
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type
            typedef void result_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;

            //-----------------------------------------------------------------
            //! constructor
            get_children_visitor(CTYPE &c):_container(c) {}

            //-----------------------------------------------------------------
            /*!
            \brief process groups
            
            As groups are the only objects that can have children this is the
            only method which needs implementation.
            \param g group instance
            \return child object
            */
            result_type operator()(const group_type &g) const
            {
                for(auto iter = g.begin();iter!=g.end();++iter)
                {
                    if(iter->object_type() == nxobject_type::NXFIELD)
                        _container.push_back(VTYPE(field_type(*iter)));
                    else if(iter->object_type() == nxobject_type::NXGROUP)
                        _container.push_back(VTYPE(group_type(*iter)));
                    else
                        throw type_error(EXCEPTION_RECORD,
                                "Object is neither a group nor a field!");
                }

            }

            //-----------------------------------------------------------------
            /*!
            \brief process fields

            Fields cannot have children - throw an exception here.
            \throws nxfield_error no children for fields
            \param f field instance
            \return to be ignored
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attributes

            Like fields attributes cannot have children - throw an exception
            here.
            \throws nxattribute_error no children for attributes
            \param a attribute instance
            \return to be ignored
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
    };

    /*!
    \ingroup variant_code
    \brief get children wrapper

    Wrapper function for the get_children_visitor template. The parent object
    from which to retrieve its children is passed as the first argument. 
    The second argument is the container within which the children will be
    stored. The value_type of the container must match the variant type of the
    parent. If this is not the case an error will be raised during compilation.

    \throws nxfield_error if the stored object is a field
    \throws nxattribute_error if the stored object is an attribute
    \throws type_error if one of the stored objects is not a nexus object
    \tparam VTYPE variant type
    \tparam CTYPE container type for the children
    \param o parent object as instance of VTYPE
    \param c container as instance of CTYPE
    \return container with children
    */
    template<typename VTYPE,typename CTYPE> 
    void get_children(const VTYPE &o,CTYPE &c)
    {
        //check if the container type is of same type is the variant type
        static_assert(std::is_same<typename CTYPE::value_type,VTYPE>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        return boost::apply_visitor(get_children_visitor<VTYPE,CTYPE>(c),o);
    }

//end of namespace
}
}
}
