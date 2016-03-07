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
#include "../nximp_code.hpp"
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get number of elements
    //!
    //! Return the number of elements stored in a group, field, or attribute.
    //! In the case of a group this function template returns the number of 
    //! children the group has. In the case of fields and attributes the number
    //! of elements are stored in the particular instance.
    //! 
    //! This template function works for 
    //! 
    //! \li nxgroup
    //! \li nxfield
    //! \li nxattribute
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
        using field_type = typename nxobject_trait<IMPID>::field_type;
        using attr_type  = typename nxobject_trait<IMPID>::attribute_type;
        using group_type = typename nxobject_trait<IMPID>::group_type;

        static_assert(std::is_same<field_type,OTYPE<IMPID>>::value ||
                      std::is_same<attr_type,OTYPE<IMPID>>::value ||
                      std::is_same<group_type,OTYPE<IMPID>>::value,
                      "Argument must be a group, field, or "
                      "attribute instance!");

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
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! \sa get_size
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class get_size_visitor : public boost::static_visitor<size_t>
    {
        public:
            //! result type
            using result_type = size_t;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type =  FTYPE;
            //! Nexus attribute type
            using attribute_type =  ATYPE;
            //! NeXus link type
            using link_type = LTYPE;

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

            //-----------------------------------------------------------------
            //!
            //! \brief process nxlink instances
            //!
            //! Throw a type_error exception as links do not have a size. 
            //! 
            //! \throws type_error 
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Links do not have a size!");
                return 0;
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
    //! \tparam LTYPE link type
    //! 
    //! \param o instance of nxobject
    //! \return size of the object
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    size_t get_size(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = get_size_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;

        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
