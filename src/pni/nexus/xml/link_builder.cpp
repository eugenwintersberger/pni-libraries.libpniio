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

#include <pni/nexus/xml/link_builder.hpp>
#include <pni/nexus/path/path.hpp>

namespace pni {
namespace nexus {
namespace xml {

LinkBuilder::LinkBuilder(const Node &node):
    ObjectBuilder(node)
{}

void LinkBuilder::build(const hdf5::node::Node &parent) const
{
  hdf5::node::Group link_parent(parent);
  std::string link_name = node().attribute("name").str_data();
  pni::nexus::Path link_target(pni::nexus::Path::from_string(node().attribute("target").str_data()));

  if(link_target.has_filename())
  {
    //create an external link
    boost::filesystem::path file_path = link_target.filename();
    hdf5::Path target_path(link_target);

    hdf5::node::link(file_path,target_path,link_parent,link_name);

  }
  else
  {
    //create a soft link
    hdf5::Path target_path(link_target);
    hdf5::node::link(target_path,link_parent,link_name);
  }

}


} // namespace xml
} // namespace nexus
} // namespace pni
