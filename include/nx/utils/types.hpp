/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Utilty functions and function templates concerning NXField objects.
 *
 * Created on: Jul 9, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <map>

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;

    /*!
    \ingroup nexus_utilities
    \brief map from strings to type ids

    This type can be used as a map from the string representation of a Nexus
    type to its type id. 
    */
    typedef std::map<string,type_id_t> str2typeid_t;

    /*!
    \ingroup nexus_utilities
    \brief map from type ids to strings

    A map type from type ids to the string representations of the type. 
    */
    typedef std::map<type_id_t,string> typeid2str_t;

    static str2typeid_t str2typeid = {
        {"uint8",type_id_t::UINT8},
        {"int8",type_id_t::INT8},
        {"uint16",type_id_t::UINT16},
        {"int16",type_id_t::INT16},
        {"uint32",type_id_t::UINT32},
        {"int32",type_id_t::INT32},
        {"uint64",type_id_t::UINT64},
        {"int64",type_id_t::INT64},
        {"float32",type_id_t::FLOAT32},
        {"float64",type_id_t::FLOAT64},
        {"float128",type_id_t::FLOAT128},
        {"complex32",type_id_t::COMPLEX32},
        {"complex64",type_id_t::COMPLEX64},
        {"complex128",type_id_t::COMPLEX128},
        {"binary",type_id_t::BINARY},
        {"string",type_id_t::STRING},
        {"str",type_id_t::STRING},
        {"bool",type_id_t::BOOL}
    };

    static typeid2str_t typeid2str = {
        {type_id_t::UINT8,"uint8"},
        {type_id_t::INT8,"int8"},
        {type_id_t::UINT16,"uint16"},
        {type_id_t::INT16,"int16"},
        {type_id_t::UINT32,"uint32"},
        {type_id_t::INT32,"int32"},
        {type_id_t::UINT64,"uint64"},
        {type_id_t::INT64,"int64"},
        {type_id_t::FLOAT32,"float32"},
        {type_id_t::FLOAT64,"float64"},
        {type_id_t::FLOAT128,"float128"},
        {type_id_t::COMPLEX32,"complex32"},
        {type_id_t::COMPLEX64,"complex64"},
        {type_id_t::COMPLEX128,"complex128"},
        {type_id_t::BINARY,"binary"},
        {type_id_t::STRING,"string"},
        {type_id_t::BOOL,"bool"}
    };
    


//end of namespace 
}
}
}
