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
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/parsers.hpp>
#include <pni/nexus/xml/node.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

using ParserType = pni::io::parser<hdf5::Dimensions::value_type>;

using IndexValue = std::pair<hdf5::Dimensions::value_type,
                             hdf5::Dimensions::value_type>;
using IndexValueVector = std::vector<IndexValue>;

bool operator<(const IndexValue &lhs,const IndexValue &rhs);

class DimensionNodeHandler
{
  private:
    static IndexValue index_value_from_node(const Node &node);
  public:
    static hdf5::Dimensions dimensions(const Node &node);
};


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
