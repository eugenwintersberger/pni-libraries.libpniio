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
#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus/xml/group_builder.hpp>
#include <pni/io/nexus/xml/object_builder.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/io/nexus/xml/data_node.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/error.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

hdf5::node::Group group_from_node(const hdf5::node::Group &parent,
                                  const Node &group_node)
{
    using namespace pni::core;

    //typedef GTYPE group_type;
    //typedef typename GTYPE::value_type object_type;

    //check if the group tag provides a name attribute
    if(!has_attribute(group_node,"name"))
        throw value_error(EXCEPTION_RECORD,
                "XML group does not provide a name!");

    //fetch the name for the group
    Node name_attr = get_attribute(group_node,"name");
    std::string name = DataNode::read(name_attr);

    if(name == "/"  && parent.link().path().is_root())
        return parent;

    //create the group
    hdf5::node::Group group(parent,name);

    //if the tag has a type attribute add its value as an NX_class
    //attribute
    if(has_attribute(group_node,"type"))
    {
        Node class_attr = get_attribute(group_node,"type");
        string gclass   = DataNode::read(class_attr);

        group.attributes.create("NX_class",hdf5::datatype::create<std::string>(),
                                           hdf5::dataspace::Scalar()).write(gclass);
    }

    return group;
}

GroupBuilder::GroupBuilder(const Node &xml_node):
    ObjectBuilder(xml_node)
{}

void GroupBuilder::build(const hdf5::node::Node &parent) const
{
  using hdf5::node::Group;

  Group parent_group = parent;
  Group new_group = group_from_node(parent,node());

  ObjectBuilder builder(node());
  builder.build(new_group);
}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
