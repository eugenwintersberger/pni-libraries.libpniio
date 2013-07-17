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

#include "../nxvariant_traits.hpp"
#include "nxvariant_algo_helper.hpp"

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup variant_code
    \brief close an object

    This visitor closes an open object.
    
    \tparam VTYPE variant type
    */
    template<typename VTYPE> 
    class close_visitor : public boost::static_visitor<void>
    {
        public:
            //! first type of the variant 
            typedef typename GETVMEMBER(VTYPE,0) first_type;
            //! result type (bool)
            typedef void result_type;   
            //! Nexus group type
            DEFINE_NXGROUP(first_type) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_type) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_type) attribute_type;
           
            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Close the group.
            \param g reference to group instance
            \return false
            */
            result_type operator()(group_type &g) const
            {
                g.close();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Close the field.
            \param f reference to field instance
            \return true
            */
            result_type operator()(field_type &f) const
            {
                f.close();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            Close the attribute.
            \param a reference to attribute instance
            \return false
            */
            result_type operator()(attribute_type &a) const
            {
                a.close();
            }
    };

    /*!
    \ingroup variant_code
    \brief close object

    Wrapper function around the close_visitor. The function closes the object
    stored in the variant type passed to it.
    \tparam VTYPE Nexus object variant type
    \param o instance of VTYPE
    \return true if the object is a field
    */
    template<typename VTYPE> 
    typename close_visitor<VTYPE>::result_type close(VTYPE &o)
    {
        return boost::apply_visitor(close_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
