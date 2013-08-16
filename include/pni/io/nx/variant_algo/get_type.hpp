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

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    /*!
    \ingroup variant_code
    \brief get type visitor

    This visitor retrieves the type code of the data stored in a field or
    attribute For groups an exception is thrown as they do not have a rank.
    \tparam VTYPE variant type
    \sa get_type
    */
    template<typename VTYPE> 
    class get_type_visitor : public boost::static_visitor<type_id_t>
    {
        public:
            //! result type
            typedef type_id_t result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Throw an exception as a group cannot have a type.
            \throws nxgroup_error groups do not have type
            \param g group instance
            \return NONE type code - can be safely ignored 
            */ 
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "A group does not have a type!");
                return type_id_t::NONE;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Returns the type of a field.
            \param f field instance
            \return type code of field data
            */
            result_type operator()(const field_type &f) const
            {
                return f.type_id();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            Returns the type of the attribute.
            \param a attribute instance
            \return type code of the attribute data
            */
            result_type operator()(const attribute_type &a) const
            {
                return a.type_id();
            }
    };

    /*!
    \ingroup variant_code
    \brief get type wrapper

    Wrapper function for the get_type_visitor template. This function returns
    the type code of the data in a field or attribute stored in a variant type.
    If the stored object is a group type an exception will be thrown.

    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    type_id_t tc = get_type(field);
    \endcode

    \throws nxgroup_error if stored object is a group
    \tparam VTYPE variant type
    \param o instance of VTYPE
    \return value of type_id_t
    */
    template<typename VTYPE> 
    typename get_type_visitor<VTYPE>::result_type get_type(const VTYPE &o)
    {
        return boost::apply_visitor(get_type_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
