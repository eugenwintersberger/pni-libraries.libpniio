//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Oct 13, 2011
//     Author: Eugen Wintersberger
//
//
#pragma once

#include <pni/types/types.hpp>

namespace pni{
namespace core{

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
    CREATE_ID_TYPE_MAP(type_id_t::UINT8,uint8);
    CREATE_ID_TYPE_MAP(type_id_t::INT8,int8);
    CREATE_ID_TYPE_MAP(type_id_t::UINT16,uint16);
    CREATE_ID_TYPE_MAP(type_id_t::INT16,int16);
    CREATE_ID_TYPE_MAP(type_id_t::UINT32,uint32);
    CREATE_ID_TYPE_MAP(type_id_t::INT32,int32);
    CREATE_ID_TYPE_MAP(type_id_t::UINT64,uint64);
    CREATE_ID_TYPE_MAP(type_id_t::INT64,int64);
    CREATE_ID_TYPE_MAP(type_id_t::FLOAT32,float32);
    CREATE_ID_TYPE_MAP(type_id_t::FLOAT64,float64);
    CREATE_ID_TYPE_MAP(type_id_t::FLOAT128,float128);
    CREATE_ID_TYPE_MAP(type_id_t::COMPLEX32,complex32);
    CREATE_ID_TYPE_MAP(type_id_t::COMPLEX64,complex64);
    CREATE_ID_TYPE_MAP(type_id_t::COMPLEX128,complex128);
    CREATE_ID_TYPE_MAP(type_id_t::STRING,string);
    CREATE_ID_TYPE_MAP(type_id_t::BINARY,binary);
    CREATE_ID_TYPE_MAP(type_id_t::BOOL,bool_t);
    CREATE_ID_TYPE_MAP(type_id_t::NONE,none);
    //! \endcond NO_API_DOC

}
}
