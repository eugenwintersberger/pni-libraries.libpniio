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
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    //!
    //! \ingroup algorithm_code
    //! \brief get number of elements
    //!
    //! Return the number of elements stored in a group, field, or attribute.
    //! In the case of a group this function template returns the number of 
    //! children the group has. In the case of fields and attributes the number
    //! of elements are stored in the particular instance.
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object template
    //! \tparam IPMID implementation ID argument of the object template
    //!
    //! \param o reference to the group, field, or attribute object
    //! \return number of elements
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    size_t get_size(const OTYPE<IMPID> &o)
    {
        return o.size();
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get size visitor
    //!
    //! Return the size (the total number of elements stored) of a field or
    //! attribute stored in a variant type. In the case of a group the number 
    //! of children attached to this group is returned.
    //!
    //! \tparam VTYPE variant type
    //! \sa get_size
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_size_visitor : public boost::static_visitor<size_t>
    {
        public:
            //! result type
            typedef size_t result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Return the number of children attached to this group.
            //! 
            //! \throws invalid_object_error if group is invalid
            //! \throws object_error in case of any other error
            //! 
            //! \param g group instance
            //! \return number of children
            //!
            result_type operator()(const group_type &g) const
            {
                return g.size();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the size of a field.
            //! 
            //! \throws invalid_object_error if the field is not valid
            //! \throws object_error in case of any other error
            //!
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
            //! 
            //! \throws invalid_object_error if the attribute is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return size of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.size();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get size 
    //!
    //! Return the number of elements stored in a group, field, or attribute.
    //! In the case of a group this function template returns the number of 
    //! children the group has. In the case of fields and attributes the number
    //! of elements are stored in the particular instance.
    //!
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    auto s = get_size(field);
    \endcode
    */
    //! \throws invalid_object_error if object is not valid
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! 
    //! \param o instance of nxobject
    //! \return size of the object
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    size_t get_size(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_size_visitor<GTYPE,FTYPE,ATYPE> visitor_type;

        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
