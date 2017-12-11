//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nexus/xml/io_node.hpp>
#include <pni/io/nexus/xml/dimensions.hpp>


namespace pni{
namespace io{
namespace nexus{
namespace xml{

//------------------------------------------------------------------------
size_t IONode::size(const Node &io_node)
{
  auto dims = io_node.get_child_optional("dimensions");
  if(dims)
    return Dimensions::size(*dims);
  else
    return 1;
}

//------------------------------------------------------------------------
size_t IONode::rank(const Node &io_node)
{
  auto dims = io_node.get_child_optional("dimensions");
  if(dims)
    return Dimensions::rank(*dims);
  else
    return 0;
}

//------------------------------------------------------------------------
std::string IONode::name(const Node &io_node)
{
  Node name_attribute = get_attribute(io_node,"name");
  return DataNode::read(name_attribute);
}

//------------------------------------------------------------------------
hdf5::Dimensions IONode::shape(const Node &io_node)
{
  hdf5::Dimensions shape{1};
  auto dims = io_node.get_child_optional("dimensions");
  if(dims)
    shape = Dimensions::object_from_xml(*dims);

  return shape;
}

//------------------------------------------------------------------------
pni::core::type_id_t IONode::type_id(const Node &io_node)
{
  Node type_attribute = get_attribute(io_node,"type");
  pni::core::string type_code = DataNode::read(type_attribute);

  //need to handle the special case of a boolean type
  if(type_code == "bool_t") type_code = "bool";

  return pni::core::type_id_from_str(type_code);
}

    
//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
