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
// Created on: Dec 13, 2017
//

#include <pni/nexus/xml/attribute_builder.hpp>

namespace pni {
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
  hdf5::dataspace::Dataspace space = hdf5::dataspace::Scalar();

  bool is_string = ((type.get_class() == hdf5::datatype::Class::VARLENGTH)
		    ||
		    (type.get_class() == hdf5::datatype::Class::STRING));

  if( (!is_string) || node().get_child_optional("dimensions"))
  {
    space = dataspace_builder_.build();
  }

  hdf5::attribute::Attribute attribute = parent.attributes.create(attribute_name,type,space);

  writer_.write(attribute);

}

} // namespace xml
} // namespace nexus
} // namespace pni
