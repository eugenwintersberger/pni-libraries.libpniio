//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 8, 2017
//

#include <pni/nexus/xml/object_builder.hpp>
#include <pni/nexus/xml/builder_factory.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

ObjectBuilder::~ObjectBuilder()
{}

ObjectBuilder::ObjectBuilder(const Node &xml_node):
    xml_node_(xml_node)
{}

const Node &ObjectBuilder::node() const noexcept
{
  return xml_node_;
}

void ObjectBuilder::build(const hdf5::node::Node &parent) const
{
  for(auto element: xml_node_)
  {
    UniquePointer builder = BuilderFactory::create(element);

    if(builder) builder->build(parent);
  }
}





} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
