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
// ========================================================================-==
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
    //! \brief set unit visitor
    //!
    //! This visitors sets the unit on a field stored in the variant type.
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> 
    class set_unit_visitor : public boost::static_visitor<void>
    {
        private:
            string _unit; //!< unit string
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
            //! \param s unit string
            //!
            set_unit_visitor(const string &s):_unit(s) {}
           
            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Groups do not have a unit. Thus an exception will be thrown.
            //! \throws nxgroup_error groups have no unit
            //! \param g group instance
            //! \return nothing
            //1
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Groups do not have units!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Sets the units attribute of the field. 
            //! \throws nxattribute_error in case of IO errors 
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(const field_type &f) const
            {
                f.template attr<string>("units",true).write(_unit);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! As attributes do not have a unit this method throws an 
            //! exception.
            //!
            //! \throws nxattribute_error attributes do not have units
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have units!");
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief set unit wrapper
    //!
    //! Wrapper function for the set_unit_visitor template.
    //! \throws nxgroup_error if the stored object is a group
    //! \throws nxattribute_error in case of attribute IO errors or if 
    //! the stored object is an attribute
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \param s unit string
    //! \return nothing
    //!
    template<typename VTYPE> 
    typename set_unit_visitor<VTYPE>::result_type 
    set_unit(const VTYPE &o,const string &s)
    {
        return boost::apply_visitor(set_unit_visitor<VTYPE>(s),o);
    }

//end of namespace
}
}
}
