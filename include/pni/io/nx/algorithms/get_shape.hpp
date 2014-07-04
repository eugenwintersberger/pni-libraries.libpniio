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
    //! \ingroup algorithm_internal_code
    //! \brief get shape visitor
    //! 
    //! This visitor retrieves the shape of an attribute or a field. If the 
    //! object stored in the variant is a group an exception will be thrown.
    //! wrapper template function.
    //!
    //! \tparam CTYPE container type for the shape
    //! \tparam VTYPE variant type
    //! \sa get_shape
    //!
    template<
             typename CTYPE,
             typename VTYPE
            > 
    class get_shape_visitor : public boost::static_visitor<CTYPE>
    {
        public:
            //! result type
            typedef CTYPE result_type;
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
            //! Throw an exception as a group cannot have a shape.
            //! \throws nxgroup_error groups do not have shapes
            //! \param g group instance
            //! \return empty instance of CTYPE
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "A group does not have a shape!");
                return CTYPE();
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the shape of a field.
            //! \param f field instance
            //! \return instance of CTYPE with elements per dimension
            //!
            result_type operator()(const field_type &f) const
            {
                return f.template shape<CTYPE>();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Returns the shape of the attribute.
            //! \param a attribute instance
            //! \return instance of CTYPE with elements per dimension
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.template shape<CTYPE>();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get shape wrapper
    //!
    //! Wrapper function for the get_shape_visitor template. This function 
    //! returns the shape (number of elements along each dimension) of a field 
    //! or an attribute stored in the variant type. 
    //! If the stored object is a group type an exception will be thrown.   
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
    //! \return an instance of CTYPE with the elements for each dimension
    //!
    template<typename CTYPE,typename VTYPE> 
    typename get_shape_visitor<CTYPE,VTYPE>::result_type get_shape(const VTYPE &o)
    {
        return boost::apply_visitor(get_shape_visitor<CTYPE,VTYPE>(),o);
    }

//end of namespace
}
}
}
