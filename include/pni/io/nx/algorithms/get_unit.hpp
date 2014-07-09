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
    //! \ingroup algorithm_code
    //! \brief get the unit of a field
    //!
    //! Return the unit string for a field 
    //!
    template<typename FTYPE> string get_unit(const FTYPE &field)
    {
        string buffer;

        if(field.attributes.exists("units"))
            field.attributes["units"].read(buffer);

        return buffer;
    }

    //!
    //! \ingroup algorithm_internal_code
    //! \brief get unit visitor
    //!
    //! Retrieves the unit string of a field stored in the variant type.
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> 
    class get_unit_visitor : public boost::static_visitor<string>
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
            //! \brief process groups
            //!
            //! Groups have no units thus an exception is thrown.
            //! \throws nxgroup_error groups have no unit
            //! \param g group instance
            //! \return an empty string - to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Group ["+g.path()+"] does not have a unit!");
                return result_type();
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Retrieve the value of the fields unit attribute. If the field 
            //! does not have a units attribute an empty string is returned.
            //!
            //! \throws nxattribute_error in case of problems with attribute 
            //! access
            //! \param f field instance
            //! \return unit string
            //!
            result_type operator()(const field_type &f) const
            {
                return get_unit(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Attributes do not posses units - an exception will be thrown.
            //! \throw nxattribute_error attributes do not have units
            //! \param a attribute instance
            //! \return an empty string - to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attribute ["+a.name()+"] does  not have a unit!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_internal_code
    //! \brief get unit wrapper
    //!
    //! Wrapper function for the get_unit_visitor. It returns the the unit 
    //! string associated with a field stored in the variant type. If the 
    //! object stored is not a field exceptions are thrown. 
    //! If a field does not posses a unit attribute an empty string is 
    //! returned.
    //!
    //! \throws nxgroup_error if the stored object is a group
    //! \throws nxattribute_error if there are IO errors with attributes 
    //! or the stored object is an attribute
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return unit string
    //!
    template<typename ...TYPES> 
    typename get_unit_visitor<boost::variant<TYPES...>>::result_type 
    get_unit(const boost::variant<TYPES...> &o)
    {
        return boost::apply_visitor(get_unit_visitor<boost::variant<TYPES...>>(),o);
    }

//end of namespace
}
}
}
