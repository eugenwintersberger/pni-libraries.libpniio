//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 30, 2013
//     Author: Eugen Wintersberger
//
//

#include <sstream>
#include <stdexcept>
#include <pni/error/exceptions.hpp>
#include <pni/types/type_utils.hpp>


namespace pni{
namespace core{
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief string to id map
    
    A map instance mapping the string representations of types to type IDs.
    */
    static const std::map<string,type_id_t> str2type_id =
    {{"uint8",type_id_t::UINT8},{"ui8",type_id_t::UINT8},
     {"int8",type_id_t::INT8},{"i8",type_id_t::INT8},
     {"uint16",type_id_t::UINT16},{"ui16",type_id_t::UINT16},
     {"int16",type_id_t::INT16},{"i16",type_id_t::INT16},
     {"uint32",type_id_t::UINT32},{"ui32",type_id_t::UINT32},
     {"int32",type_id_t::INT32},{"i32",type_id_t::INT32},
     {"uint64",type_id_t::UINT64},{"ui64",type_id_t::UINT64},
     {"int64",type_id_t::INT64},{"i64",type_id_t::INT64},
     {"float32",type_id_t::FLOAT32},{"f32",type_id_t::FLOAT32},
     {"float64",type_id_t::FLOAT64},{"f64",type_id_t::FLOAT64},
     {"float128",type_id_t::FLOAT128},{"f128",type_id_t::FLOAT128},
     {"complex32",type_id_t::COMPLEX32},{"c32",type_id_t::COMPLEX32},
     {"complex64",type_id_t::COMPLEX64},{"c64",type_id_t::COMPLEX64},
     {"complex128",type_id_t::COMPLEX128},{"c128",type_id_t::COMPLEX128},
     {"string",type_id_t::STRING},{"str",type_id_t::STRING},
     {"binary",type_id_t::BINARY}, {"bool",type_id_t::BOOL},
     {"none",type_id_t::NONE}
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief type ID to string map

    This map provides mapping from type_id to the string representations of a
    type.
    */
    static const std::map<type_id_t,string> type_id2str =
    {{type_id_t::UINT8,"uint8"},   {type_id_t::INT8,"int8"},
     {type_id_t::UINT16,"uint16"}, {type_id_t::INT16,"int16"},
     {type_id_t::UINT32,"uint32"}, {type_id_t::INT32,"int32"},
     {type_id_t::UINT64,"uint64"}, {type_id_t::INT64,"int64"},
     {type_id_t::FLOAT32,"float32"},
     {type_id_t::FLOAT64,"float64"},
     {type_id_t::FLOAT128,"float128"},
     {type_id_t::COMPLEX32,"complex32"},
     {type_id_t::COMPLEX64,"complex64"},
     {type_id_t::COMPLEX128,"complex128"},
     {type_id_t::STRING,"string"},
     {type_id_t::BINARY,"binary"},
     {type_id_t::BOOL,"bool"},
     {type_id_t::NONE,"none"}
    };

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const binary &)
    {
        return type_id_t::BINARY;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const bool_t &)
    {
        return type_id_t::BOOL;
    }

    //-------------------------------------------------------------------------
    type_id_t get_type_id(const string &)
    {
        return type_id_t::STRING;
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
}

