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

#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{


    /*!
    \ingroup variant_code
    \brief get path visitor

    Retrieves the path of a Nexus object. This works currently only for groups
    and fields as we cannot retrieve the parent object from an attribute.
    \tparam VTYPE variant type
    \sa get_path
    */
    template<typename VTYPE> 
    class get_path_visitor : public boost::static_visitor<string>
    {
        public:
            //! result type
            typedef string result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Return the path of a group instance
            \param g group instance
            \return string with the path
            */ 
            result_type operator()(const group_type &g) const
            {
                return g.path();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Retrieve the path of a field instance.
            \param f field instance
            \return name of the field
            */
            result_type operator()(const field_type &f) const
            {
                return f.path();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            Throw an exception as we currently cannot retrieve the full path
            from an attribute.
            \throws nxattribute_error
            \param a attribute instance
            \return name of the attribute
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes currently do not support path!");
                return result_type();
            }
    };

    /*!
    \ingroup variant_code
    \brief get path wrapper

    Wrapper function for the get_path_visitor class. 
    \tparam VTYPE
    \param o instance of VTYPE
    \return a string with the path of the object
    */
    template<typename VTYPE> 
    typename get_path_visitor<VTYPE>::result_type get_path(const VTYPE &o)
    {
        return boost::apply_visitor(get_path_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
