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
// Created on: Jul 1, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup variant_code
    //! \brief get name visitor
    //!
    //! This visitor retrieves the name of an object stored in a variant type. 
    //! The class is not intended to be directly used. Rather use the get_name
    //! wrapper template function.
    //! 
    //! \tparam VTYPE variant type
    //! \sa get_name
    //!
    template<typename VTYPE> 
    class get_name_visitor : public boost::static_visitor<string>
    {
        public:
            //! result type
            typedef string result_type;
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
            //! Retrieve the name from a group instance.
            //! \param g group instance
            //! \return string with the group name
            //!
            result_type operator()(const group_type &g) const
            {
                return g.name();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Retrieve the name of a field instance.
            //! \param f field instance
            //! \return name of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return f.name();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Retrieve the name of an attribute instance.
            //! \param a attribute instance
            //! \return name of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.name();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief get name wrapper
    //!
    //! Wrapper function for the get_name_visitor template. Use this function
    //! instead of get_name_visitor directly. 
    //! \tparam VTYPE
    //! \param o instance of VTYPE
    //! \return a string with the name of the object
    //!
    template<typename VTYPE> 
    typename get_name_visitor<VTYPE>::result_type get_name(const VTYPE &o)
    {
        return boost::apply_visitor(get_name_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
