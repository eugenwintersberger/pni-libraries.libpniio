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
//  Created on: Dec 13, 2011
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/types/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni{

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
    template<typename ElementT> 
    struct type_id_map
    {
        //! id value for type ElementT
        static constexpr type_id_t type_id = type_id_t::None; 
    };

    //! \cond NO_API_DOC
    CREATE_TYPE_ID_MAP(uint8,type_id_t::UInt8);
    CREATE_TYPE_ID_MAP(int8,type_id_t::Int8);
    CREATE_TYPE_ID_MAP(uint16,type_id_t::UInt16);
    CREATE_TYPE_ID_MAP(int16,type_id_t::Int16);
    CREATE_TYPE_ID_MAP(uint32,type_id_t::UInt32);
    CREATE_TYPE_ID_MAP(int32,type_id_t::Int32);
    CREATE_TYPE_ID_MAP(uint64,type_id_t::UInt64);
    CREATE_TYPE_ID_MAP(int64,type_id_t::Int64);
    CREATE_TYPE_ID_MAP(float32,type_id_t::Float32);
    CREATE_TYPE_ID_MAP(float64,type_id_t::Float64);
    CREATE_TYPE_ID_MAP(float128,type_id_t::Float128);
    CREATE_TYPE_ID_MAP(complex32,type_id_t::Complex32);
    CREATE_TYPE_ID_MAP(complex64,type_id_t::Complex64);
    CREATE_TYPE_ID_MAP(complex128,type_id_t::Complex128);
    CREATE_TYPE_ID_MAP(string,type_id_t::String);
    CREATE_TYPE_ID_MAP(binary,type_id_t::Binary);
    CREATE_TYPE_ID_MAP(bool_t,type_id_t::Bool);
    CREATE_TYPE_ID_MAP(bool,type_id_t::Bool);
    CREATE_TYPE_ID_MAP(hdf5::datatype::EBool,type_id_t::EBool);
    CREATE_TYPE_ID_MAP(none,type_id_t::None);
    //! \endcond NO_API_DOC

//end of namespace
}
