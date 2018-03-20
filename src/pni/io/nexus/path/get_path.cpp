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
// Created on: Dec 18, 2017
//

#include <pni/io/nexus/path/path.hpp>
#include <pni/io/nexus/path/utils.hpp>
#include <pni/io/nexus/containers.hpp>
#include <algorithm>

namespace pni {
namespace io {
namespace nexus {

Path::Element get_group_element(const hdf5::node::Group &group)
{
  //--------------------set the name of the group link-----------
  std::string group_name;

  hdf5::Path group_path = group.link().path();
  if(group_path.is_root())
    group_name = "/";
  else
    group_name = group_path.name();

  //--------------check the class of a group-------------------
  std::string group_class;
  if(group.attributes.exists("NX_class"))
  {
    hdf5::attribute::Attribute nx_class = group.attributes["NX_class"];
    hdf5::datatype::String file_type = nx_class.datatype();
    nx_class.read(group_class,file_type);
  }

  return {group_name,group_class};
}

Path::Element get_dataset_element(const hdf5::node::Dataset &dataset)
{
  return {dataset.link().path().name(),std::string()};
}

Path::Element get_element(const hdf5::node::Node &node)
{
  switch(node.type())
  {
    case hdf5::node::Type::GROUP:
      return get_group_element(hdf5::node::Group(node));
    case hdf5::node::Type::DATASET:
      return get_dataset_element(hdf5::node::Dataset(node));
    default:
      return {std::string(),std::string()};
  }
}


Path get_path(const hdf5::node::Link &link)
{

  //
  // for a link we can assume that its parent object exists (which must be a
  // group).
  //
  hdf5::node::Group link_parent = link.parent();
  Path path = get_path(link_parent);

  //
  // a link is just a name and thus we cannot make any statement about the
  // particular type of the object referenced by the link. We thus only
  // set the name field of the path element.
  //
  path.push_back({link.path().name(),std::string()});

  return path;
}

Path get_path(const hdf5::node::Node &node)
{
  Path path;
  path.filename(node.link().file().path()); //set the path to the file

  hdf5::node::Node current_node = node.link().file().root();
  path.push_back(get_element(current_node));

  for(auto node_name: node.link().path())
  {
    if(current_node.type() == hdf5::node::Type::GROUP)
      current_node = hdf5::node::Group(current_node).nodes[node_name];

    path.push_back(get_element(current_node));
  }
  return path;
}

Path get_path(const hdf5::attribute::Attribute &attribute)
{
  Path parent_path = get_path(*attribute.parent_link());
  parent_path.attribute(attribute.name());
  return parent_path;
}

} // namespace nexus
} // namespace io
} // namespace pni
