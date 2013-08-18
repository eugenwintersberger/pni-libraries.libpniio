/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 1, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{


    /*!
    \ingroup variant_code
    \brief is class visitor

    Checks if the group stored in a variant type is of a particular class.
    \tparam VTYPE variant type
    */
    template<typename VTYPE> 
    class is_class_visitor : public boost::static_visitor<string>
    {
        private:
            string _class; //!< class type
        public:
            //! result type
            typedef bool result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param s class type
            */
            is_class_visitor(const string &s):_class(s) {}
           
            //-----------------------------------------------------------------
            /*!
            \brief process groups

            Check the class of the group stored in the variant type. 
            If the groups class and the _class match the method returns true,
            false otherwise. If the group does not have an NX_class attribute
            false will be returnd.
            \throws nxgroup_error if NX_class attribute does not exist
            \param g group instance
            \return true if class types match, false otherwise
            */
            result_type operator()(const group_type &g) const
            {
                string buffer;
                if(g.has_attr("NX_class"))
                    g.attr("NX_class").read(buffer);
                else
                    return false;

                return buffer==_class;

            }

            //-----------------------------------------------------------------
            /*!
            \brief process fields
            
            As fields do not have a class type this method throws an exception. 
            \throws nxfield_error fields do not have a class
            \param f field instance
            \return can be ignored 
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have a class!");
                return result_type();
            }

            //----------------------------------------------------------------
            /*!
            \brief process attributes

            Attributes do not have a class type. Thus this method throws an
            exception. 
            \throws nxattribute_error attributes have no class
            \param a attribute instance
            \return can be ignored
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
                return result_type();
            }
    };

    /*!
    \ingroup variant_code
    \brief is class wrapper 

    Wrapper function for the is_class_visitor template. 

    \throws nxgroup_error if group does not have an NX_class attribute
    \throws nxfield_error if the stored object is a field
    \throws nxattribute_error if the stored object is an attribute
    \tparam VTYPE variant type
    \param o instance of VTYPE
    \param c Nexus class to check for
    \return true if group class and c match, false otherwise
    */
    template<typename VTYPE> 
    typename is_class_visitor<VTYPE>::result_type 
    is_class(const VTYPE &o,const string &c)
    {
        return boost::apply_visitor(is_class_visitor<VTYPE>(c),o);
    }

//end of namespace
}
}
}
