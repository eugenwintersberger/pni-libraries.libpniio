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

#include <pni/nexus/xml/dataspace_builder.hpp>
#include <pni/nexus/xml/dimension_node_handler.hpp>


namespace pni {
namespace io {
namespace nexus {
namespace xml {

DataspaceBuilder::DataspaceBuilder(const Node &node):
    node_(node)
{}

hdf5::dataspace::Simple DataspaceBuilder::build() const
{
  using hdf5::dataspace::Simple;

  Simple space({1},{1});

  auto has_dimension_node = node_.get_child_optional("dimensions");
  if(has_dimension_node)
  {
    Node dimension_node = has_dimension_node.get();
    hdf5::Dimensions current_dimensions = DimensionNodeHandler::dimensions(dimension_node);

    space = Simple(current_dimensions,current_dimensions);
  }

  return space;


}


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
