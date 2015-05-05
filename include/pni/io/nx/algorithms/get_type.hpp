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

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    //!
    //! \ingroup algorithm_code
    //! \brief get type 
    //!
    //! Get the type ID of a field or attribute. If the type of the object 
    //! is not an attribute or field type compilation will fails due to an 
    //! static_insert within the template.
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws type_error if the data type used is not suppported
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID
    //!
    //! \param o object reference
    //! \return type ID
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    type_id_t get_type(const OTYPE<IMPID> &o)
    {
        typedef OTYPE<IMPID> object_type;
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;

        static_assert(std::is_same<object_type,field_type>::value ||
                      std::is_same<object_type,attribute_type>::value,
                      "OBJECT MUST BE A FIELD OR ATTRIBUTE TYPE!");

        return o.type_id();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get type visitor
    //!
    //! This visitor retrieves the type code of the data stored in a field or
    //! attribute For groups an exception is thrown as they do not have a rank.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \sa get_type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_type_visitor : public boost::static_visitor<type_id_t>
    {
        public:
            //! result type
            typedef type_id_t result_type;
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
            //! Throw an exception as a group cannot have a type.
            //! \throws type_error groups do not have type
            //! \param g group instance
            //! \return NONE type code - can be safely ignored 
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "A group does not have a type!");
                return type_id_t::NONE;
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the type of a field.
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws type_error if the data type is not supported
            //! \throws object_error in case of any  other error
            //!
            //! \param f field instance
            //! \return type code of field data
            //!
            result_type operator()(const field_type &f) const
            {
                return f.type_id();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Returns the type of the attribute.
            //! 
            //! \throws invalid_object_error if the attribute is not valid
            //! \throws type_error if the data type is not supported
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return type code of the attribute data
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.type_id();
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get type 
    //!
    //! Get the type ID of a field or attribute. 
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    type_id_t tc = get_type(field);
    \endcode
    */
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws type_error if the data type is not supported or the object
    //! is a group 
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute_type
    //!
    //! \param o object wrapped into nxobject
    //! \return value of type_id_t
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    type_id_t get_type(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_type_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
