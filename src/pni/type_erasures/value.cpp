//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpninexus.
//!
//! libpninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Jan 14, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <pni/type_erasures/value.hpp>
#include <pni/types/none.hpp>
#include <pni/type_erasures/value_ref.hpp>


namespace pni{

    //-------------------------------------------------------------------------
    // Implementation of constructors
    //-------------------------------------------------------------------------
    value::value():
        _ptr(new value_holder<none>(none()))
    {}

    //-------------------------------------------------------------------------
    value::value(const value &o)
        :_ptr(o._ptr ? o._ptr->clone() : new value_holder<none>(none())) 
    {}
   
    //------------------------------------------------------------------------
    value::value(value &&o)
        :_ptr(std::move(o._ptr)) 
    {
        o = value();
    }

    //-------------------------------------------------------------------------
    // Implementation of assignment operators
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    value &value::operator=(const value &o)
    {
        if(this == &o) return *this;

        //we have to clone here as we cannot copy a unique pointer
        _ptr = std::unique_ptr<value_holder_interface>(o._ptr->clone());

        return *this;
    }
    
    //-------------------------------------------------------------------------
    value &value::operator=(value &&o)
    {
        if(this == &o) return *this;
        std::swap(_ptr,o._ptr);
        return *this;
    }

    //-------------------------------------------------------------------------
    value &value::operator=(const value_ref &v)
    {
        *this = to_value(v);
        return *this;
    }

    //-------------------------------------------------------------------------
    type_id_t value::type_id() const
    {
        return _ptr->type_id();
    }

    //-------------------------------------------------------------------------
    type_id_t type_id(const value &v)
    {
        return v.type_id();
    }

    //------------------------------------------------------------------------
    value make_value(type_id_t tid)
    {
        switch(tid)
        {
            case type_id_t::UInt8:      return make_value<uint8>();
            case type_id_t::Int8:       return make_value<int8>();
            case type_id_t::UInt16:     return make_value<uint16>();
            case type_id_t::Int16:      return make_value<int16>();
            case type_id_t::UInt32:     return make_value<uint32>();
            case type_id_t::Int32:      return make_value<int32>();
            case type_id_t::UInt64:     return make_value<uint64>();
            case type_id_t::Int64:      return make_value<int64>();
            case type_id_t::Float32:    return make_value<float32>();
            case type_id_t::Float64:    return make_value<float64>();
            case type_id_t::Float128:   return make_value<float128>();
            case type_id_t::Complex32:  return make_value<complex32>();
            case type_id_t::Complex64:  return make_value<complex64>();
            case type_id_t::Complex128: return make_value<complex128>();
            case type_id_t::Binary:     return make_value<binary>();
            case type_id_t::String:     return make_value<string>();
            case type_id_t::Bool:       return make_value<bool_t>();
            default:
                throw type_error(EXCEPTION_RECORD,
                        "Unknown type ID - cannot instantive value!");
        }
    }
//end of namespace
}
