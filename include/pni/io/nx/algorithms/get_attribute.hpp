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
    //! Return an attribute from a parent object. 
    //! 
    //! \throws key_error if the object does not have an attribute with name
    //! \tparam PTYPE parent type template
    //! \tparam IMPID parent type implementation id
    //! \param p refernece to parent instance
    //! \param name attributes name
    //! \return attribute type
    //! 
    template<
             template<nximp_code> class PTYPE,
             nximp_code IMPID
           >
    typename nxobject_trait<IMPID>::attribute_type
    get_attribute(const PTYPE<IMPID> &p,const string &name)
    {
        if(!p.has_attr(name))
            throw key_error(EXCEPTION_RECORD,"Object ["+get_name(p)+"] "
                    "does not have an attribute ["+name+"]!");

        return p.attr(name);
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attribute visitor
    //!
    //! Visitor obtaining an attribute from an object stored in a variant type 
    //! and returns it as an objects_type.
    //!
    //! \tparam VTYPE variant type to act on
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_attribute_visitor : public boost::static_visitor<ATYPE>
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
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes cannot have attributes by themself!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
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
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    ATYPE get_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o,const string &a)
    {
        typedef get_attribute_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(a),o);
    }

//end of namespace 
}
}
}
