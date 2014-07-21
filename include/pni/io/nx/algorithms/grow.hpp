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
    //! \ingroup algorithm_internal_code
    //! \brief grow visitor
    //!
    //!  This visitor grows a field along a particular dimensions. 
    //! Exceptions will be thrown for group and attribute objects.
    //! \tparam VTYPE variant type
    //! \sa grow
    //!
    template<typename VTYPE> 
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
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;

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
            //! A group cannot grow - thus an exception is thrown.
            //! \throws nxgroup_error 
            //! \param g group instance
            //! \return nothing
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "One cannot grow a group object!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Grows the field along a particular dimenension.
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
            //! Throw an exception as an attribute cannot grow.
            //! \throw nxattribute_error
            //! \param a attribute instance
            //! \return nothing
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw type_error(EXCEPTION_RECORD,
                    "An attribute cannot be grown!");
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief grow wrapper
    //!
    //! This function is a wrapper to the grow_visitor. It grows a field 
    //! along a particular dimension. As groups and attribute cannot be 
    //! grown exceptions will be thrown if the stored type is of a group or 
    //! attribute type.
    /*!
    \code{.cpp}
    object_types field = get_object(root,path_to_field);
    grow(field,1,10);
    \endcode
    */
    //! If called without specifying the dimension and the extend by which to 
    //! grow the field will be extended by one element along the first 
    //! dimension.
    //!
    //! \throws nxgroup_error if stored object is a group
    //! \throws nxattribute_error if the stored object is an attribute type
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \param d dimension along which to grow
    //! \param e extent by which to grow along d
    //! \return nothing
    //!
    template<typename VTYPE> 
    typename grow_visitor<VTYPE>::result_type 
    grow(VTYPE &o,size_t d=0,size_t e=1)
    {
        return boost::apply_visitor(grow_visitor<VTYPE>(d,e),o);
    }

//end of namespace
}
}
}
