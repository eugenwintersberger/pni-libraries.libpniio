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

#include <pni/io/nx/xml/field.hpp>
#include "field_utils.hpp"


namespace xml_test{
namespace field_test{

    size_t size(const pni::io::nx::xml::node &node)
    {
        return pni::io::nx::xml::field::size(node);
    }

    size_t rank(const pni::io::nx::xml::node &node)
    {
        return pni::io::nx::xml::field::rank(node);
    }

    pni::core::type_id_t type_id(const pni::io::nx::xml::node &node)
    {
        return pni::io::nx::xml::field::type_id(node);
    }

#define DEF_DATA_FROM_XML(type) \
    void data_from_xml(const pni::io::nx::xml::node &node, \
                       type &value) \
    { \
        using namespace pni::io::nx::xml; \
        value = field::data_from_xml<type>(node); \
    }

    DEF_DATA_FROM_XML(pni::core::uint8)
    DEF_DATA_FROM_XML(pni::core::int8)
    DEF_DATA_FROM_XML(pni::core::uint16)
    DEF_DATA_FROM_XML(pni::core::int16)
    DEF_DATA_FROM_XML(pni::core::uint32)
    DEF_DATA_FROM_XML(pni::core::int32)
    DEF_DATA_FROM_XML(pni::core::uint64)
    DEF_DATA_FROM_XML(pni::core::int64)

    DEF_DATA_FROM_XML(pni::core::float32)
    DEF_DATA_FROM_XML(pni::core::float64)
    DEF_DATA_FROM_XML(pni::core::float128)
    
    DEF_DATA_FROM_XML(pni::core::complex32)
    DEF_DATA_FROM_XML(pni::core::complex64)
    DEF_DATA_FROM_XML(pni::core::complex128)

    DEF_DATA_FROM_XML(pni::core::string)
    DEF_DATA_FROM_XML(pni::core::bool_t)
    
    DEF_DATA_FROM_XML(uint8_vector)
    DEF_DATA_FROM_XML(int8_vector)
    DEF_DATA_FROM_XML(uint16_vector)
    DEF_DATA_FROM_XML(int16_vector)
    DEF_DATA_FROM_XML(uint32_vector)
    DEF_DATA_FROM_XML(int32_vector)
    DEF_DATA_FROM_XML(uint64_vector)
    DEF_DATA_FROM_XML(int64_vector)

    DEF_DATA_FROM_XML(float32_vector)
    DEF_DATA_FROM_XML(float64_vector)
    DEF_DATA_FROM_XML(float128_vector)
    
    DEF_DATA_FROM_XML(complex32_vector)
    DEF_DATA_FROM_XML(complex64_vector)
    DEF_DATA_FROM_XML(complex128_vector)

    DEF_DATA_FROM_XML(string_vector)
    DEF_DATA_FROM_XML(bool_t_vector)

#define DEF_DATA_TO_XML(type) \
    void data_to_xml(const type &value,pni::io::nx::xml::node &node) \
    { \
        using namespace pni::io::nx::xml; \
        field::data_to_xml(node,value); \
    }
    
    DEF_DATA_TO_XML(pni::core::uint8)
    DEF_DATA_TO_XML(pni::core::int8)
    DEF_DATA_TO_XML(pni::core::uint16)
    DEF_DATA_TO_XML(pni::core::int16)
    DEF_DATA_TO_XML(pni::core::uint32)
    DEF_DATA_TO_XML(pni::core::int32)
    DEF_DATA_TO_XML(pni::core::uint64)
    DEF_DATA_TO_XML(pni::core::int64)

    DEF_DATA_TO_XML(pni::core::float32)
    DEF_DATA_TO_XML(pni::core::float64)
    DEF_DATA_TO_XML(pni::core::float128)
    
    DEF_DATA_TO_XML(pni::core::complex32)
    DEF_DATA_TO_XML(pni::core::complex64)
    DEF_DATA_TO_XML(pni::core::complex128)

    DEF_DATA_TO_XML(pni::core::string)
    DEF_DATA_TO_XML(pni::core::bool_t)
    
    DEF_DATA_TO_XML(uint8_vector)
    DEF_DATA_TO_XML(int8_vector)
    DEF_DATA_TO_XML(uint16_vector)
    DEF_DATA_TO_XML(int16_vector)
    DEF_DATA_TO_XML(uint32_vector)
    DEF_DATA_TO_XML(int32_vector)
    DEF_DATA_TO_XML(uint64_vector)
    DEF_DATA_TO_XML(int64_vector)

    DEF_DATA_TO_XML(float32_vector)
    DEF_DATA_TO_XML(float64_vector)
    DEF_DATA_TO_XML(float128_vector)
    
    DEF_DATA_TO_XML(complex32_vector)
    DEF_DATA_TO_XML(complex64_vector)
    DEF_DATA_TO_XML(complex128_vector)

    DEF_DATA_TO_XML(string_vector)
    DEF_DATA_TO_XML(bool_t_vector)

    pni::io::nx::xml::node 
    object_to_xml(const pni::io::nx::h5::nxobject &object)
    {
        using namespace pni::io::nx::xml;
        return field::object_to_xml(object);
    }

    pni::io::nx::h5::nxobject 
    object_from_xml(const pni::io::nx::h5::nxobject &parent,
                    const pni::io::nx::xml::node &node)
    {
        using namespace pni::io::nx::xml;
        return field::object_from_xml(parent,node);
    }
}
}
