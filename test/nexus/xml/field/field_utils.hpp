//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: Sep 04, 2015
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/nexus/xml/node.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <pni/types.hpp>
#include <vector>

using uint8_vector  = std::vector<pni::uint8>;
using int8_vector   = std::vector<pni::int8>;
using uint16_vector = std::vector<pni::uint16>;
using int16_vector  = std::vector<pni::int16>;
using uint32_vector = std::vector<pni::uint32>;
using int32_vector  = std::vector<pni::int32>;
using uint64_vector = std::vector<pni::uint64>;
using int64_vector  = std::vector<pni::int64>;

using float32_vector  = std::vector<pni::float32>;
using float64_vector  = std::vector<pni::float64>;
using float128_vector = std::vector<pni::float128>;

using complex32_vector   = std::vector<pni::complex32>;
using complex64_vector   = std::vector<pni::complex64>;
using complex128_vector = std::vector<pni::complex128>;

using string_vector = std::vector<pni::string>;
using bool_t_vector = std::vector<pni::bool_t>;
using ebool_vector = std::vector<hdf5::datatype::EBool>;

namespace xml_test{
namespace field_test{

    size_t size(const pni::nexus::xml::Node &node);

    size_t rank(const pni::nexus::xml::Node &node);

    pni::type_id_t type_id(const pni::nexus::xml::Node &node);

#define DECLARE_DATA_FROM_XML(type)\
    void data_from_xml(const pni::nexus::xml::Node &node, \
                       type &value)

    DECLARE_DATA_FROM_XML(pni::uint8);
    DECLARE_DATA_FROM_XML(pni::int8);
    DECLARE_DATA_FROM_XML(pni::uint16);
    DECLARE_DATA_FROM_XML(pni::int16);
    DECLARE_DATA_FROM_XML(pni::uint32);
    DECLARE_DATA_FROM_XML(pni::int32);
    DECLARE_DATA_FROM_XML(pni::uint64);
    DECLARE_DATA_FROM_XML(pni::int64);

    DECLARE_DATA_FROM_XML(pni::float32);
    DECLARE_DATA_FROM_XML(pni::float64);
    DECLARE_DATA_FROM_XML(pni::float128);
    
    DECLARE_DATA_FROM_XML(pni::complex32);
    DECLARE_DATA_FROM_XML(pni::complex64);
    DECLARE_DATA_FROM_XML(pni::complex128);

    DECLARE_DATA_FROM_XML(pni::string);
    DECLARE_DATA_FROM_XML(pni::bool_t);
  DECLARE_DATA_FROM_XML(hdf5::datatype::EBool);
    
    DECLARE_DATA_FROM_XML(uint8_vector);
    DECLARE_DATA_FROM_XML(int8_vector);
    DECLARE_DATA_FROM_XML(uint16_vector);
    DECLARE_DATA_FROM_XML(int16_vector);
    DECLARE_DATA_FROM_XML(uint32_vector);
    DECLARE_DATA_FROM_XML(int32_vector);
    DECLARE_DATA_FROM_XML(uint64_vector);
    DECLARE_DATA_FROM_XML(int64_vector);

    DECLARE_DATA_FROM_XML(float32_vector);
    DECLARE_DATA_FROM_XML(float64_vector);
    DECLARE_DATA_FROM_XML(float128_vector);
    
    DECLARE_DATA_FROM_XML(complex32_vector);
    DECLARE_DATA_FROM_XML(complex64_vector);
    DECLARE_DATA_FROM_XML(complex128_vector);

    DECLARE_DATA_FROM_XML(string_vector);
    DECLARE_DATA_FROM_XML(bool_t_vector);
    DECLARE_DATA_FROM_XML(ebool_vector);

#define DECLARE_DATA_TO_XML(type)\
    void data_to_xml(const type &value,pni::nexus::xml::Node &node)

    DECLARE_DATA_TO_XML(pni::uint8);
    DECLARE_DATA_TO_XML(pni::int8);
    DECLARE_DATA_TO_XML(pni::uint16);
    DECLARE_DATA_TO_XML(pni::int16);
    DECLARE_DATA_TO_XML(pni::uint32);
    DECLARE_DATA_TO_XML(pni::int32);
    DECLARE_DATA_TO_XML(pni::uint64);
    DECLARE_DATA_TO_XML(pni::int64);

    DECLARE_DATA_TO_XML(pni::float32);
    DECLARE_DATA_TO_XML(pni::float64);
    DECLARE_DATA_TO_XML(pni::float128);
    
    DECLARE_DATA_TO_XML(pni::complex32);
    DECLARE_DATA_TO_XML(pni::complex64);
    DECLARE_DATA_TO_XML(pni::complex128);

    DECLARE_DATA_TO_XML(pni::string);
    DECLARE_DATA_TO_XML(pni::bool_t);
    DECLARE_DATA_TO_XML(hdf5::datatype::EBool);
    
    DECLARE_DATA_TO_XML(uint8_vector);
    DECLARE_DATA_TO_XML(int8_vector);
    DECLARE_DATA_TO_XML(uint16_vector);
    DECLARE_DATA_TO_XML(int16_vector);
    DECLARE_DATA_TO_XML(uint32_vector);
    DECLARE_DATA_TO_XML(int32_vector);
    DECLARE_DATA_TO_XML(uint64_vector);
    DECLARE_DATA_TO_XML(int64_vector);

    DECLARE_DATA_TO_XML(float32_vector);
    DECLARE_DATA_TO_XML(float64_vector);
    DECLARE_DATA_TO_XML(float128_vector);
    
    DECLARE_DATA_TO_XML(complex32_vector);
    DECLARE_DATA_TO_XML(complex64_vector);
    DECLARE_DATA_TO_XML(complex128_vector);

    DECLARE_DATA_TO_XML(string_vector);
    DECLARE_DATA_TO_XML(bool_t_vector);
    DECLARE_DATA_TO_XML(ebool_vector);

    pni::nexus::xml::Node
    object_to_xml(const hdf5::node::Node &object);

    hdf5::node::Node
    object_from_xml(const hdf5::node::Node &parent,
                    const pni::nexus::xml::Node &node);

}
}
