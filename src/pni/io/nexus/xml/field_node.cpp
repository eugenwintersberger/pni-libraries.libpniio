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
// Created on: Nov 27, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/error.hpp>
#include <pni/io/nexus/xml/data_node.hpp>
#include <pni/io/nexus/xml/dimensions.hpp>
#include <pni/io/nexus/xml/field_node.hpp>
#include <h5cpp/hdf5.hpp>


namespace pni{
namespace io{
namespace nexus{
namespace xml{

using namespace pni::core;


//------------------------------------------------------------------------
std::string FieldNode::unit(const Node &field_node)
{
  std::string unit;

  if(field_node.has_attribute("units"))
  {
    unit = field_node.attribute("units").str_data();
  }

  return unit;
}

//------------------------------------------------------------------------
std::string FieldNode::long_name(const Node &field_node)
{
  string long_name;

  if(field_node.has_attribute("long_name"))
  {
    long_name = field_node.attribute("long_name").str_data();
  }

  return long_name;
}

//-------------------------------------------------------------------------
hdf5::Dimensions FieldNode::chunk(const Node &field_node)
{
  auto chunk = field_node.get_child_optional("chunk");
  if(chunk)
    return Dimensions::object_from_xml(*chunk);
  else
    return hdf5::Dimensions();
}


//end of namespace
}
}
}
}
