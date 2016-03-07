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
//
// Created on: Jul 4, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"
#include "../nximp_code_map.hpp"
#include "../nxfilter.hpp"
#include "get_object.hpp"
#include "utils.hpp"

namespace pni{
namespace io{
namespace nx{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief create field visitor
    //!
    //! This visitor creates a field below the group stored in the variant 
    //! type.  If the stored object is not a group an exception will be 
    //! thrown. 
    //! 
    //! \tparam VTYPE variant type
    //! \tparam T data type of the field
    //! \tparam STYPE container type for the shape
    //! \tparam CSTYPE container type for the chunk shape
    //! \tparam FTYPE filter type
    //! \sa create_group
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename T,
             typename STYPE,
             typename FILTERT
            > 
    class create_field_visitor : public boost::static_visitor<
                                 nxobject<GTYPE,FTYPE,ATYPE> 
                                 >
    {
        public:
            //! result type
            typedef nxobject<GTYPE,FTYPE,ATYPE> result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
            //! define the filter type
            typedef FILTERT filter_type;
        private:
            pni::core::string _name;   //!< the name of the field
            STYPE  _shape;             //!< shape of field
            STYPE  _cshape;            //!< chunk shape of the field
            filter_type  _filter;      //!< reference to the filter
        public:

            //----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! Visitor constructor
            //! \param n name of the field
            //! \param s shape 
            //! \param cs chunk shape
            //! \param filter filter instance to use
            //!
            create_field_visitor(const pni::core::string &n,const STYPE &s,
                                 const STYPE &cs,const filter_type &filter):
                _name(n),
                _shape(s),
                _cshape(cs),
                _filter(filter)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Create a new group of name _name and class _class below the 
            //! parent group g. The new group will be stored as object_types 
            //! variant.
            //! 
            //! \throws invalid_object_error if the parent is not valid
            //! \throws type_error if the data type is not supported
            //! \throws size_mismatch_error if chunk-shape and shape do not
            //! match
            //! \throws object_error in case of any other error
            //!
            //! \param g parent group instance
            //! \return new group stored as object_types
            //!
            result_type operator()(const group_type &g) const
            {
                auto f = g.template create_field<T>(_name,_shape,_cshape,_filter);

                return result_type(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! A field cannot create another field. Throw an exception here.
            //!
            //! \throws type_error cannot create field with a field parent
            //!
            //! \param f field instance
            //! \return empty result type
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create a field below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! An attribute cannot create a field - an exception will be 
            //! thrown.
            //! 
            //! \throws type_error cannot create field with an attribute
            //! parent
            //!
            //! \param a attribute instance
            //! \return an empty result type
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create a field below an attribute!");
                return result_type();
            }

            //----------------------------------------------------------------
            //!
            //! \brief process link instances
            //!
            //! Throw type_error as one cannot create a field on a link
            //! instance.
            //!
            //! \throws type_error
            //!
            //! \return invalid instance of nxfield
            //!
            result_type operator()(const nxlink &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create a field below a link instance!");
                return result_type();
            }
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup algorithm_code
    //! \brief field construction
    //!
    //! The full function to construct a field relative to a particular 
    //! group.
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the data type is not supported
    //! \throws size_mismatch_error if chunk-shape and shape do not
    //! match
    //! \throws object_error in case of any other error
    //!
    //! \tparam T data type of the new array
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam STYPE shape type
    //! \tparam FILTERT filter type
    //! \tparam PATHT path type
    //! 
    //! \param location the root location where the field should be created
    //! \param path a string or nxpath object with the path to the field
    //! \param shape the initial shape of the field
    //! \param chunk the chunkd shape of the field
    //! \param filter reference to the filter object
    //!
    //! \return field type wrapped into an nxobject instance
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename STYPE,
             typename FILTERT,
             typename PATHT
            >
    nxobject<GTYPE,FTYPE,ATYPE>
    create_field(const nxobject<GTYPE,FTYPE,ATYPE> &location,const PATHT &path,
                 const STYPE &shape,const STYPE &chunk,
                 const FILTERT &filter)
    {
        typedef create_field_visitor<GTYPE,FTYPE,ATYPE,T,STYPE,FILTERT> visitor_type;

        nxpath fpath = get_path(path);

        pni::core::string field_name = fpath.back().first;
        nxpath parent_path(fpath);
        parent_path.pop_back();

        nxobject<GTYPE,FTYPE,ATYPE> parent = get_object(location,parent_path);
        return boost::apply_visitor(visitor_type(field_name,shape,chunk,filter),parent);

    }
   
    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief field construction template
    //!
    //! This template does field construction without filters
    //! 
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the data type is not supported
    //! \throws size_mismatch_error if chunk-shape and shape do not
    //! match
    //! \throws object_error in case of any other error
    //!
    //! \tparam T data type of the new field
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam STYPE shape type
    //! \tparam PATHT path type
    //!
    //! \param parent the parent object for the field
    //! \param path string or nxpath with the location of the field
    //! \param shape the shape of the field
    //! \param chunk the chunk shape for the field
    //!
    //! \return field type wrapped into an nxobject instance
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename STYPE,
             typename PATHT
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    create_field(const nxobject<GTYPE,FTYPE,ATYPE> &parent,const PATHT &path,
                 const STYPE &shape,const STYPE &chunk)
    {
        //create the default filter
        typename nxobject_trait<nximp_code_map<ATYPE>::icode>::filter_type filter;
        
        return create_field<T>(parent,path,shape,chunk,filter);
    }
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief field construction template
    //!
    //! This template does field construction with filters. Only the primary
    //! shape of the field is given by the user. The chunk shape will be 
    //! created automatically.
    //! 
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the data type is not supported
    //! \throws size_mismatch_error if chunk-shape and shape do not
    //! match
    //! \throws object_error in case of any other error
    //!
    //! \tparam T data type of the new field
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam STYPE shape type
    //! \tparam PATHT path type
    //! \tparam FILTERIMP filter implementation type
    //!
    //! \param parent the parent object for the field
    //! \param path string or nxpath with the location of the field
    //! \param shape the shape of the field
    //! \param filter reference to the filter to use
    //!
    //! \return field type wrapped into an nxobject instance
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename STYPE,
             typename PATHT,
             typename FILTERIMP
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    create_field(const nxobject<GTYPE,FTYPE,ATYPE> &parent,const PATHT &path,
                 const STYPE &shape,const nxfilter<FILTERIMP> &filter)
    {
        //create the default filter
        STYPE chunk(shape);
        chunk.front() = 1;
        
        return create_field<T>(parent,path,shape,chunk,filter);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief field construction template
    //! 
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the data type is not supported
    //! \throws size_mismatch_error if chunk-shape and shape do not
    //! match
    //! \throws object_error in case of any other error
    //!
    //! \tparam T data type of the new field
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam PATHT path type
    //! \tparam STYPE shape type
    //!
    //! \param parent the parent location for the new field
    //! \param path string or nxpath with the relative position for the field
    //! \param shape the shape of the new field
    //!
    //! \return field type wrapped into an nxobject instance
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename PATHT,
             typename STYPE = pni::core::shape_t
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    create_field(const nxobject<GTYPE,FTYPE,ATYPE> &parent,const PATHT &path,
                 const STYPE &shape = {1})
    {
        STYPE chunk(shape);
        chunk.front() = 1;
        
        return create_field<T>(parent,path,shape,chunk);
    }

    //--------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief field construction template
    //! 
    //! This template function is particulary useful if the data type for the 
    //! new field is available only at runtime. 
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws type_error if the data type is not supported
    //! \throws size_mismatch_error if chunk-shape and shape do not
    //! match
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam ARGTS residual argument types
    //!
    //! \param o parent location for the new field
    //! \param tid the type ID for the new field
    //! \param args residual args as for the other function templates
    //!
    //! \return field type wrapped into an nxobject instance
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename ...ARGTS
            >
    nxobject<GTYPE,FTYPE,ATYPE>
    create_field(const nxobject<GTYPE,FTYPE,ATYPE> &o,
                 pni::core::type_id_t tid,ARGTS...args)
    {
        using namespace pni::core;
        switch(tid)
        {
            case type_id_t::UINT8:  return create_field<uint8>(o,args...);
            case type_id_t::INT8:   return create_field<int8>(o,args...);
            case type_id_t::UINT16: return create_field<uint16>(o,args...);
            case type_id_t::INT16:  return create_field<int16>(o,args...);
            case type_id_t::UINT32: return create_field<uint32>(o,args...);
            case type_id_t::INT32:  return create_field<int32>(o,args...);
            case type_id_t::UINT64: return create_field<uint64>(o,args...);
            case type_id_t::INT64:  return create_field<int64>(o,args...);
            case type_id_t::FLOAT32:  return create_field<float32>(o,args...);
            case type_id_t::FLOAT64:  return create_field<float64>(o,args...);
            case type_id_t::FLOAT128: return create_field<float128>(o,args...);
            case type_id_t::COMPLEX32:  return create_field<complex32>(o,args...);
            case type_id_t::COMPLEX64:  return create_field<complex64>(o,args...);
            case type_id_t::COMPLEX128: return create_field<complex128>(o,args...);
            case type_id_t::BINARY:     return create_field<binary>(o,args...);
            case type_id_t::STRING:     return create_field<string>(o,args...);
            case type_id_t::BOOL:       return create_field<bool_t>(o,args...);
            default:
                throw type_error(EXCEPTION_RECORD,
                        "Unknown type id!");
        };
    }

//end of namespace
}
}
}
