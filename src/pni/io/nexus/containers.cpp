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

#include <pni/io/nexus/containers.hpp>
#include <algorithm>
#include <pni/io/nexus/path/path_object.hpp>

namespace pni {
namespace io {
namespace nexus {

GroupList::GroupList(const NodeList &nodes)
{
  std::copy(nodes.begin(),nodes.end(),std::back_inserter(*this));
}

GroupList::GroupList(const PathObjectList &list)
{
  std::copy(list.begin(),list.end(),std::back_inserter(*this));
}

DatasetList::DatasetList(const PathObjectList &list)
{
  std::copy(list.begin(),list.end(),std::back_inserter(*this));
}

} // namespace nexus
} // namespace io
} // namespace pni
