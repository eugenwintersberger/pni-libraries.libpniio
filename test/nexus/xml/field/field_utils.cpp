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

#include "field_utils.hpp"
#include <pni/nexus/xml/field_node.hpp>



namespace xml_test{
namespace field_test{

    size_t size(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::size(node);
    }

    size_t rank(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::rank(node);
    }

    pni::type_id_t type_id(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::type_id(node);
    }

#define DEF_DATA_FROM_XML(type) \
    void data_from_xml(const pni::nexus::xml::Node &node, \
                       type &value) \
    { \
        using namespace pni::nexus::xml; \
        value = FieldNode::data_from_xml<type>(node); \
    }

    DEF_DATA_FROM_XML(pni::uint8)
    DEF_DATA_FROM_XML(pni::int8)
    DEF_DATA_FROM_XML(pni::uint16)
    DEF_DATA_FROM_XML(pni::int16)
    DEF_DATA_FROM_XML(pni::uint32)
    DEF_DATA_FROM_XML(pni::int32)
    DEF_DATA_FROM_XML(pni::uint64)
    DEF_DATA_FROM_XML(pni::int64)

    DEF_DATA_FROM_XML(pni::float32)
    DEF_DATA_FROM_XML(pni::float64)
#ifndef _MSC_VER
    DEF_DATA_FROM_XML(pni::float128)
#endif
    
    DEF_DATA_FROM_XML(pni::complex32)
    DEF_DATA_FROM_XML(pni::complex64)
#ifndef _MSC_VER
    DEF_DATA_FROM_XML(pni::complex128)
#endif

    DEF_DATA_FROM_XML(pni::string)
    DEF_DATA_FROM_XML(pni::bool_t)
    
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
#ifndef _MSC_VER
    DEF_DATA_FROM_XML(float128_vector)
#endif
    
    DEF_DATA_FROM_XML(complex32_vector)
    DEF_DATA_FROM_XML(complex64_vector)
#ifndef _MSC_VER
    DEF_DATA_FROM_XML(complex128_vector)
#endif

    DEF_DATA_FROM_XML(string_vector)
    DEF_DATA_FROM_XML(bool_t_vector)

#define DEF_DATA_TO_XML(type) \
    void data_to_xml(const type &value,pni::nexus::xml::Node &node) \
    { \
        using namespace pni::nexus::xml; \
        FieldNode::data_to_xml(node,value); \
    }
    
    DEF_DATA_TO_XML(pni::uint8)
    DEF_DATA_TO_XML(pni::int8)
    DEF_DATA_TO_XML(pni::uint16)
    DEF_DATA_TO_XML(pni::int16)
    DEF_DATA_TO_XML(pni::uint32)
    DEF_DATA_TO_XML(pni::int32)
    DEF_DATA_TO_XML(pni::uint64)
    DEF_DATA_TO_XML(pni::int64)

    DEF_DATA_TO_XML(pni::float32)
    DEF_DATA_TO_XML(pni::float64)
#ifndef _MSC_VER
    DEF_DATA_TO_XML(pni::float128)
#endif
    
    DEF_DATA_TO_XML(pni::complex32)
    DEF_DATA_TO_XML(pni::complex64)
#ifndef _MSC_VER
    DEF_DATA_TO_XML(pni::complex128)
#endif

    DEF_DATA_TO_XML(pni::string)
    DEF_DATA_TO_XML(pni::bool_t)
    
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
#ifndef _MSC_VER
    DEF_DATA_TO_XML(float128_vector)
#endif
    
    DEF_DATA_TO_XML(complex32_vector)
    DEF_DATA_TO_XML(complex64_vector)
#ifndef _MSC_VER
    DEF_DATA_TO_XML(complex128_vector)
#endif

    DEF_DATA_TO_XML(string_vector)
    DEF_DATA_TO_XML(bool_t_vector)

    pni::nexus::xml::Node
    object_to_xml(const hdf5::node::Node &object)
    {
        using namespace pni::nexus::xml;
        return FieldNode::object_to_xml(object);
    }

    hdf5::node::Node
    object_from_xml(const hdf5::node::Node &parent,
                    const pni::nexus::xml::Node &node)
    {
        using namespace pni::nexus::xml;
        return FieldNode::object_from_xml(parent,node);
    }
}
}
