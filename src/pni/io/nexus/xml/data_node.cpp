//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 15, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <algorithm>
#include <pni/io/nexus/xml/data_node.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

namespace pni{
namespace io{
namespace nexus{
namespace xml{

std::string DataNode::read(const Node &n)
{
  std::string data = n.data();
  boost::algorithm::trim(data);

  //we do not care about line breaks - the data of a node is considered
  //a linear stream of elements.
  std::replace(data.begin(),data.end(),'\n',' ');

  return data;
}

//-------------------------------------------------------------------------
void DataNode::write(Node &n,const std::string &data)
{
  n.put_value(data);
}

//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
