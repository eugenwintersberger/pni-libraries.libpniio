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
// Created on: Jul 18, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <type_traits>
#include "../nxobject_traits.hpp"
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup variant_code
    //! \brief get attributes visitor
    //! 
    //! Adds all attributes of an object to a container.
    //! \tparam VTYPE variant type
    //! \tparam CTYPE container template
    //!
    template<
             typename VTYPE,
             typename CTYPE
            > 
    class get_attributes_visitor : public boost::static_visitor<void>
    {
        private:
            CTYPE &_container; //!< container holding the children

            //!
            //! \brief append attributes
            //!
            //! Groups as well as fields have the same interface to retrieve
            //! attributes. Thus, a single template function can be used to 
            //! append the attributes to the container.
            //!
            //! \tparam NXTYPE nexus object type
            //! \param o reference to the nexus object
            //!
            template<typename NXTYPE> 
            void append_attributes(const NXTYPE &o) const
            {
                for(auto iter = o.attr_begin(); iter!=o.attr_end();++iter)
                    _container.push_back(VTYPE(*iter));

            }

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
            //! constructor
            get_attributes_visitor(CTYPE &c):_container(c) {}

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //! 
            //! Append group attributes to the attribute container.
            //! \param g group instance
            //! \return child object
            //!
            result_type operator()(const group_type &g) const
            {
                append_attributes(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Append field attributes to the container.
            //! \param f field instance
            //! \return to be ignored
            //!
            result_type operator()(const field_type &f) const
            {
                append_attributes(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Attributes cannot have other attributes - thus an exception 
            //! will be thrown here.
            //!
            //! \throws nxattribute_error no children for attributes
            //! \param a attribute instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup variant_code
    //! \brief get attributes wrapper
    //!
    //! Wrapper function for the get_attributes_visitor template. The parent 
    //! object from which to retrieve its attributes is passed as the first 
    //! argument.  The second argument is the container within which the 
    //! attributes will be stored. The value_type of the container must 
    //! match the variant type of the parent. If this is not the case an 
    //! error will be raised during compilation.
    //!
    //! \throws nxattribute_error if the stored object is an attribute
    //! \tparam VTYPE variant type
    //! \tparam CTYPE container type for the children
    //! \param o parent object as instance of VTYPE
    //! \param c container as instance of CTYPE
    //! \return container with attributes
    //!
    template<
             typename VTYPE,
             typename CTYPE
            > 
    void get_attributes(const VTYPE &o,CTYPE &c)
    {
        //check if the container type is of same type is the variant type
        static_assert(std::is_same<typename CTYPE::value_type,VTYPE>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        return boost::apply_visitor(get_attributes_visitor<VTYPE,CTYPE>(c),o);
    }

//end of namespace
}
}
}
