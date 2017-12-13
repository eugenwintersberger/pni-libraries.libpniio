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

#include <pni/io/nexus/xml/data_node.hpp>
#include <pni/io/nexus/xml/dimensions.hpp>
#include <pni/io/parsers.hpp>
#include <numeric>

namespace pni{
namespace io{
namespace nexus{
namespace xml{
    
//! parser for size_t values
using Size_tParser = pni::io::parser<size_t>;

bool operator<(const IndexValue &lhs,const IndexValue &rhs)
{
  return lhs.first<rhs.first;
}

//------------------------------------------------------------------------
Node Dimensions::index_value_to_node(size_t index,size_t value)
{
  Node dim_node;
  dim_node.put("<xmlattr>.index",index);
  dim_node.put("<xmlattr>.value",value);

  return dim_node;
}

//------------------------------------------------------------------------
IndexValue Dimensions::index_value_from_node(const Node &dim_node)
{
  Size_tParser p;
  Node index_attribute = dim_node.attribute("index");
  Node value_attribute = dim_node.attribute("value");

  return {p(DataNode::read(index_attribute)),
    p(DataNode::read(value_attribute))};
}

//-----------------------------------------------------------------------
size_t Dimensions::rank(const Node &dim)
{
  Node type_attribute = dim.attribute("rank");
  return Size_tParser()(type_attribute.str_data());
}

//-----------------------------------------------------------------------
size_t Dimensions::size(const Node &dim)
{
  hdf5::Dimensions shape = object_from_xml(dim);

  return std::accumulate(shape.begin(),shape.end(),size_t(1),
                         std::multiplies<size_t>());

}

//-----------------------------------------------------------------------
hdf5::Dimensions Dimensions::object_from_xml(const Node &dims)
{
  using namespace pni::core;
  IndexValueVector buffer;
  Size_tParser p;

  //read all index value pairs
  for(auto dim: dims)
    if(dim.first == "dim")
      buffer.push_back(index_value_from_node(dim.second));

  if(buffer.size()!=rank(dims))
    throw shape_mismatch_error(EXCEPTION_RECORD,
                               "Rank in dimensions tag does not match number of dim values!");

  std::sort(buffer.begin(),buffer.end());

  hdf5::Dimensions result;
  auto iter = buffer.begin();
  std::generate_n(std::back_inserter(result),buffer.size(),
                  [&iter](){ return (iter++)->second; });
  return result;
}


//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
