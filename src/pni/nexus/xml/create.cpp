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
// Created on: Dec 14, 2017
//

#include <pni/nexus/xml/create.hpp>

#include <pni/nexus/xml/object_builder.hpp>
#include <pni/nexus/xml/node.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

void create_from_file(const hdf5::node::Node &parent,const boost::filesystem::path &xml_file)
{
  //first we have to build the node data
  Node xml_node = Node::from_file(xml_file);
  ObjectBuilder builder(xml_node);
  builder.build(parent);
}

void create_from_string(const hdf5::node::Node &parent,const std::string &xml_data)
{
  Node xml_node = Node::from_string(xml_data);
  ObjectBuilder builder(xml_node);
  builder.build(parent);

}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
