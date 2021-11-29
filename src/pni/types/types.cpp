//!
//! (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//! Created on: Apr 25, 2012
//!     Author: Eugen Wintersberger
//!
//!

#include <pni/types/types.hpp>
namespace pni{

    //! output operator for TypeID
    std::ostream &operator<<(std::ostream &o,const type_id_t &tid)
    {
        if(tid==type_id_t::None) {o<<"NONE"; return o;}
        if(tid==type_id_t::Int8) {o<<"INT8"; return o;}
	    if(tid==type_id_t::UInt8) {o<<"UINT8"; return o;}
		if(tid==type_id_t::Int16) {o<<"INT16"; return o;}
		if(tid==type_id_t::UInt16) {o<<"UINT16"; return o;}
		if(tid==type_id_t::Int32) {o<<"INT32"; return o;}
		if(tid==type_id_t::UInt32) {o<<"UINT32"; return o;}
		if(tid==type_id_t::Int64) {o<<"INT64"; return o;}
		if(tid==type_id_t::UInt64) {o<<"UINT64"; return o;}
	    if(tid==type_id_t::Float32) {o<<"FLOAT32"; return o;}
	    if(tid==type_id_t::Float64) {o<<"FLOAT64"; return o;}
	    if(tid==type_id_t::Float128) {o<<"FLOAT128"; return o;}
	    if(tid==type_id_t::Complex32) {o<<"COMPLEX32"; return o;}
	    if(tid==type_id_t::Complex64) {o<<"COMPLEX64"; return o;}
	    if(tid==type_id_t::Complex128) {o<<"COMPLEX128"; return o;}
	    if(tid==type_id_t::String) {o<<"STRING"; return o;}
	    if(tid==type_id_t::Binary) {o<<"BINARY"; return o;}
	    if(tid==type_id_t::Bool) {o<<"BOOL"; return o;}

        //this is just to make the compiler happy - we should never come here.
        return o; 
    }

    //handle missing comparison operators for class enum types for some
    //compilers.
#ifdef ENUMBUG
    bool operator<(type_id_t a,type_id_t b) { return int(a)<int(b); }

    //-------------------------------------------------------------------------
    bool operator>(type_id_t a,type_id_t b) { return int(a)>int(b); }

    //-------------------------------------------------------------------------
    bool operator<=(type_id_t a,type_id_t b) { return int(a)<=int(b); }

    //-------------------------------------------------------------------------
    bool operator>=(type_id_t a,type_id_t b) { return int(a)>=int(b); }

    //-------------------------------------------------------------------------
    bool operator<(type_class_t a,type_class_t b) { return int(a)<int(b); }

    //-------------------------------------------------------------------------
    bool operator>(type_class_t a,type_class_t b) { return int(a)>int(b); }

    //-------------------------------------------------------------------------
    bool operator<=(type_class_t a,type_class_t b) { return int(a)<=int(b); }

    //-------------------------------------------------------------------------
    bool operator>=(type_class_t a,type_class_t b) { return int(a)>=int(b); }
#endif
//end of namespace 
}
