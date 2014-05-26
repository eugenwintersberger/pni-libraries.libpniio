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
// ===========================================================================
// Created on: Jul 3, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup variant_code
    //! \brief get rank visitor
    //!
    //! This visitor retrieves the rank (the number of dimensions) of a 
    //! field or attribute stored in a variant type.  If the object stored 
    //! in the variant is a group an exception will be thrown.
    //!
    //! \tparam CTYPE container type for the shape
    //! \tparam VTYPE variant type
    //! \sa get_rank
    //!
    template<typename VTYPE> 
    class get_rank_visitor : public boost::static_visitor<size_t>
    {
        public:
            //! result type
            typedef size_t result_type;
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type; 

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throw an exception as a group cannot have a rank.
            //!
            //! \throws nxgroup_error groups do not have a rank
            //! \param g group instance
            //! \return 0
            //!
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "A group does not have a shape!");
                return size_t(0);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the rank of a field.
            //! \param f field instance
            //! \return number of dimensions
            //!
            result_type operator()(const field_type &f) const
            {
                return f.rank();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //! 
            //! Returns the rank of the attribute.
            //! \param a attribute instance
            //! \return number of dimensions
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.rank();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief get rank wrapper
    //!
    //! Wrapper function for the get_rank_visitor template. This function 
    //! returns the rank (number of dimensions) of a field or an attribute 
    //! stored in the variant type.  If the stored object is a group type 
    //! an exception will be thrown.
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    auto shape = get_shape<shape_t>(field);
    \endcode
    */
    //! \throws nxgroup_error if stored object is a group
    //! \tparam CTYPE container type for the shape
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return number of dimensions
    //!
    template<typename VTYPE> 
    typename get_rank_visitor<VTYPE>::result_type get_rank(const VTYPE &o)
    {
        return boost::apply_visitor(get_rank_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
