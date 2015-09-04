//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Sep 04, 2015
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/xml/group.hpp>
#include <vector>

typedef std::vector<pni::core::uint8> uint8_vector; 
typedef std::vector<pni::core::int8> int8_vector; 
typedef std::vector<pni::core::uint16> uint16_vector; 
typedef std::vector<pni::core::int16> int16_vector; 
typedef std::vector<pni::core::uint32> uint32_vector; 
typedef std::vector<pni::core::int32> int32_vector; 
typedef std::vector<pni::core::uint64> uint64_vector; 
typedef std::vector<pni::core::int64> int64_vector; 

typedef std::vector<pni::core::float32> float32_vector;
typedef std::vector<pni::core::float64> float64_vector;
typedef std::vector<pni::core::float128> float128_vector;

typedef std::vector<pni::core::complex32> complex32_vector;
typedef std::vector<pni::core::complex64> complex64_vector;
typedef std::vector<pni::core::complex128> complex128_vector;

typedef std::vector<pni::core::string> string_vector;
typedef std::vector<pni::core::bool_t> bool_t_vector;


namespace xml_test{
namespace attr{

    size_t size(const pni::io::nx::xml::node &node);

    size_t rank(const pni::io::nx::xml::node &node);

    pni::core::type_id_t type_id(const pni::io::nx::xml::node &node);

#define DECLARE_DATA_FROM_XML(type)\
    void data_from_xml(const pni::io::nx::xml::node &node, \
                       type &value)

    DECLARE_DATA_FROM_XML(pni::core::uint8);
    DECLARE_DATA_FROM_XML(pni::core::int8);
    DECLARE_DATA_FROM_XML(pni::core::uint16);
    DECLARE_DATA_FROM_XML(pni::core::int16);
    DECLARE_DATA_FROM_XML(pni::core::uint32);
    DECLARE_DATA_FROM_XML(pni::core::int32);
    DECLARE_DATA_FROM_XML(pni::core::uint64);
    DECLARE_DATA_FROM_XML(pni::core::int64);

    DECLARE_DATA_FROM_XML(pni::core::float32);
    DECLARE_DATA_FROM_XML(pni::core::float64);
    DECLARE_DATA_FROM_XML(pni::core::float128);
    
    DECLARE_DATA_FROM_XML(pni::core::complex32);
    DECLARE_DATA_FROM_XML(pni::core::complex64);
    DECLARE_DATA_FROM_XML(pni::core::complex128);

    DECLARE_DATA_FROM_XML(pni::core::string);
    DECLARE_DATA_FROM_XML(pni::core::bool_t);
    
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

#define DECLARE_DATA_TO_XML(type)\
    void data_to_xml(const type &value,pni::io::nx::xml::node &node)

    DECLARE_DATA_TO_XML(pni::core::uint8);
    DECLARE_DATA_TO_XML(pni::core::int8);
    DECLARE_DATA_TO_XML(pni::core::uint16);
    DECLARE_DATA_TO_XML(pni::core::int16);
    DECLARE_DATA_TO_XML(pni::core::uint32);
    DECLARE_DATA_TO_XML(pni::core::int32);
    DECLARE_DATA_TO_XML(pni::core::uint64);
    DECLARE_DATA_TO_XML(pni::core::int64);

    DECLARE_DATA_TO_XML(pni::core::float32);
    DECLARE_DATA_TO_XML(pni::core::float64);
    DECLARE_DATA_TO_XML(pni::core::float128);
    
    DECLARE_DATA_TO_XML(pni::core::complex32);
    DECLARE_DATA_TO_XML(pni::core::complex64);
    DECLARE_DATA_TO_XML(pni::core::complex128);

    DECLARE_DATA_TO_XML(pni::core::string);
    DECLARE_DATA_TO_XML(pni::core::bool_t);
    
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

    pni::io::nx::xml::node 
    object_to_xml(const pni::io::nx::h5::nxobject &object);

    pni::io::nx::h5::nxobject 
    object_from_xml(const pni::io::nx::h5::nxobject &parent,
                    const pni::io::nx::xml::node &node);

}
}
