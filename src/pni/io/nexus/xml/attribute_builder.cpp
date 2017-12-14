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
// Created on: Dec 13, 2017
//

#include <pni/io/nexus/xml/attribute_builder.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

AttributeBuilder::AttributeBuilder(const Node &node):
    ObjectBuilder(node),
    datatype_builder_(node),
    dataspace_builder_(node),
    writer_(node)
{}

void AttributeBuilder::build(const hdf5::node::Node &parent) const
{
  std::string attribute_name = node().name();

  hdf5::datatype::Datatype type = datatype_builder_.build();
  hdf5::dataspace::Simple space = dataspace_builder_.build();

  hdf5::attribute::Attribute attribute = parent.attributes.create(attribute_name,type,space);

  writer_.write(attribute);

}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
