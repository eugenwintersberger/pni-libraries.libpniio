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
// Created on: Jul 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    //!
    //! \ingroup variant_code
    //! \brief get size visitor
    //!
    //! Return the size (the total number of elements stored) of a field or
    //! attribute stored in a variant type. In the case of a group the number 
    //! of children attached to this group is returned.
    //!
    //! \tparam VTYPE variant type
    //! \sa get_size
    //!
    template<typename VTYPE> 
    class get_size_visitor : public boost::static_visitor<size_t>
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
            //! Return the number of children attached to this group.
            //! \throws nxgroup_error groups do not have type
            //! \param g group instance
            //! \return number of children
            //!
            result_type operator()(const group_type &g) const
            {
                return g.nchildren();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the size of a field.
            //! \param f field instance
            //! \return size of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return f.size();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Returns the size of the attribute.
            //! \param a attribute instance
            //! \return size of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.size();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief get size wrapper
    //!
    //! This function is a wrapper to the get_size_visitor template. It 
    //! returns the total number of elements held by a field or attribute 
    //! stored in a variant type. If the stored object is agroup an 
    //! exception will be thrown.
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    auto s = get_size(field);
    \endcode
    */
    //! \throws nxgroup_error if stored object is a group
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return size of the object
    //!
    template<typename VTYPE> 
    typename get_size_visitor<VTYPE>::result_type get_size(const VTYPE &o)
    {
        return boost::apply_visitor(get_size_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
