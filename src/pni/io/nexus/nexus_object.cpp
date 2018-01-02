//
// (c) Copyright 2018 DESY
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
// Created on: Jan 2, 2018
//

#include <pni/io/nexus/nexus_object.hpp>
#include <pni/io/nexus/predicates.hpp>
#include <stdexcept>
#include <sstream>

namespace pni {
namespace io {
namespace nexus {

NeXusObject::NeXusObject(const hdf5::Path &path)
{
  IsValidNeXusName name_check;

  if(!name_check(path.name()))
  {
    std::stringstream ss;
    ss<<"Failure to create a NeXus base class!";
    ss<<"The path ["<<path<<"] does not comply with the NeXus name rules!";
    throw std::runtime_error(ss.str());
  }
}

} // namespace nexus
} // namespace io
} // namespace pni
