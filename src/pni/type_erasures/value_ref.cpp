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

#include <pni/type_erasures/value_ref.hpp>
#include <pni/type_erasures/value.hpp>

namespace pni{

    //-------------------------------------------------------------------------
    // Implementation of private member functions
    //-------------------------------------------------------------------------
    void value_ref::_check_pointer(const exception_record &r) const
    {
        if(!_ptr)
            throw memory_not_allocated_error(r,
                    "Instance of value_ref holds no data!");
    }

    //------------------------------------------------------------------------
    void value_ref::_check_type(type_id_t tid,const exception_record &r) const
    {
        if(type_id() != tid)
            throw type_error(r,"incompatible type - cannot return value");
    }

    //-------------------------------------------------------------------------
    // Implementation of constructors
    //-------------------------------------------------------------------------
    value_ref::value_ref():_ptr(nullptr)
    {}

    //-------------------------------------------------------------------------
    value_ref::value_ref(const value_ref &o)
        :_ptr(nullptr)
    {
        if(o._ptr) _ptr = pointer_type(o._ptr->clone());
    }

    //-------------------------------------------------------------------------
    // Implementation of assignment operators
    //-------------------------------------------------------------------------
    value_ref &value_ref::operator=(const value_ref &o)
    {
        if(this == &o) return *this;
        _ptr = pointer_type(o._ptr->clone());

        return *this;
    }
    

    //-------------------------------------------------------------------------
    value_ref &value_ref::operator=(const value &v)
    {
        _check_pointer(EXCEPTION_RECORD);

        type_id_t tid = type_id(); //obtain the type id of the value_ref

        switch(tid)
        {
            case type_id_t::UINT8:      *this = v.as<uint8>();      break;
            case type_id_t::INT8:       *this = v.as<int8>();       break;
            case type_id_t::UINT16:     *this = v.as<uint16>();     break;
            case type_id_t::INT16:      *this = v.as<int16>();      break;
            case type_id_t::UINT32:     *this = v.as<uint32>();     break;
            case type_id_t::INT32:      *this = v.as<int32>();      break;
            case type_id_t::UINT64:     *this = v.as<uint64>();     break;
            case type_id_t::INT64:      *this = v.as<int64>();      break; 
            case type_id_t::FLOAT32:    *this = v.as<float32>();    break;
            case type_id_t::FLOAT64:    *this = v.as<float64>();    break;
            case type_id_t::FLOAT128:   *this = v.as<float128>();   break;
            case type_id_t::COMPLEX32:  *this = v.as<complex32>();  break;
            case type_id_t::COMPLEX64:  *this = v.as<complex64>();  break;
            case type_id_t::COMPLEX128: *this = v.as<complex128>(); break;
            case type_id_t::STRING:     *this = v.as<string>();     break;
            case type_id_t::BOOL:       *this = v.as<bool_t>();     break;
            case type_id_t::BINARY:     *this = v.as<binary>();     break;
            default:
                throw type_error(EXCEPTION_RECORD, "Unkown type!");
        }

        return *this;
    }

    //-------------------------------------------------------------------------
    value_ref::operator value() const
    {
        return to_value(*this);
    }

    //-------------------------------------------------------------------------
    // Implementation of member functions
    //-------------------------------------------------------------------------
    type_id_t value_ref::type_id() const
    {
        _check_pointer(EXCEPTION_RECORD);
        return _ptr->type_id();

    }

    //------------------------------------------------------------------------
    value to_value(const value_ref &v)
    {
        type_id_t tid = v.type_id();

        switch(tid)
        {
            case type_id_t::UINT8:      return value(v.as<uint8>());
            case type_id_t::INT8:       return value(v.as<int8>());
            case type_id_t::UINT16:     return value(v.as<uint16>());
            case type_id_t::INT16:      return value(v.as<int16>()); 
            case type_id_t::UINT32:     return value(v.as<uint32>());
            case type_id_t::INT32:      return value(v.as<int32>());
            case type_id_t::UINT64:     return value(v.as<uint64>());
            case type_id_t::INT64:      return value(v.as<int64>());
            case type_id_t::FLOAT32:    return value(v.as<float32>());
            case type_id_t::FLOAT64:    return value(v.as<float64>());
            case type_id_t::FLOAT128:   return value(v.as<float128>());
            case type_id_t::COMPLEX32:  return value(v.as<complex32>());
            case type_id_t::COMPLEX64:  return value(v.as<complex64>());
            case type_id_t::COMPLEX128: return value(v.as<complex128>());
            case type_id_t::STRING:     return value(v.as<string>());
            case type_id_t::BOOL:       return value(v.as<bool_t>());
            default: 
                throw type_error(EXCEPTION_RECORD,
                                 "Value is of unkown type!");
        }

    }

//end of namespace
}
