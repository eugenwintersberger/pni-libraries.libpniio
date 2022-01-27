//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 30, 2013
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
//
//

#include <sstream>
#include <stdexcept>
#include <pni/error/exceptions.hpp>
#include <pni/types/type_utils.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>


namespace pni{
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief string to id map
    
    A map instance mapping the string representations of types to type IDs.
    */
    static const std::map<string,type_id_t> str2type_id =
    {{"uint8",type_id_t::UInt8},{"ui8",type_id_t::UInt8},
     {"int8",type_id_t::Int8},{"i8",type_id_t::Int8},
     {"uint16",type_id_t::UInt16},{"ui16",type_id_t::UInt16},
     {"int16",type_id_t::Int16},{"i16",type_id_t::Int16},
     {"uint32",type_id_t::UInt32},{"ui32",type_id_t::UInt32},
     {"int32",type_id_t::Int32},{"i32",type_id_t::Int32},
     {"uint64",type_id_t::UInt64},{"ui64",type_id_t::UInt64},
     {"int64",type_id_t::Int64},{"i64",type_id_t::Int64},
     {"float32",type_id_t::Float32},{"f32",type_id_t::Float32},
     {"float64",type_id_t::Float64},{"f64",type_id_t::Float64},
     {"float128",type_id_t::Float128},{"f128",type_id_t::Float128},
     {"complex32",type_id_t::Complex32},{"c32",type_id_t::Complex32},
     {"complex64",type_id_t::Complex64},{"c64",type_id_t::Complex64},
     {"complex128",type_id_t::Complex128},{"c128",type_id_t::Complex128},
     {"string",type_id_t::String},{"str",type_id_t::String},
     {"binary",type_id_t::Binary}, {"bool",type_id_t::EBool},
     {"ibool",type_id_t::Bool},
     {"ebool",type_id_t::EBool},
     {"none",type_id_t::None}
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief type ID to string map

    This map provides mapping from type_id to the string representations of a
    type.
    */
    static const std::map<type_id_t,string> type_id2str =
    {{type_id_t::UInt8,"uint8"},   {type_id_t::Int8,"int8"},
     {type_id_t::UInt16,"uint16"}, {type_id_t::Int16,"int16"},
     {type_id_t::UInt32,"uint32"}, {type_id_t::Int32,"int32"},
     {type_id_t::UInt64,"uint64"}, {type_id_t::Int64,"int64"},
     {type_id_t::Float32,"float32"},
     {type_id_t::Float64,"float64"},
     {type_id_t::Float128,"float128"},
     {type_id_t::Complex32,"complex32"},
     {type_id_t::Complex64,"complex64"},
     {type_id_t::Complex128,"complex128"},
     {type_id_t::String,"string"},
     {type_id_t::Binary,"binary"},
     {type_id_t::Bool,"ibool"},
     {type_id_t::EBool,"bool"},
     // {type_id_t::EBool,"ebool"},
     {type_id_t::None,"none"}
    };

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const binary &)
    {
        return type_id_t::Binary;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const bool_t &)
    {
        return type_id_t::Bool;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const hdf5::datatype::EBool &)
    {
        return type_id_t::EBool;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const string &)
    {
        return type_id_t::String;
    }

    //-------------------------------------------------------------------------
    type_id_t type_id_from_str(const string &s)
    {
        try
        {
            return str2type_id.at(s);
        }
        catch(std::out_of_range &)
        {
            string msg = "String ["+s+"] does not represent a type!";
            throw key_error(EXCEPTION_RECORD,s);
        }
    }

    //-------------------------------------------------------------------------
    string str_from_type_id(type_id_t id)
    {
        try
        {
            return type_id2str.at(id);
        }
        catch(std::out_of_range &)
        {
            std::stringstream ss;
            ss<<"Type id ["<<id<<"] does not have a string representation!";
            throw key_error(EXCEPTION_RECORD,ss.str());
        }
    }

//end of namespace
}

