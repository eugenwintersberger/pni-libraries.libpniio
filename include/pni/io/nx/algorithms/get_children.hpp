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
// ==========================================================================
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
    //! \ingroup algorithm_code
    //! \brief get container with children
    //! 
    //! This function template appends all children of a group object to a 
    //! container passed by the user. 
    //! 
    //! \tparam OTYPE parent object template
    //! \tparam IMPID implementation id of the parent 
    //! \tparam CTYPE container type
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename CTYPE
            >
    void get_children(const OTYPE<IMPID> &o,CTYPE &c)
    {
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        typedef OTYPE<IMPID> object_type;

        static_assert(!std::is_same<object_type,field_type>::value,
                "GROUP TYPE REQUIRED - GOT A FIELD TYPE!");
        static_assert(!std::is_same<object_type,attribute_type>::value,
                "GROUP TYPE REQUIRED - GOT AN ATTRIBUTE TYPE!");

        for(auto &child: o)
            c.push_back(child);
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get children visitor
    //! 
    //! Visitor wrapper for the get_children function. This visitor is used
    //! when the input argument is an nxobject instance.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam CTYPE container type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename CTYPE
            > 
    class get_children_visitor : public boost::static_visitor<void>
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
            get_children_visitor(CTYPE &c):_container(c) {}

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //! 
            //! As groups are the only objects that can have children this is 
            //! the only method which needs implementation.
            //!
            //! \param g group instance
            //! \return child object
            //!
            result_type operator()(const group_type &g) const 
            {
                get_children(g,_container);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Fields cannot have children - throw an exception here.
            //! \throws nxfield_error no children for fields
            //! \param f field instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Like fields attributes cannot have children - throw an 
            //! exception here.
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
    //! \brief get children wrapper
    //!
    //! Wrapper function for the get_children_visitor. 
    //!
    //! \throws nxfield_error if the stored object is a field
    //! \throws nxattribute_error if the stored object is an attribute
    //! \throws type_error if one of the stored objects is not a nexus object
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam CTYPE container type
    //! \param o parent object as instance of VTYPE
    //! \param c container as instance of CTYPE
    //! \return container with children
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename CTYPE
            > 
    void get_children(const nxobject<GTYPE,FTYPE,ATYPE> &o,CTYPE &c)
    {
        typedef get_children_visitor<GTYPE,FTYPE,ATYPE,CTYPE> visitor_type;
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;
        typedef typename CTYPE::value_type value_type;
        //check if the container type is of same type is the variant type
        static_assert(std::is_same<value_type,object_type>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        return boost::apply_visitor(visitor_type(c),o);
    }

//end of namespace
}
}
}
