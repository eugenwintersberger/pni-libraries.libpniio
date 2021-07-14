//
// (c) Copyright 2018 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Jan 3, 2018
//

#include <pni/nexus/base_class_factory.hpp>
#include <pni/nexus/predicates.hpp>

namespace pni {
namespace io {
namespace nexus {

hdf5::node::Group BaseClassFactory::create(const hdf5::node::Group &parent,
                                           const hdf5::Path &path,
                                           const std::string &class_name,
                                           const hdf5::property::LinkCreationList &lcpl,
                                           const hdf5::property::GroupCreationList &gcpl,
                                           const hdf5::property::GroupAccessList &gapl)
{
  IsValidNeXusName name_check;
  if(!name_check(path.name()))
  {
    std::stringstream ss;
    ss<<"Cannot construct ["<<path<<"] below ["<<parent.link().path()<<"] as its "
      <<"name does not comply to the NeXus standard!";
    throw std::runtime_error(ss.str());
  }

  hdf5::node::Group base_class(parent,path,lcpl,gcpl,gapl);

  auto type = hdf5::datatype::create<std::string>();
  hdf5::dataspace::Scalar space;
  base_class.attributes.create("NX_class",type,space).write(class_name);

  return base_class;
}

} // namespace nexus
} // namespace io
} // namespace pni
