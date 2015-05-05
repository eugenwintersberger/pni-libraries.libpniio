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

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get the unit of a field
    //!
    //! Return the unit string of a field. This function works only for field 
    //! types as attributes cannot store unit information.
    //! 
    //! \tparam invalid_object_error if the field is not valid
    //! \tparam shape_mismatch_error if the unit attribute is not scalar
    //! \tparam io_error if reading the attribute failed
    //! \tparam type_error if the type used for the units attribute is not 
    //! supported
    //! \tparam object_error in case of any other error
    //!
    //! \param field instance of the Nexus field
    //! \return content of the units string
    //!
    template<typename FTYPE> pni::core::string get_unit(const FTYPE &field)
    {
        typedef nximp_code_map<FTYPE> imp_map;
        typedef typename nxobject_trait<imp_map::icode>::field_type field_type;
        
        static_assert(std::is_same<FTYPE,field_type>::value,
                      "UNIT CAN ONLY BE RETRIEFVED FROM A FIELD TYPE!");

        pni::core::string buffer;

        if(field.attributes.exists("units"))
            field.attributes["units"].read(buffer);

        return buffer;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get unit visitor
    //!
    //! Retrieves the unit string of a field stored in the variant type.
    //! \tparam VTYPE variant type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_unit_visitor : public boost::static_visitor<pni::core::string>
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
    
            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Groups have no units thus an exception is thrown.
            //! \throws type_error cannot retrieve units information from a 
            //! type
            //!
            //! \param g group instance
            //! \return an empty string - to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot retreive a unit from a group!");

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
            //! \tparam invalid_object_error if the field is not valid
            //! \tparam shape_mismatch_error if the unit attribute is not scalar
            //! \tparam io_error if reading the attribute failed
            //! \tparam type_error if the type used for the units attribute is not 
            //! supported
            //! \tparam object_error in case of any other error
            //!
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
            //!
            //! \throw type_error cannot retrieve unit from an attribute
            //!
            //! \param a attribute instance
            //! \return an empty string - to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot retrieve a unit from an attribute type!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal
    //! \brief get unit 
    //!
    //! Wrapper function for the get_unit_visitor. It returns the the unit 
    //! string associated with a field stored in the variant type. If the 
    //! object stored is not a field exceptions are thrown. 
    //! If a field does not posses a unit attribute an empty string is 
    //! returned.
    //!
    //! \tparam invalid_object_error if the field is not valid
    //! \tparam shape_mismatch_error if the unit attribute is not scalar
    //! \tparam io_error if reading the attribute failed
    //! \tparam type_error if the type used for the units attribute is not 
    //! supported
    //! \tparam object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o instance of VTYPE
    //! \return unit string
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    pni::core::string get_unit(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_unit_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
