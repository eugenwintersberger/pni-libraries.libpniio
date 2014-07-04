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
#include "../nxobject.hpp"
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
    //! \ingroup algorithm_code
    //! \brief get attribute container
    //! 
    //! Append all attributes of a particular object to a container. 
    //! The container type has to provide a push_back function as any STL 
    //! container does. By appending the attribtues we avoid allocation problems
    //! of the container. The Nexus object can be either a group or a field
    //! object.
    //! 
    //! \tparam CTYPE container type
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //! \param o Nexus object
    //! \param c container to which to append
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    void get_attributes(const OTYPE<IMPID> &o,CTYPE &c)
    {
        static_assert(std::is_same<typename CTYPE::value_type,
                      typename nxobject_trait<IMPID>::attribute_type>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        auto iter = o.attr_begin();
        auto end = o.attr_end();

        while(iter!=end) c.push_back(*iter++);
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attributes visitor
    //! 
    //! Adds all attributes of an object to a container.
    //! \tparam CTYPE container template
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_attributes_visitor : public boost::static_visitor<void>
    {
        private:
            CTYPE &_container; //!< container holding the children
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
                get_attributes(g,_container);
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
                get_attributes(f,_container);
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
    //! \ingroup algorithm_code
    //! \brief get attributes 
    //!
    //! Return a list of attributes attached to an instance of nxobject. 
    //! 
    //!
    //! \throws nxattribute_error if the stored object is an attribute
    //! \tparam CTYPE container type for the children
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o parent object of type nxobject<GTYPE,FTYPE,ATYPE>
    //! \param c container as instance of CTYPE
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void get_attributes(const nxobject<GTYPE,FTYPE,ATYPE> &o,CTYPE &c)
    {
        //check if the container type is of same type is the variant type
        static_assert(std::is_same<typename CTYPE::value_type,ATYPE>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        return boost::apply_visitor(get_attributes_visitor<CTYPE,GTYPE,FTYPE,ATYPE>(c),o);
    }

//end of namespace
}
}
}
