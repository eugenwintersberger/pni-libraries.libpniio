//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 31, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"


namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup algorithm_code
    //! \brief get attributes from an object
    //! 
    //! Return a container with all attributes attached to an object. 
    //! The value type of the container must either be an instance of nxobject
    //! or nxattribute (otherwise a compile time assertion will be raised). 
    //! 
    //! This template will retrieve the attributes from the following types
    //! \li nxfield
    //! \li nxgroup
    //! 
    //! \throws object_error in case of any other erro
    //!
    //! \tparam CTYPE container type where to store the attributes
    //! \tparam PTYPE parent type template
    //! \tparam IMPID parent type implementation id
    //!
    //! \param parent reference to parent instance
    //! \return instance of CTYPE  with attributes
    //! 
    template<
             typename CTYPE, 
             template<nximp_code> class PTYPE,
             nximp_code IMPID
           >
    CTYPE get_attributes(const PTYPE<IMPID> &parent)
    {
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        typedef typename CTYPE::value_type value_type;

        static_assert(std::is_same<value_type,object_type>::value || 
                      std::is_same<value_type,attribute_type>::value,
                      "The containers value_type must be either an attribute"
                      " or an object type!");
        
        CTYPE attributes;

        std::copy(parent.attributes.begin(),parent.attributes.end(),
                  std::back_inserter(attributes));

        return attributes;
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attribute visitor
    //!
    //! Visitor obtaining an attribute from an object stored in a instance
    //! of nxobject.
    //!
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
    class get_attributes_visitor : public boost::static_visitor<CTYPE>
    {
        public:
            //! result type
            typedef CTYPE result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
      
            //---------------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Retrieve all attributes from a group. 
            //! 
            //! \throws object_error in case of any other attribute
            //!
            //! \param g group instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const group_type &g) const
            {
                return get_attributes<result_type>(g);
            }

            //---------------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Retrieve all attributes from a field.
            //!
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const field_type &f) const
            {
                return get_attributes<result_type>(f);
            }

            //---------------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! As attribute cannot have other attributes throw type_error
            //! here. 
            //! 
            //! \throws type_error - in any case
            //! 
            //! \param a instance of an attribute type
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes cannot have attributes by themself!");
                return result_type();
            }

            //----------------------------------------------------------------
            //!
            //! \brief process link
            //!
            //! links do not have attributes -> throw type_error
            //!
            //! \throw type_error
            //!
            //! \return default constructed (invalid) instance of the attribute
            //!         container
            //!
            result_type operator()(const nxlink &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Instances of link do not have attributes!");
                return result_type();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get attributes
    //!
    //! Return all attributes attached to an object in an instance of a 
    //! ser defined container type.
    //! 
    //! \throws invalid_object_error if the parent is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam CTYPE container type
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! 
    //! \param parent reference to the parent object
    //! \return attribute as an object_types variant
    //!
    template<
             typename CTYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    CTYPE get_attributes(const nxobject<GTYPE,FTYPE,ATYPE> &parent)
    {
        typedef get_attributes_visitor<CTYPE,GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),parent);
    }

//end of namespace 
}
}
}
