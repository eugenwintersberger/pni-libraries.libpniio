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
    //! container does. The value_type of the container must be an appropriate
    //! instance of nxobject. Appending the attributes has several advantages:
    //! \li we do not need to allocate memory in advance
    //! \li we can collect attributes from different parent objects
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam CTYPE container type
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //!
    //! \param parent reference to the object holding the attributes
    //! \param container the container instance where to append the attributes
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    void get_attributes(const OTYPE<IMPID> &parent,CTYPE &container)
    {
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        typedef typename CTYPE::value_type value_type;
        static_assert(std::is_same<value_type,object_type>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        for(auto attribute: parent.attributes) 
            container.push_back(attribute);
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attributes visitor
    //! 
    //! Adds all attributes of an object to a container.
    //!
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
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error in case of any other error
            //!
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
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws object_error in case of any other error
            //!
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
            //! \throws type_error as attributes do not have other attributes
            //! \param a attribute instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get attributes 
    //!
    //! Return a list of attributes attached to an instance of nxobject. 
    //! The object must hold an nxfield or nxattribute instance otherwise
    //! type_error is thrown.
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the parent object is an instance of nxattribute
    //! \throws object_error in case of any other error
    //!
    //! \tparam CTYPE container type for the children
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param parent the attributes parent as nxobject instance
    //! \param container the container instance to which the attribute should 
    //! be appended
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void get_attributes(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                        CTYPE &container)
    {
        typedef get_attributes_visitor<CTYPE,GTYPE,FTYPE,ATYPE> visitor_type;
        typedef typename CTYPE::value_type value_type;
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;

        //check if the container type is of same type is the variant type
        static_assert(std::is_same<value_type,object_type>::value,
                      "The target container value type must be the same as the"
                      " variant type!");

        return boost::apply_visitor(visitor_type(container),parent);
    }

//end of namespace
}
}
}
