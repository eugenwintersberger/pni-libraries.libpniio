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
#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief grow a field
    //! 
    //! \throws invalid_object_error if the field is not active
    //! \throws index_error if dimension exceeds the rank
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //! 
    //! \param o the object to grow
    //! \param dimension index of the dimension which to extend
    //! \param extend number of elements by which to extend
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    void grow(OTYPE<IMPID> &o,size_t dimension=0,size_t extend=1)
    {
        o.grow(dimension,extend);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief grow visitor
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class grow_visitor : public boost::static_visitor<void>
    {
        private:
            //! the index of the dimension along which to grow
            size_t _dim;    
            //! the number of elements to grow along the desired dimension
            size_t _extent;
        public:
            //! result type
            typedef void result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param d index of dimension along which to grow
            //! \param e number of elements about which to grow
            //!
            grow_visitor(size_t d,size_t e):
                _dim(d),
                _extent(e)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! \throws type_error
            //!
            //! \param g group instance
            //! \return nothing
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "One cannot grow a group object!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Grows the field along a particular dimenension.
            //!
            //! \throws invalid_object_error if the field is not active
            //! \throws index_error if dimension exceeds the rank
            //! \throws object_error in case of any other error
            //! 
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(field_type &f) const
            {
                f.grow(_dim,_extent);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! \throw type_error
            //!
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                    "An attribute cannot be grown!");
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief grow  object
    //!
    /*!
    \code{.cpp}
    auto field = get_object(root,path_to_field);
    grow(field,1,10);
    \endcode
    */
    //!
    //! \throws invalid_object_error if the field is not active
    //! \throws index_error if dimension exceeds the rank
    //! \throws type_error if the wrapped object is a group or attribute
    //! \throws object_error in the case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o instance of nxobject
    //! \param d dimension along which to grow
    //! \param e extent by which to grow along d
    //! \return nothing
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void grow(nxobject<GTYPE,FTYPE,ATYPE> &o,size_t d=0,size_t e=1)
    {
        typedef grow_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(d,e),o);
    }

//end of namespace
}
}
}
