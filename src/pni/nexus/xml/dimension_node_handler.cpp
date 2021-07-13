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

#include <pni/nexus/xml/dimension_node_handler.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {


bool operator<(const IndexValue &lhs,const IndexValue &rhs)
{
  return lhs.first<rhs.first;
}

hdf5::Dimensions DimensionNodeHandler::dimensions(const Node &node)
{
  size_t rank = ParserType()(node.attribute("rank").str_data());
  IndexValueVector index_values;
  for(auto value: node)
    if(value.first == "dim")
      index_values.push_back(index_value_from_node(value.second));

  if (rank > 0 and index_values.size() == 0){
    for(size_t rk = 0; rk != rank; rk++)
      index_values.push_back({rk, rk == 0 ? 0 : 1});
  }
  else if(rank != index_values.size())
  {
    std::stringstream ss;
    ss<<"Number of dim elements ("<<index_values.size()<<") does not match "
      <<"dimension rank ("<<rank<<")!";
    throw std::runtime_error(ss.str());
  }

  std::sort(index_values.begin(),index_values.end());
  hdf5::Dimensions dimensions;
  std::transform(index_values.begin(),index_values.end(),
                 std::back_inserter(dimensions),
                 [](const IndexValue &value) { return value.second; });

  if(dimensions.empty())
  {
    std::stringstream ss;
    ss<<"Valid dimensions tag without content!";
    throw std::runtime_error(ss.str());
  }

  return dimensions;
}


//------------------------------------------------------------------------
IndexValue DimensionNodeHandler::index_value_from_node(const Node &dim_node)
{
  ParserType p;
  Node index_attribute = dim_node.attribute("index");
  Node value_attribute = dim_node.attribute("value");

  return {p(index_attribute.str_data()),
          p(value_attribute.str_data())};
}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
