//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Sep 27, 2012
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types/types.hpp>

namespace pni{
   
//!
//! \ingroup type_classes_internal
//! \brief macro for type/class map creation
//! 
//! This macro creates a type to type class map specialization. 
//!
#define CREATE_TYPE_CLASS_MAP(type,tclass)\
    template<> struct type_class_map<type>\
    {\
        static const type_class_t type_class = tclass;\
    }
    
    //!
    //! \ingroup type_classes
    //! \brief type to class mapping
    //!  
    //! Template mapping a particular data type to its type class.
    //! \tparam T data type
    //!
    template<typename T> 
    struct type_class_map
    {
        //! class of type T
        static const type_class_t type_class = type_class_t::None;
    };

    //! \cond NO_API_DOC
    CREATE_TYPE_CLASS_MAP(uint8,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(int8,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(uint16,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(int16,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(uint32,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(int32,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(uint64,type_class_t::Integer);
    CREATE_TYPE_CLASS_MAP(int64,type_class_t::Integer);
    
    CREATE_TYPE_CLASS_MAP(float32,type_class_t::Float);
    CREATE_TYPE_CLASS_MAP(float64,type_class_t::Float);
    CREATE_TYPE_CLASS_MAP(float128,type_class_t::Float);

    CREATE_TYPE_CLASS_MAP(complex32,type_class_t::Complex);
    CREATE_TYPE_CLASS_MAP(complex64,type_class_t::Complex);
    CREATE_TYPE_CLASS_MAP(complex128,type_class_t::Complex);

    CREATE_TYPE_CLASS_MAP(bool_t,type_class_t::Bool);
    CREATE_TYPE_CLASS_MAP(binary,type_class_t::Binary);
    CREATE_TYPE_CLASS_MAP(string,type_class_t::String);

    CREATE_TYPE_CLASS_MAP(none,type_class_t::None);

    //! \endcond NO_API_DOC

//end of namespace
}
