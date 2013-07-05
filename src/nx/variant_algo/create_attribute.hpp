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

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create attribute visitor

    This visitor creates an attribute below the group stored in the variant type. 
    If the stored object is not a group an exception will be thrown. 
    \tparam VTYPE variant type
    \tparam T data type of the attribute
    \tparam STYPE container type for the shape
    \sa create_attribute
    */
    template<typename VTYPE,
             typename T,
             typename STYPE
            > 
    class create_attribute_visitor : public boost::static_visitor<
                                 typename nxvariant_traits<
                                 typename nxvariant_member_type<VTYPE,0>::type 
                                 >::object_types 
                                 >
    {
        private:
            string _name;  //!< the name of the field
            STYPE _shape;  //!< shape of field
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

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param n name of the attribute
            \param s shape of the attribute
            */
            create_attribute_visitor(const string &n,const STYPE &s):
                _name(n),
                _shape(s)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Create a new attribute of name _name attached to group g.ant.
            \throws nxattribute_error in case of errors
            \param g parent group instance for the attribute
            \return new group stored as object_types
            */ 
            result_type operator()(const group_type &g) const
            {
                attribute_type a = g.template attr<T>(_name,_shape);

                return result_type(a);

            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Create a new attribute of name _name attached to field f.
            \throws nxattribute_error in case of errors
            \param f field instance
            \return empty result type
            */
            result_type operator()(const field_type &f) const
            {
                attribute_type a = f.template attr<T>(_name,_shape);
                return result_type(a);
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            An attribute cannot create an  attribute - an exception will be
            thrown.
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
    \brief create_attribute wrapper

    This wrapper function for the create_attribute_visitor creates a new
    attribute below attached to an object stored in the varian type.  The object
    must be a field or a group type.

    \code
    object_types g = get_object(...);
    create_attribute<int32>(g,"test",shape_t{4,4});
    \endcode

    \throws nxattribute_error in case of errors
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \param o instance of VTYPE with the parent group
    \param n name of the new attribute
    \param s shape of the attribute
    \return object_types with the newly created attribute
    */
    template<typename T,
             typename VTYPE,
             typename STYPE = shape_t,
             typename CSTYPE = shape_t
             > 
    typename create_attribute_visitor<VTYPE,T,STYPE>::result_type 
    create_attribute(const VTYPE &o,const string &n,const STYPE &s=STYPE())
    {
        typedef create_attribute_visitor<VTYPE,T,STYPE> visitor_t;
        return boost::apply_visitor(visitor_t(n,s),o);
    }
    
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_attribute wrapper

    Wrapper function for the create_attribute_visitor template. The function
    creates a new attribute described  by a path relative to the object passed
    as the first argument of the function. This object must be either a gruop or
    a field.

    \code
    nxpath path = path_from_string("/:NXentry/:NXinstrument/:NXdetector/data@test");
    object_types root = get_object(...);
    create_attribute<int32>(root,path,shape_t{4,4});
    \endcode

    \throws nxattribute_error in the case of errors
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \param o instance of VTYPE with the parent group
    \param path Nexus path to the attribute
    \param s shape of the attribute
    \return object_types with the newly created attribute
    */
    template<typename T,
             typename VTYPE,
             typename STYPE = shape_t
             > 
    typename create_attribute_visitor<VTYPE,T,STYPE>::result_type 
    create_attribute(const VTYPE &o,const nxpath &path,const STYPE &s=STYPE())
    {
        typedef create_attribute_visitor<VTYPE,T,STYPE> visitor_t;
        nxpath group_path,target_path;

        //check if the path describes an attribute
        if(path.attribute().empty())
            throw nxattribute_error(EXCEPTION_RECORD,
                    "Path does not describe an attribute!");

        split_last(path,group_path,target_path);

        VTYPE parent = get_object(o,group_path);
        parent = get_child(parent,target_path.begin()->first,
                           target_path.begin()->second);

        return boost::apply_visitor(visitor_t(target_path.attribute(),s),parent);
    }
    

//end of namespace
}
}
}
