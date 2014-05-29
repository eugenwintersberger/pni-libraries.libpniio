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
    //! \brief as attribute visitor
    //!
    //! This visitor return the object stored in a variant as a attribute 
    //! object.  Obviously this will only work if the object is really an 
    //! attribute object.  If the stored object is a field or a group object 
    //! an exception will be thrown.
    //!
    //! \tparam VTYPE variant type
    //! \sa as_attribute
    //!
    template<typename VTYPE> 
    class as_attribute_visitor : public boost::static_visitor<
                             typename nxobject_attribute<VTYPE>::type
                             >
    {
        public:
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;
            //! result type
            typedef attribute_type result_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throws an exception as the stored object is not an attribute 
            //! type.
            //! \throws nxattribute_error object not an attribute
            //! \param g group instance
            //! \return invalid attribute instance
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Object is not an attribute but a group!");
                return result_type();
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as the object is not an attribute type 
            //! instance
            //! \throws nxattribute_error instance not a group type
            //! \param f field instance
            //! \return invalid attribute instance
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Object is a field but not an attribute instance!");
                return result_type();
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Returns the atttribute instance.
            //! \param a attribute instance
            //! \return attribute instance
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a;
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief as attribute wrapper
    //!
    //! Wrapper function for the as_attribute_visitor template. This function 
    //! takes a variant object and returns an attribute object if the stored 
    //! object is an instance of an attribute type. In other cases an 
    //! exception will be thrown.
    /*!
    \code{.cpp}
    object_types attr_obj = get_object(root,path_to_atribute);
    auto a = as_attribute(attr_obj);
    \endcode
    */
    //!
    //! \throws nxattribute_error if stored object is not a attribute type
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \return instance of a attribute type
    //!
    template<typename VTYPE> 
    typename nxobject_attribute<VTYPE>::type as_attribute(const VTYPE &o)
    {
        return boost::apply_visitor(as_attribute_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
