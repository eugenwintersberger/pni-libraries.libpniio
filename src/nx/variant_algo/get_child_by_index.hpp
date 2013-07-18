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
 * Created on: Jul 18, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <sstream>
#include "../nxvariant_traits.hpp"
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"
#include "get_size.hpp"

namespace pni{
namespace io{
namespace nx{


    /*!
    \ingroup variant_code
    \brief get child by index visitor
   
    Retrieves the child of a group according to its index. Clearly this works
    only for groups. In case of attributes and fields an exception is thrown.
    \tparam VTYPE variant type
    */
    template<typename VTYPE> 
    class get_child_by_index_visitor : public boost::static_visitor<
                              typename nxvariant_traits<typename
                              nxvariant_member_type<VTYPE,0>::type>::object_types>
    {
        private: 
            size_t _index;
        public:
            //! first type of the variant type
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type
            typedef typename nxvariant_traits<first_member>::object_types result_type;
            //! Nexus object type
            DEFINE_NXOBJECT(first_member) object_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param index the index of the element
            */
            get_child_by_index_visitor(size_t index): _index(index) {}
           
            //-----------------------------------------------------------------
            /*!
            \brief process groups
            
            Returns the child of a group identified by its index. If the index
            exceeds the total number of elements an index_error exception will
            be thrown.

            \throws pni::core::index_error if index exceeds total number of
            children
            \param g group instance
            \return child object
            */
            result_type operator()(const group_type &g) const
            {
                if(_index>=g.nchildren())
                {
                    std::stringstream ss;
                    ss<<"Index "<<_index<<" exceeds total number of group ";
                    ss<<" children "<<g.nchildren()<<"!";

                    throw index_error(EXCEPTION_RECORD,ss.str());
                }


                //here comes the interesting part
                result_type result; 

                object_type o = g[i];
                if(o.object_type() ==  nxobject_type::GROUP)
                    return result_type(group_type(o));
                else if(o.object_type() == nxobject_type::FIELD)
                    return result_type(field_type(o));
                else
                    throw type_error(EXCEPTION_RECORD,
                            "Child has unkown Nexus type!");


                //in the worst case we return an invalid object
                return result_type();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process fields

            Fields cannot have children - throw an exception here.
            \throws nxfield_error no children for fields
            \param f field instance
            \return to be ignored
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attributes

            Like fields attributes cannot have children - throw an exception
            here.
            \throws nxattribute_error no children for attributes
            \param a attribute instance
            \return to be ignored
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
    };

    /*!
    \ingroup variant_code
    \brief get child by index wrapper

    Wrapper function for the get_child_visitor template. 
    \throws nxfield_error if the stored object is a field
    \throws nxattribute_error if the stored object is an attribute
    \throws index_error if the index exceeds the number of children
    \throws type_error if the Nexus object is of unknown type
    \tparam VTYPE variant type
    \param n name of the child
    \param c class of the child (only for groups)
    \return child object
    */
    template<typename VTYPE> 
    typename get_child_by_index_visitor<VTYPE>::result_type
    get_child(const VTYPE &o,size_t i)
    {
        return boost::apply_visitor(get_child_visitor<VTYPE>(i),o);
    }

//end of namespace
}
}
}
