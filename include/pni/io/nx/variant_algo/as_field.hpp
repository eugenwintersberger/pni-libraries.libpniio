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
    //! \brief as field visitor
    //!
    //! This visitor return the object stored in a variant as a field object.
    //! Obviously this will only work if the object is really a field object. 
    //! If the stored object is a group or an attribute object an exception 
    //! will be thrown.
    //!
    //! \tparam VTYPE variant type
    //! \sa as_field
    //!
    template<typename VTYPE> 
    class as_field_visitor : public boost::static_visitor<
                             typename nxobject_field<VTYPE>::type
                             >
    {
        public:
            //! field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;
            //! result type of the visitor
            typedef field_type result_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throws an exception as the stored object is not a field.
            //! \throws nxfield_error groups do not have a rank
            //! \param g group instance
            //! \return invalid field instance
            //!
            result_type operator()(const group_type &g) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Object is a group and not a field!");
                return field_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the field stored in the variant.
            //! \param f field instance
            //! \return field instance
            //!
            result_type operator()(const field_type &f) const
            {
                return f;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Throw an exception as the object is not a field object.
            //! \throws nxfield_error no field instance
            //! \param a attribute instance
            //! \return invalid field instance
            //!
            result_type operator()(const attribute_type &a) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Object is an attribute not a field!");
                return field_type();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief as field wrapper
    //!
    //! Wrapper function for the as_field_visitor template. This function takes a
    //! variant object and returns a field object if the stored object is an
    //! instance of a field type. In other cases an exception will be thrown.
    /*!
    \code{.cpp}
    object_types field_obj = get_object(root,path_to_field);
    auto f = as_field(field_obj);
    \endcode
    */
    //!
    //! \throws nxfield_error if stored object is not a field type
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return instance of a field type
    //!
    template<typename VTYPE> 
    typename nxobject_field<VTYPE>::type as_field(const VTYPE &o)
    {
        return boost::apply_visitor(as_field_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
