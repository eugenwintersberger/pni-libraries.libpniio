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
    //! \brief get parent visitor
    //!
    //! This visitor retrieve the parent of an object stored in a variant 
    //! type.  This works for fields and groups. Parent retrieval is 
    //! currently not supported for attribute. The parent object will be 
    //! returned as an object_types type.
    //!
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> 
    class get_parent_visitor : public boost::static_visitor<VTYPE>
    {
        public:
            //! result type
            typedef VTYPE result_type;
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
            //! Return the parent group of a group. 
            //! \param g group instance
            //! \return parent group
            //!
            result_type operator()(const group_type &g) const
            {
                return g.parent();
                //return result_type(group_type(g.parent()));
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Return the fields parent group.
            //! \param f field instance
            //! \return parent group of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return f.parent();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute
            //!
            //! Retrieve the type of an object.
            //! \throws nxattribute_error parent retrieval not supported
            //! \param a attribute instance
            //! \return to be ignored
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.parent();

                //auto object = a.parent();
               
                //the situation is a bit more difficult here as an attribute can
                //have either a field or a group as its parent.
                /*
                if(object.object_type() == nxobject_type::NXFIELD)
                    return result_type(field_type(object));
                else if(object.object_type() == nxobject_type::NXGROUP)
                    return result_type(group_type(object));
                else
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Parent is of unknown type!");

                //just to make the compiler happy
                return result_type();
                */
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief get parent wrapper
    //!
    //! Wrapper for the get_parent_visitor template. Returns the parent object 
    //! of an object stored in the variant type. As parent retrieval works only 
    //! for fields and groups an exception will be thrown if the stored object 
    //! is an attribute.
    //!
    //! \throws nxattribute_error if the stored object is an attribute
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return parent object
    //!
    template<typename VTYPE> 
    typename get_parent_visitor<VTYPE>::result_type get_parent(const VTYPE &o)
    {
        return boost::apply_visitor(get_parent_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
