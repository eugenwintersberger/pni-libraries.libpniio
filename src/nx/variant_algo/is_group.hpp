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
 * Created on: Jun 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    /*!
    \ingroup variant_code
    \brief check if group

    Check if the object stored in a variant is a group. The return value of the
    () operator of this visitor is bool.
    \tparam VTYPE variant type
    \return true if the object is a group, false otherwise
    */
    template<typename VTYPE> 
    class is_group_visitor : public boost::static_visitor<bool>
    {
        public:
            //! first type of the variant 
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type 
            typedef bool result_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;
          
            //----------------------------------------------------------------
            /*!
            \brief process group objects

            \param g reference to group instance
            \return true
            */
            result_type operator()(const group_type &g) const
            {
                return true;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field objects

            \param f reference to field instance
            \return false
            */
            result_type operator()(const field_type &f) const
            {
                return false;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute objects

            \param a reference to attribute instance
            \return false
            */
            result_type operator()(const attribute_type &a) const
            {
                return false;
            }
    };

    /*!
    \ingroup variant_code
    \brief check for group

    This template function is a wrapper around the is_group_visitor visitor
    template. It checks if the object stored in a variant type is a group and
    returns true if this is the case. In all other cases false is returned.
    \tparam VTYPE variant type
    \param o reference to VTYPE instance
    \return true if object is a group, false otherwise
    */
    template<typename VTYPE> 
    typename is_group_visitor<VTYPE>::result_type is_group(const VTYPE &o)
    {
        return boost::apply_visitor(is_group_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
