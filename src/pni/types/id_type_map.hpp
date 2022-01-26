//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Oct 13, 2011
//     Author: Eugen Wintersberger
//
//
#pragma once

#include <pni/types/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni{

//!
//! \ingroup type_classes_internal
//! \brief macro for ID to type map specialization
//! 
//! This macro is used to create a specialization of IDTypeMap.
//!
#define CREATE_ID_TYPE_MAP(tid,dtype)\
    template<> struct id_type_map<tid>\
    {\
        typedef dtype type;\
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief map from type_id_t to type
    //!
    //! This template implements a map from a type_id_t to a specific data 
    //! type. The type map can be used in a template to determine the type of a 
    //! variable by the ID rather than by its type:
    /*!
    \code
    id_type_map<ID>::type variable;
    \endcode
    !*/ 
    //! \tparam id value of the type id
    //!
    template<type_id_t id> 
    struct id_type_map
    {
        //! type identified by the template parameter
        typedef uint8 type; 
    };

    //! \cond NO_API_DOC
    CREATE_ID_TYPE_MAP(type_id_t::UInt8,uint8);
    CREATE_ID_TYPE_MAP(type_id_t::Int8,int8);
    CREATE_ID_TYPE_MAP(type_id_t::UInt16,uint16);
    CREATE_ID_TYPE_MAP(type_id_t::Int16,int16);
    CREATE_ID_TYPE_MAP(type_id_t::UInt32,uint32);
    CREATE_ID_TYPE_MAP(type_id_t::Int32,int32);
    CREATE_ID_TYPE_MAP(type_id_t::UInt64,uint64);
    CREATE_ID_TYPE_MAP(type_id_t::Int64,int64);
    CREATE_ID_TYPE_MAP(type_id_t::Float32,float32);
    CREATE_ID_TYPE_MAP(type_id_t::Float64,float64);
    CREATE_ID_TYPE_MAP(type_id_t::Float128,float128);
    CREATE_ID_TYPE_MAP(type_id_t::Complex32,complex32);
    CREATE_ID_TYPE_MAP(type_id_t::Complex64,complex64);
    CREATE_ID_TYPE_MAP(type_id_t::Complex128,complex128);
    CREATE_ID_TYPE_MAP(type_id_t::String,string);
    CREATE_ID_TYPE_MAP(type_id_t::Binary,binary);
    CREATE_ID_TYPE_MAP(type_id_t::Bool,bool_t);
    CREATE_ID_TYPE_MAP(type_id_t::EBool,hdf5::datatype::EBool);
    CREATE_ID_TYPE_MAP(type_id_t::None,none);
    //! \endcond NO_API_DOC

}
