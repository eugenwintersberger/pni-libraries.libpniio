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

#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get shape
    //!
    //! Returns the shape of an attribute or field type. In the case of any
    //! other type compilation fails due to an internal static_assert statement.
    //! The container type used to retrieve the shape information must be
    //! provided by the user as a template parameter.
    //!
    /*!
    \code{.cpp}
    nxfield field = get_object(root,path_to_field);
    auto shape = get_shape<shape_t>(field);
    \endcode
    */
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws object_error in case of any other error
    //! 
    //! \tparam CTYPE container type for the shape
    //! \tparam OTYPE object template 
    //! \tparam IMPID implementation ID
    //!
    //! \param object the object for which the shape should be determined
    //!
    //! \return instance of CTYPE with shape information
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    CTYPE get_shape(const OTYPE<IMPID> &object)
    {
        typedef OTYPE<IMPID> object_type;
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        typedef std::is_same<object_type,field_type> field_check_type;
        typedef std::is_same<object_type,attribute_type> attribute_check_type;
        static_assert(field_check_type::value || attribute_check_type::value,
                      "OBJECT MUST BE A FIELD OR ATTRIBUTE TYPE!");

        return object.template shape<CTYPE>();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get shape visitor
    //! 
    //! This visitor retrieves the shape of an attribute or a field. If the 
    //! object stored in the variant is a group an exception will be thrown.
    //! wrapper template function.
    //!
    //! \tparam CTYPE container type for the shape
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \sa get_shape
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_shape_visitor : public boost::static_visitor<CTYPE>
    {
        public:
            //! result type
            typedef CTYPE result_type;
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
            //! Throw an exception as a group cannot have a shape.
            //! \throws type_error 
            //! \param g group instance
            //! \return empty instance of CTYPE
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "A group does not have a shape!");
                return CTYPE();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the shape of a field.
            //! 
            //! \throws invalid_object_error if the object is not valid
            //! \throws object_error in case of any other error
            //!
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
            //!
            //! \throws invalid_object_error if the object is not valid
            //! \throws object_error in case of any other error
            //!
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
    //! \brief get shape 
    //!
    //! Returns the shape of an attribute or field type. In the case of any
    //! other type compilation fails due to an internal static_assert statement.
    //! The container type used to retrieve the shape information must be
    //! provided by the user as a template parameter.
    //!
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    auto shape = get_shape<shape_t>(field);
    \endcode
    */
    //! \throws invalid_object_error if the object is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam CTYPE container type for the shape
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o instance of VTYPE
    //! \return an instance of CTYPE with the elements for each dimension
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    CTYPE get_shape(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_shape_visitor<CTYPE,GTYPE,FTYPE,ATYPE> visitor_type;

        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
