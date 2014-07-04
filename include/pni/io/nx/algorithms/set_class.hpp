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

#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    
    //!
    //! \ingroup algorithm_internal_code
    //! \brief set class visitor
    //!
    //! This visitor sets the class on a Nexus group stored in a variant type.
    //! \tparam VTYPE variant type
    //! \sa set_class
    //!
    template<typename VTYPE> 
    class set_class_visitor : public boost::static_visitor<void>
    {
        private:
            string _class; //!< Nexus class
        public:
            //! result type
            typedef void result_type;
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
            //! \param s class type as string
            //!
            set_class_visitor(const string &s):_class(s) {}

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Set the NX_class attribute on a group instance. If setting the
            //! attribute fails an exception will be thrown. 
            //! \throws nxgroup_error if setting the class fails
            //! \param g group instance
            //! \return nothing
            //!
            result_type operator()(const group_type &g) const
            {
                try
                {
                    g.template attr<string>("NX_class",true).write(_class);
                }
                catch(...)
                {
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "Error writing NX_class attribute to group "
                            +g.path()+"!");
                }

            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! As fields cannot have a Nexus class an exception will be 
            //! thrown if a field is stored in the variant type passed to 
            //! this visitor.
            //!
            //! \throws nxfield_error fields do not have a class
            //! \param f field instance
            //! \return nothing
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have a class!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Attributes have no Nexus class. Thus an exception is thrown 
            //! if the object stored in the variant passed to this visitor 
            //! is an attribute.
            //!
            //! \throws nxattribute_error attributes do not have a class
            //! \param a attribute instance
            //! \return nothing
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief set class wrapper
    //!
    //! This function is a wrapper for the set_class_visitor template. 
    //!
    //! \throws nxgroup_error cannot set an attribute on the group
    //! \throws nxfield_error fields do not have a class
    //! \throws nxattribute_error attributes do not have a class
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \param c class as string
    //! \return nothing
    //!
    template<typename VTYPE> 
    typename set_class_visitor<VTYPE>::result_type 
    set_class(const VTYPE &o,const string &c)
    {
         boost::apply_visitor(set_class_visitor<VTYPE>(c),o);
    }

//end of namespace
}
}
}
