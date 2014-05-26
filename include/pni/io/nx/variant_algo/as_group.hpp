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
    //! \brief as group visitor
    //!
    //! This visitor return the object stored in a variant as a group object.
    //! Obviously this will only work if the object is really a group object. 
    //! If the stored object is a field or an attribute object an exception 
    //! will be thrown.
    //!
    //! \tparam VTYPE variant type
    //! \sa as_group
    //!
    template<typename VTYPE> 
    class as_group_visitor : public boost::static_visitor<
                             typename nxobject_group<VTYPE>::type
                             >
    {
        public:
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type     group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type     field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;
            //! result type
            typedef group_type result_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Returns the instance of the group object.
            //! \param g group instance
            //! \return instance of group type
            //!
            result_type operator()(const group_type &g) const
            {
                return g;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as the object is not a field type instance
            //! \throws nxgroup_error instance not a group type
            //! \param f field instance
            //! \return empty instance of group_type
            //!
            result_type operator()(const field_type &f) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Object is a field but not a group instance!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Throw an exception as the object is not a group object.
            //! \throws nxfield_error no group instance
            //! \param a attribute instance
            //! \return invalid group instance
            //!
            result_type operator()(const attribute_type &a) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Object is an attribute not a field!");
                return result_type();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief as group wrapper
    //!
    //! Wrapper function for the as_group_visitor template. This function 
    //! takes a variant object and returns a group object if the stored 
    //! object is an instance of a group type. In other cases an exception 
    //! will be thrown.
    /*!
    \code{.cpp}
    object_types group_obj = get_object(root,path_to_group);
    auto g = as_group(group_obj);
    \endcode
    */
    //!
    //! \throws nxgroup_error if stored object is not a group type
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return instance of a group type
    //!
    template<typename VTYPE> 
    typename nxobject_group<VTYPE>::type as_group(const VTYPE &o)
    {
        return boost::apply_visitor(as_group_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
