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
    //! \brief get rank
    //!
    //! Return the number of dimensions of an attribute or field.
    //!
    //! \throws invalid_object_error if object is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //!
    //! \param o reference to the field or attribute
    //! \return number of dimensions
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    size_t get_rank(const OTYPE<IMPID> &o)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;

        static_assert(std::is_same<field_type,OTYPE<IMPID>>::value ||
                      std::is_same<attribute_type,OTYPE<IMPID>>::value,
                      "THE RANK CAN ONLY BE OBTAINED FROM FIELDS AND"
                      " ATTRIBUTE!");

        return o.rank();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get rank visitor
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class get_rank_visitor : public boost::static_visitor<size_t>
    {
        public:
            //! result type
            using result_type = size_t;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! NeXus link type
            using link_type = LTYPE;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throw an exception as a group cannot have a rank.
            //!
            //! \throws type_error groups do not have a rank
            //! \param g group instance
            //! \return 0
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Groups do not have a shape!");
                return size_t(0);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the rank of a field.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return number of dimensions
            //!
            result_type operator()(const field_type &f) const
            {
                return get_rank(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //! 
            //! Returns the rank of the attribute.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return number of dimensions
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.rank();
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process nxlink instances
            //! 
            //! Throws type_error exception - a link does not have a rank.
            //!
            //! \throws type_error
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,"Links do not have a rank!");
                return size_t(0);
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get rank 
    //!
    //! Return the number of dimensions of a field or attribute wrapped in an 
    //! instance of nxobject.
    //!
    /*!
    \code{.cpp}
    auto field = get_object(root,path_to_field);
    size_t r = get_rank(field);
    \endcode
    */
    //!
    //! \throws invalid_object_error if object is not valid
    //! \throws type_error if the wrapped object is a group
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o object instance
    //! \return number of dimensions
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    size_t get_rank(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = get_rank_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
