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
 * Created on: Jul 4, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../nxvariant_traits.hpp"
#include "get_object.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    template<typename FTYPE> struct field_creator
    {
        template<typename T,
                 typename FT,
                 typename GTYPE,
                 typename STYPE,
                 typename CSTYPE
                 >
        static FT create_field(const GTYPE &g,
                               const string &name, 
                               const STYPE &s,
                               const CSTYPE &cs,
                               const FTYPE &filter)
        {
            return g.template create_field<T>(name,s,cs,filter);
        }
    };

    template<> struct field_creator<int>
    {
        template<typename T,
                 typename FT,
                 typename GTYPE,
                 typename STYPE,
                 typename CSTYPE
                >
        static FT create_field(const GTYPE &g,
                               const string &name,
                               const STYPE &s,
                               const CSTYPE &cs,
                               const int &filter)
        {

            return g.template create_field<T>(name,s,cs);
        }

    };

    /*!
    \ingroup variant_code
    \brief create field visitor

    This visitor creates a field below the group stored in the variant type. 
    If the stored object is not a group an exception will be thrown. 
    \tparam VTYPE variant type
    \tparam T data type of the field
    \tparam STYPE container type for the shape
    \tparam CSTYPE container type for the chunk shape
    \tparam FTYPE filter type
    \sa create_group
    */
    template<typename VTYPE,
             typename T,
             typename STYPE,
             typename CSTYPE,
             typename FTYPE
            > 
    class create_field_visitor : public boost::static_visitor<
                                 typename nxvariant_traits<
                                 typename nxvariant_member_type<VTYPE,0>::type 
                                 >::object_types 
                                 >
    {
        private:
            string _name;  //!< the name of the field
            STYPE _shape;  //!< shape of field
            CSTYPE _cshape; //!< chunk shape of the field
            FTYPE _filter;  //!< filter type
        public:
            //! first type of the variant type
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type
            typedef typename nxvariant_traits<first_member>::object_types result_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;

            create_field_visitor(const string &n,const STYPE &s,const CSTYPE
                    &cs,const FTYPE &filter):
                _name(n),
                _shape(s),
                _cshape(cs),
                _filter(filter)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Create a new group of name _name and class _class below the parent
            group g. The new group will be stored as object_types variant.
            \throws nxgroup_error in case of errors
            \param g parent group instance
            \return new group stored as object_types
            */ 
            result_type operator()(const group_type &g) const
            {
                typedef field_creator<FTYPE> creator_t;
                auto f = creator_t::template create_field<T,field_type>(g,_name,_shape,_cshape,_filter);

                return result_type(f);

            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            A field cannot create another field. Throw an exception here.
            \throws nxfield_error  
            \param f field instance
            \return empty result type
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Cannot create a group below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            An attribute cannot create a field - an exception will be thrown.
            \throws nxattribute_error 
            \param a attribute instance
            \return an empty result type
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Cannot create a group below an attribute!");
                return result_type();
            }
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_field wrapper

    Wrapper function for the create_group_visitor. This wrapper creates a new
    group of a particular name and class directly below the parent group.
    In order to successfully create a group at least the name argument must be
    non-empty. If an empty string is passed as the groups class then the
    NX_class attribute will not be set.


    \throws nxgroup_error if stored object is a group
    \tparam VTYPE variant type
    \param o instance of VTYPE with the parent group
    \param n name of the new group
    \param c Nexus class of the group
    \return object_types with the newly created group
    */
    template<typename T,
             typename VTYPE,
             typename STYPE = shape_t,
             typename CSTYPE = shape_t,
             typename FTYPE = int
             > 
    typename create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE>::result_type 
    create_field(const VTYPE &o,const string &n,const STYPE &s=STYPE(),
                 const CSTYPE &cs=CSTYPE())
    {
        typedef create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE> visitor_t;
        return boost::apply_visitor(visitor_t(n,s,cs,int(0)),o);
    }
    
    template<typename T,
             typename VTYPE,
             typename STYPE,
             typename CSTYPE,
             typename FTYPE
             > 
    typename create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE>::result_type 
    create_field(const VTYPE &o,const string &n,const STYPE &s,
                 const CSTYPE &cs,const FTYPE &filter)
    {
        typedef create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE> visitor_t;
        return boost::apply_visitor( visitor_t(n,s,cs,filter),o);
    }

//end of namespace
}
}
}
