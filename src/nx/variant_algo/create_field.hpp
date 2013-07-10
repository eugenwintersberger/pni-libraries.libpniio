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

    /*!
    \ingroup variant_code
    \brief field creator 

    This template selects which member function of a group type to use for field
    creation depending on the filter type. This is the default template which
    will be used in cases where the FTYPE is a real filter type. 

    \tparam FTYPE filter type
    */
    template<typename FTYPE> struct field_creator
    {
        /*!
        \brief create field

        This static member function calls the field creation member of a group
        type. In this case the member including the filter as an argument will
        be used. 

        \throws nxgroup_error in case that field creation fails
        \throws shape_mismatch_error in case the field shape and chunk shape do
        not match
        \tparam T data type of the field
        \tparam FT field type
        \tparam GTYPE group type
        \tparam STYPE container type for the shape
        \tparam CSTYPE container type for the chunk shape
        \param g instance of GTYPE - the parent group
        \param name the name of the new field
        \param s instance of STYPE with the field shape
        \param cs instance of CSTYPE with the fields chunk shape
        \param filter instance of FTYPE with the filter class
        \return instance of FT - the newly created field
        */
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

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief field creator 

    This is a specialization of the field_creator template. If FTYPE is int it
    is assumed that no filter shall be used. Thus the groups member function for
    field creation without a filter is used.
    */
    template<> struct field_creator<int>
    {
        /*!
        \brief create field

        This static member function calls the field creation member of a group
        type. In this case the member including the filter as an argument will
        be used. 

        \throws nxgroup_error in case that field creation fails
        \throws shape_mismatch_error in case the field shape and chunk shape do
        not match
        \tparam T data type of the field
        \tparam FT field type
        \tparam GTYPE group type
        \tparam STYPE container type for the shape
        \tparam CSTYPE container type for the chunk shape
        \param g instance of GTYPE - the parent group
        \param name the name of the new field
        \param s instance of STYPE with the field shape
        \param cs instance of CSTYPE with the fields chunk shape
        \param filter instance of FTYPE with the filter class
        \return instance of FT - the newly created field
        */
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

    //-------------------------------------------------------------------------
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
            \throws shape_mismatch_error if the chunk shape and the field shape
            do not match
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

    This wrapper function for the create_field_visitor creates a new field below
    a parent group. No compression is used for this field. The shape arguments
    are optional. If not given a field of shape (1) is created. 

    \code
    object_types g = get_object(...);
    auto field = create_field<int32>(g,"test",shape_t{4,4});
    \endcode

    \throws nxgroup_error if stored object is a group or if field creation fails
    \throws shape_mismatch_error if the chunk shape and the field shape do not
    match
    \throws nxfield_error if the object stored in the variant is a field
    \throws nxattribute_error if the object stored in the variant is an
    attribute
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \tparam CSTYPE container type for the chunk shape (default is shape_t)
    \param o instance of VTYPE with the parent group
    \param n name of the new field
    \param s the shape of the field
    \param cs the chunk shape of the field
    \return object_types with the newly created field
    */
    template<typename T,
             typename VTYPE,
             typename STYPE = shape_t,
             typename CSTYPE = shape_t
             > 
    typename create_field_visitor<VTYPE,T,STYPE,CSTYPE,int>::result_type 
    create_field(const VTYPE &o,const string &n,const STYPE &s=STYPE(),
                 const CSTYPE &cs=CSTYPE())
    {
        typedef create_field_visitor<VTYPE,T,STYPE,CSTYPE,int> visitor_t;
        return boost::apply_visitor(visitor_t(n,s,cs,int(0)),o);
    }
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_field wrapper

    This wrapper function for the create_field_visitor creates a new field below
    a parent group. In this case compression is used for the field. Compression
    always requires you to pass the shape arguments. 

    \code
    object_types g = get_object(...);
    h5::nxdeflate_filter filter(5,true);

    auto field = create_field<int32>(g,"test",shape_t{4,4},shape_t{1,4},filter);
    \endcode

    \throws nxgroup_error if stored object is a group or if field creation fails
    \throws shape_mismatch_error if the chunk shape and the field shape do not
    match
    \throws nxfield_error if the object stored in the variant is a field
    \throws nxattribute_error if the object stored in the variant is an
    attribute
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \tparam CSTYPE container type for the chunk shape (default is shape_t)
    \tparam FTYPE filter type
    \param o instance of VTYPE with the parent group
    \param n name of the new field
    \param s shape of the field
    \param cs chunk shape of the field
    \param filter instance of FTYPE
    \return object_types with the newly created field
    */
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
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_field wrapper

    This wrapper function for the create_field_visitor creates a new field whose
    location and name within the file is determined by a Nexus path object. The
    filename part of the path is ignored by this function. Intermediate groups
    are not created and are assumed to exist. Otherwise an exception will be
    thrown. No compression is used for this field. The shape arguments are
    optional. If not given a field of shape (1) is created. 

    \code
    nxpath path = path_from_string("/:NXentry/:NXinstrument/:NXdetector/data");
    object_types root = get_object(...);
    auto field = create_field<int32>(root,path,shape_t{4,4});
    \endcode

    \throws nxgroup_error if stored object is a group or if field creation fails
    \throws shape_mismatch_error if the chunk shape and the field shape do not
    match
    \throws nxfield_error if the object stored in the variant is a field
    \throws nxattribute_error if the object stored in the variant is an
    attribute
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \tparam CSTYPE container type for the chunk shape (default is shape_t)
    \param o instance of VTYPE with the parent group
    \param path Nexus path to the field
    \param s shape of the new field
    \param cs chunk shape of the field
    \return object_types with the newly created group
    */
    template<typename T,
             typename VTYPE,
             typename STYPE = shape_t,
             typename CSTYPE = shape_t
             > 
    typename create_field_visitor<VTYPE,T,STYPE,CSTYPE,int>::result_type 
    create_field(const VTYPE &o,const nxpath &path,const STYPE &s=STYPE(),
                 const CSTYPE &cs=CSTYPE())
    {
        typedef create_field_visitor<VTYPE,T,STYPE,CSTYPE,int> visitor_t;
        nxpath group_path,target_path;

        split_last(path,group_path,target_path);

        VTYPE parent = get_object(o,group_path);

        return boost::apply_visitor(visitor_t(target_path.begin()->first,
                                              s,cs,int(0)),parent);
    }
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief create_field wrapper

    This wrapper function for the create_field_visitor creates a new field. The
    location and name of the field is determined by a Nexus path with respect to
    the parent object passed as the first argument. Intermediate groups in the
    path are assumed to exist. Otherwise an exception will be thrown.  In this
    case compression is used for the field. Compression always requires you to
    pass the shape arguments. 

    \code
    nxpath path = path_from_string("/:NXentry/:NXinstrument/:NXdetector/data");
    h5::nxdeflate_filter filter(5,true);
    object_types root = get_object(...);
    auto field = create_field<int32>(root,path,shape_t{4,4},shape_t{1,4},filter);
    \endcode

    \throws nxgroup_error if stored object is a group or if field creation fails
    \throws shape_mismatch_error if the chunk shape and the field shape do not
    match
    \throws nxfield_error if the object stored in the variant is a field
    \throws nxattribute_error if the object stored in the variant is an
    attribute
    \tparam T data type of the field
    \tparam VTYPE variant type
    \tparam STYPE container type for the shape (default is shape_t)
    \tparam CSTYPE container type for the chunk shape (default is shape_t)
    \tparam FTYPE filter type
    \param o instance of VTYPE with the parent group
    \param path the path to the new location of the field
    \param s shape of the field
    \param cs chunk shape of the field
    \param filter instance of FTYPE
    \return object_types with the newly created group
    */
    template<typename T,
             typename VTYPE,
             typename STYPE,
             typename CSTYPE,
             typename FTYPE
             > 
    typename create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE>::result_type 
    create_field(const VTYPE &o,const nxpath &path,const STYPE &s,
                 const CSTYPE &cs,const FTYPE &filter)
    {
        typedef create_field_visitor<VTYPE,T,STYPE,CSTYPE,FTYPE> visitor_t;
        nxpath group_path,target_path;

        split_last(path,group_path,target_path);

        VTYPE parent = get_object(o,group_path);

        return boost::apply_visitor( visitor_t(target_path.begin()->first,
                                    s,cs,filter),parent);
    }

//end of namespace
}
}
}
