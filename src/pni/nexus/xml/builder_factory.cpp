//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 8, 2017
//
#include <pni/nexus/xml/builder_factory.hpp>
#include <pni/nexus/xml/group_builder.hpp>
#include <pni/nexus/xml/field_builder.hpp>
#include <pni/nexus/xml/attribute_builder.hpp>
#include <pni/nexus/xml/link_builder.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

ObjectBuilder::UniquePointer BuilderFactory::create(const Node::value_type &element)
{
  if(element.first == "field")
    return ObjectBuilder::UniquePointer(new FieldBuilder(element.second));
  else if(element.first == "group")
    return ObjectBuilder::UniquePointer(new GroupBuilder(element.second));
  else if(element.first == "attribute")
    return ObjectBuilder::UniquePointer(new AttributeBuilder(element.second));
  else if(element.first == "link")
    return ObjectBuilder::UniquePointer(new LinkBuilder(element.second));
  else
  {
    return nullptr;
  }
}


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
