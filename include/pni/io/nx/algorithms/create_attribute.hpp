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
// Created on: Jul 4, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief create attribute visitor
    //!
    //! This visitor creates an attribute below the group stored in an nxobject 
    //! type. If the nxobject instance holds an instance of nxattribute a 
    //! type_error exception is thrown.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE fieldtype
    //! \tparam ATYPE attribute type
    //! \tparam T data type of the attribute
    //! \tparam STYPE container type for the shape
    //!
    //! \sa create_attribute
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename T,
             typename STYPE
            > 
    class create_attribute_visitor : public boost::static_visitor<
                                     nxobject<GTYPE,FTYPE,ATYPE>  
                                     >
    {
        private:
            pni::core::string _name;  //!< the name of the field
            STYPE _shape;             //!< shape of field
            bool  _overwrite;         //!< overwrite flag for the attribute
        public:
            //! result type
            typedef nxobject<GTYPE,FTYPE,ATYPE> result_type;
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
            //! \param n name of the attribute
            //! \param s shape of the attribute
            //! \param o overwrite flag
            //!
            create_attribute_visitor(const pni::core::string &n,
                                     const STYPE &s,bool o):
                _name(n),
                _shape(s),
                _overwrite(o)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Create a new attribute of name _name attached to group g.ant.
            //! 
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error if the data type is not supported
            //! \throws object_error in case of any other error
            //!
            //! \param g parent group instance for the attribute
            //! \return new group stored as object_types
            //!
            result_type operator()(const group_type &g) const
            {
                auto attr =  g.attributes.template create<T>(_name,_shape,_overwrite);
                return result_type(attr);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Create a new attribute of name _name attached to field f.
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws type_error if the datat type is not supported
            //! \throws object_error in case of any other errors
            //!
            //! \param f field instance
            //! \return empty result type
            //!
            result_type operator()(const field_type &f) const
            {
                auto attr = f.attributes.template create<T>(_name,_shape,_overwrite);
                return result_type(attr);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! An attribute cannot create an  attribute - an exception will be
            //! thrown.
            //!
            //! \throws type_error as one cannot attach an attribute to an 
            //! attribute
            //!
            //! \param a attribute instance
            //! \return an empty result type
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create an attribute at an attribute!");
                return result_type();
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create multidimensional attribute 
    //!
    //! Create an attribute of a particular name, type, and shape at a parent 
    //! object. The parent is provided as an instance of nxobject. 
    /*!
    \code
    auto g = get_object(...);
    auto attr = create_attribute<int32>(g,"test",shape_t{4,4});
    \endcode
    */
    //!
    //! The last argument is the shape of the attribute. If now shape is passed
    //! a scalar attribute will be created. 
    //!
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws type_error if the data type is not supported or the parent
    //! holds an nxattribute instance
    //! \throws object_error in case of any other error
    //! 
    //! \tparam T data type of the attribute
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam STYPE shape container type
    //! 
    //! \param parent instance of parent object
    //! \param name name of the new attribute
    //! \param shape shape of the attribute
    //! \param overwrite if true an existing attribute will be overwritten
    //! \return attribute as an instance of nxobject
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename STYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    create_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                     const pni::core::string &name,
                     const STYPE &shape,
                     bool overwrite=false)
    {
        typedef create_attribute_visitor<GTYPE,FTYPE,ATYPE,T,STYPE> visitor_t;
        return boost::apply_visitor(visitor_t(name,shape,overwrite),parent);
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create scalar attribute 
    //!
    //! Create an attribute of a particular name, type, and shape at a parent 
    //! object. The parent is provided as an instance of nxobject. 
    /*!
    \code
    auto g = get_object(...);
    auto attr = create_attribute<int32>(g,"test",shape_t{4,4});
    \endcode
    */
    //!
    //! The last argument is the shape of the attribute. If now shape is passed
    //! a scalar attribute will be created. 
    //!
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws type_error if the data type is not supported or the parent
    //! holds an nxattribute instance
    //! \throws object_error in case of any other error
    //! 
    //! \tparam T data type of the attribute
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! 
    //! \param parent instance of the parent
    //! \param name name of the new attribute
    //! \param overwrite if true overwrite an existing attribute of equal name
    //! \return attribute as an instance of nxobject
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    create_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                     const pni::core::string &name,
                     bool overwrite=false)
    {
        return create_attribute<T>(parent,name,shape_t{},overwrite);
    }
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create attribute 
    //! 
    //! Create an attribute of a given name, shape, and type at a parent 
    //! object. This special version of create_attribute is particularly 
    //! useful in situations where the data type is provided at runtime. 
    /*!
    \code
    auto parent = get_object(...);
    string name = get_name_from_user(...);
    type_id_t tid = get_type_from_user(...);

    auto attr = create_attribute(parent,tid,name);
    \endcode
    */
    //! The first two arguments are the parent object and the type id.
    //! All other arguments are the same as for the other create_attribute
    //! templates.
    //!
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws type_error if the data type is not supported or the parent
    //! holds an nxattribute instance
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam STYPE shape container type
    //! 
    //! \param o instance of VTYPE with the parent group
    //! \param tid type id of the attributes data type
    //! \param args residual arguments
    //!
    //! \return newly created attribute as an instance of nxobject
    //! 
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename ...ARGTS
            >
    nxobject<GTYPE,FTYPE,ATYPE>
    create_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o,type_id_t tid,
                     ARGTS ...args)
    {
        using namespace pni::core;
        
        if(tid == type_id_t::UINT8)
            return create_attribute<uint8>(o,args...);
        else if(tid == type_id_t::INT8)
            return create_attribute<int8>(o,args...);
        else if(tid == type_id_t::UINT16)
            return create_attribute<uint16>(o,args...);
        else if(tid == type_id_t::INT16)
            return create_attribute<int16>(o,args...);
        else if(tid == type_id_t::UINT32)
            return create_attribute<uint32>(o,args...);
        else if(tid == type_id_t::INT32)
            return create_attribute<int32>(o,args...);
        else if(tid == type_id_t::UINT64)
            return create_attribute<uint64>(o,args...);
        else if(tid == type_id_t::INT64)
            return create_attribute<int64>(o,args...);
        else if(tid == type_id_t::FLOAT32)
            return create_attribute<float32>(o,args...);
        else if(tid == type_id_t::FLOAT64)
            return create_attribute<float64>(o,args...);
        else if(tid == type_id_t::FLOAT128)
            return create_attribute<float128>(o,args...);
        else if(tid == type_id_t::COMPLEX32)
            return create_attribute<complex32>(o,args...);
        else if(tid == type_id_t::COMPLEX64)
            return create_attribute<complex64>(o,args...);
        else if(tid == type_id_t::COMPLEX128)
            return create_attribute<complex128>(o,args...);
        else if(tid == type_id_t::BOOL)
            return create_attribute<bool_t>(o,args...);
        else if(tid == type_id_t::STRING)
            return create_attribute<string>(o,args...);
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unknown type code!");
        
    }

//end of namespace
}
}
}
