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
//  Created on: Dec 13, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types/types.hpp>

namespace pni{
namespace core{

//!
//! \ingroup type_classes_internal
//! \brief macro to create type to type id maps
//!
//! This macro is used to create a specialization of the type_id_map type map.
//!
#define CREATE_TYPE_ID_MAP(type,tid)\
    template<> struct type_id_map<type>\
    {\
        static constexpr type_id_t type_id = tid;\
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief map from a type to type_id
    //! 
    //! This template implements a map from a concrete type to its type_id
    //!
    template<typename T> 
    struct type_id_map
    {
        //! id value for type T
        static constexpr type_id_t type_id = type_id_t::NONE; 
    };

    //! \cond NO_API_DOC
    CREATE_TYPE_ID_MAP(uint8,type_id_t::UINT8);
    CREATE_TYPE_ID_MAP(int8,type_id_t::INT8);
    CREATE_TYPE_ID_MAP(uint16,type_id_t::UINT16);
    CREATE_TYPE_ID_MAP(int16,type_id_t::INT16);
    CREATE_TYPE_ID_MAP(uint32,type_id_t::UINT32);
    CREATE_TYPE_ID_MAP(int32,type_id_t::INT32);
    CREATE_TYPE_ID_MAP(uint64,type_id_t::UINT64);
    CREATE_TYPE_ID_MAP(int64,type_id_t::INT64);
    CREATE_TYPE_ID_MAP(float32,type_id_t::FLOAT32);
    CREATE_TYPE_ID_MAP(float64,type_id_t::FLOAT64);
    CREATE_TYPE_ID_MAP(float128,type_id_t::FLOAT128);
    CREATE_TYPE_ID_MAP(complex32,type_id_t::COMPLEX32);
    CREATE_TYPE_ID_MAP(complex64,type_id_t::COMPLEX64);
    CREATE_TYPE_ID_MAP(complex128,type_id_t::COMPLEX128);
    CREATE_TYPE_ID_MAP(string,type_id_t::STRING);
    CREATE_TYPE_ID_MAP(binary,type_id_t::BINARY);
    CREATE_TYPE_ID_MAP(bool_t,type_id_t::BOOL);
    CREATE_TYPE_ID_MAP(bool,type_id_t::BOOL);
    CREATE_TYPE_ID_MAP(none,type_id_t::NONE);
    //! \endcond NO_API_DOC

//end of namespace
}
}
