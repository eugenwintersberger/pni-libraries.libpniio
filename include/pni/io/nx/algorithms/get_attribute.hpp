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

#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"


namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup algorithm_code
    //! \brief get attribute by name
    //! 
    //! Return an attribute from a parent object. This template will work for 
    //! the following types
    //! \li nxfield
    //! \li nxgroup
    //! 
    //! \throws invalid_object_error if parent is not valid 
    //! \throws key_error if the object does not have an attribute with name
    //! \throws object_error in case of any other erro
    //!
    //! \tparam PTYPE parent type template
    //! \tparam IMPID parent type implementation id
    //!
    //! \param parent refernece to parent instance
    //! \param name attributes name
    //! \return attribute type
    //! 
    template<
             template<nximp_code> class PTYPE,
             nximp_code IMPID
           >
    typename nxobject_trait<IMPID>::object_type
    get_attribute(const PTYPE<IMPID> &parent,const string &name)
    {
        return parent.attributes[name];
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
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_attribute_visitor : public boost::static_visitor<
                                  nxobject<GTYPE,FTYPE,ATYPE>
                                  >
    {
        private:
            string _attribute; //!< name of the attribute to retrieve
        public:
            //! result type
            typedef ATYPE result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
      
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
            //! 
            //! \throws invalid_object_error if the group is not valid
            //! \throws key_error if the attribute does not exist
            //! \throws object_error in case of any other attribute
            //!
            //! \param g group instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const group_type &g) const
            {
                return get_attribute(g,_attribute);
            }

            //---------------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Return an attribute attached to a field. 
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws key_error if the attribute does not exist
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return instance of object_types with attribute
            //!
            result_type operator()(const field_type &f) const
            {
                return get_attribute(f,_attribute);
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
                throw type_error(EXCEPTION_RECORD,
                        "Attributes cannot have attributes by themself!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get attribute 
    //!
    //! Returns an attribute from an object stored in an instance of nxobject.
    //! The object must be either an nxfield or an nxgroup instance.
    //! 
    //! \throws invalid_object_error if the parent is not valid
    //! \throws key_error if the attribute does not exist
    //! \throws type_error if the parent is not a field or group
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! 
    //! \param parent reference to the parent object
    //! \param name the attributes name
    //! \return attribute as an object_types variant
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE>
    get_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                  const string &name)
    {
        typedef get_attribute_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(name),parent);
    }

//end of namespace 
}
}
}
