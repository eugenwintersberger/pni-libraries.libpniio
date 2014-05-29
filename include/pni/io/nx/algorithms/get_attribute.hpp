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
// Created on: Jul 2, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject_traits.hpp"


namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup variant_code
    //! \brief get attribute visitor
    //!
    //! Visitor obtaining an attribute from an object stored in a variant type 
    //! and returns it as an objects_type.
    //!
    //! \tparam VTYPE variant type to act on
    //!
    template<typename VTYPE> 
    class get_attribute_visitor : public boost::static_visitor<VTYPE>
    {
        private:
            string _attribute; //!< name of the attribute to retrieve
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
            //! \brief constructor
            //!
            //! Setting up the visitor. 
            //! \param attr name of the attribute to retrieve
            //!
            get_attribute_visitor(const string &attr):_attribute(attr) {}
          
            //---------------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Return the attribute of a group type instance. 
            //! \param g group instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const group_type &g) const
            {
                return result_type(g.attr(_attribute));
            }

            //---------------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Return an attribute attached to a field. 
            //! \param f field instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const field_type &f) const
            {
                return result_type(f.attr(_attribute));
            }

            //---------------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Attributes obviously cannot hold additional attributes. Thus an
            //! exception will be thrown. The return value here is just to make the
            //! compiler happy - not to complain about a missing return value. 
            //! This method will never return something as an exception is thrown
            //! before.
            //!
            //! \throws nxattribute_error - in any case
            //! \param a instance of an attribute type
            //! \return instance of object_types with attribute
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes cannot have attributes by themself!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup variant_code
    //! \brief get attribute 
    //!
    //! Return the attribute of an object stored in a variant type. If you 
    //! try to retrieve an attribute from an other attribute or the attribute 
    //! does not exist an exception is thrown.
    //!
    //! \throws nxattribute_error in case of errors
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \param a name of the attribute
    //! \return attribute as an object_types variant
    //!
    template<typename VTYPE> 
    typename get_attribute_visitor<VTYPE>::result_type 
    get_attribute(const VTYPE &o,const string &a)
    {
        return boost::apply_visitor(get_attribute_visitor<VTYPE>(a),o);
    }

//end of namespace 
}
}
}
