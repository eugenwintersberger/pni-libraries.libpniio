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

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief set the unit
    //!
    //! Set the unit for a field. The unit is stored in an attribute with name 
    //! "units" of data type string. The attribute is scalar.
    //!
    //! \throws invalid_object_error if field is not valid
    //! \throws type_error if data type is not supported
    //! \throws io_error if writing of the value fails
    //! \throws object_error in case of any other error
    //!
    //! \tparam FTYPE field type
    //!
    //! \param field instance of the field 
    //! \param value the value for the units attribute
    //!
    template<typename FTYPE> 
    void set_unit(const FTYPE &field,const pni::core::string &value)
    {
        using namespace pni::core;
        typedef nximp_code_map<FTYPE> map_type;
        typedef typename nxobject_trait<map_type::icode>::field_type field_type;

        static_assert(std::is_same<field_type,FTYPE>::value,
                      "A UNIT CAN ONLY SET ON A FIELD TYPE!");

        auto attribute = field.attributes.template create<string>("units",true);
        attribute.write(value);
    }


    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief set unit visitor
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class set_unit_visitor : public boost::static_visitor<void>
    {
        private:
            pni::core::string _unit; //!< unit string
        public:
            //! result type
            using result_type = void;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! NeXus link type
            using link_type = LTYPE;
       
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param s unit string
            //!
            set_unit_visitor(const pni::core::string &s):_unit(s) {}
           
            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! \throws type_error cannot attach a unit to a group
            //!
            //! \param g group instance
            //! \return nothing
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Groups do not have units!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Sets the units attribute of the field. 
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws type_error if data type is not supported
            //! \throws io_error if writing of the value fails
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(const field_type &f) const
            {
                set_unit(f,_unit);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! \throws type_error cannot attach a unit to an attribute
            //!
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have units!");
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process links
            //!
            //! \throws type_error cannot attach a unit to a link
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Links do not have units!");
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief set unit 
    //!
    //! Set the unit for a field. The unit is stored in an attribute with name 
    //! "units" of data type string. The attribute is scalar.
    //!
    //! \throws invalid_object_error if field is not valid
    //! \throws type_error if data type is not supported
    //! \throws io_error if writing of the value fails
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o instance of the parent object
    //! \param s content of the unit string
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    void set_unit(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o,
                  const pni::core::string &s)
    {
        using visitor_type = set_unit_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;

        return boost::apply_visitor(visitor_type(s),o);
    }

//end of namespace
}
}
}
