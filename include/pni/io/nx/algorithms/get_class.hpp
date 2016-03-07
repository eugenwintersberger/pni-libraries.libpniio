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
//
// Created on: Jul 1, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "../nximp_code.hpp"
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get the class of a group
    //! 
    //! This function template returns the class of a group which is stored in 
    //! its NX_class attribute.
    //!
    //! \throws invalid_object_error if parent group is not valid
    //! \throws shape_mismatch_error the attribute is not a scalar
    //! \throws type_error the attribute type is not supported
    //! \throws io_error attribute data retrieval failed
    //! \throws object_error in case of any other error
    //!
    //! \tparam IMPID implementation ID for the group
    //! \param group the group for which the class should be obtained
    //! \return string with class type
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    pni::core::string get_class(const OTYPE<IMPID> &group)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;
        typedef OTYPE<IMPID> arg_type;

        static_assert(!(std::is_same<arg_type,field_type>::value || 
                      std::is_same<arg_type,attribute_type>::value),
                      "get_class CAN ONLY BE USED WITH GROUP TYPES");

        pni::core::string group_class;
        if(group.attributes.exists("NX_class"))
            group.attributes["NX_class"].read(group_class);

        return group_class;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get class visitor
    //!
    //! Retrieves the Nexus class of a group stored in variant type. 
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_class_visitor : public boost::static_visitor<pni::core::string>
    {
        public:
            //! result type
            typedef pni::core::string result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //!
            //! \brief process groups 
            //!
            //! Retrieve the content of the NX_class attribute of a Nexus 
            //! group and return it as a string. If the group has no type 
            //! (the NX_class attribute does not exist) an exception will 
            //! be thrown.
            //! 
            //! \throws invalid_object_error if parent group is not valid
            //! \throws shape_mismatch_error the attribute is not a scalar
            //! \throws type_error the attribute type is not supported
            //! \throws io_error attribute data retrieval failed
            //! \throws object_error in case of any other error
            //! 
            //!
            //! \param g group instance
            //! \return Nexus class as string
            //!
            result_type operator()(const group_type &g) const
            {
                return get_class(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Fields have no Nexus class. Thus an exception will be thrown 
            //! when this visitor is applied to a field.
            //!
            //! \throw type_error a field type has no class attribute
            //!
            //! \param f instance of a field
            //! \return empty string
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Fields do not have a class!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Attributes have no Nexus class. Thus an exception will be 
            //! thrown. 
            //!
            //! \throw type_error an attribute type cannot have an attribute
            //! at all
            //!
            //! \param a attribute instance
            //! \return empty string
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
                return result_type();
            }

            //----------------------------------------------------------------
            //!
            //! \brief process links
            //!
            //! Links do not have a class, thow type_error is thrown.
            //!
            //! \throw type_error
            //!
            //! \return default constructed string
            //!
            result_type operator()(const nxlink &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Links do not have a type!");
                return result_type();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get group class
    //!
    //! Return the class of a group.
    //!
    //! \throws type_error if the passed object is not a group
    //! \throws invalid_object_error if the passed object is not valid
    //! \throws shape_mismatch_error if NX_class attribute is not a scalar
    //! \throws io_error if attribute data could not be retrieved
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o group as instance of nxobject
    //! \return Nexus class as a tring
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    pni::core::string get_class(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_class_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
