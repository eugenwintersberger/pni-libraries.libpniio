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

#include <pni/io/nexus/xml/dataspace_builder.hpp>


namespace pni {
namespace io {
namespace nexus {
namespace xml {



DataspaceBuilder::DataspaceBuilder(const Node &node):
    node_(node)
{}


using ParserType = pni::io::parser<hdf5::Dimensions::value_type>;

using IndexValue = std::pair<hdf5::Dimensions::value_type,
                             hdf5::Dimensions::value_type>;
using IndexValueVector = std::vector<IndexValue>;

bool operator<(const IndexValue &lhs,const IndexValue &rhs)
{
  return lhs.first<rhs.first;
}

//------------------------------------------------------------------------
IndexValue index_value_from_node(const Node &dim_node)
{
  ParserType p;
  Node index_attribute = dim_node.attribute("index");
  Node value_attribute = dim_node.attribute("value");

  return {p(index_attribute.str_data()),
          p(value_attribute.str_data())};
}

hdf5::dataspace::Simple DataspaceBuilder::build() const
{
  using hdf5::dataspace::Simple;

  Simple space({1},{1});

  auto has_dimension_node = node_.get_child_optional("dimensions");
  if(has_dimension_node)
  {
    Node dimension_node = has_dimension_node.get();

    size_t rank = ParserType()(dimension_node.attribute("rank").str_data());
    IndexValueVector index_values;
    for(auto value: dimension_node)
      if(value.first == "dim")
        index_values.push_back(index_value_from_node(value.second));

    if(rank != index_values.size())
    {
      std::stringstream ss;
      ss<<"Number of dim elements ("<<index_values.size()<<") does not match "
        <<"dimension rank ("<<rank<<")!";
      throw std::runtime_error(ss.str());
    }

    std::sort(index_values.begin(),index_values.end());
    hdf5::Dimensions current_dimensions;
    std::transform(index_values.begin(),index_values.end(),
                   std::back_inserter(current_dimensions),
                   [](const IndexValue &value) { return value.second; });

    if(current_dimensions.empty())
    {
      std::stringstream ss;
      ss<<"Valid dimensions tag without content!";
      throw std::runtime_error(ss.str());
    }

    space = Simple(current_dimensions,current_dimensions);
  }

  return space;


}


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
