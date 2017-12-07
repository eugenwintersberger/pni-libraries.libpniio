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
// Created on: Dec 7, 2017
//
#include <pni/io/nexus/base_class.hpp>

namespace pni {
namespace io {
namespace nexus {

BaseClass::BaseClass(const hdf5::node::Group &parent,
           const hdf5::Path &path,
           const std::string &class_name,
           const hdf5::property::LinkCreationList &lcpl,
           const hdf5::property::GroupCreationList &gcpl,
           const hdf5::property::GroupAccessList &gapl):
    Group(parent,path,lcpl,gcpl,gapl)
{
  auto type = hdf5::datatype::create<std::string>();
  hdf5::dataspace::Scalar space;
  attributes.create("NX_class",type,space).write(class_name);
}

BaseClass::BaseClass(const hdf5::node::Node &node):
    Group(node)
{
  if(!attributes.exists("NX_class"))
  {
    std::stringstream ss;
    ss<<"Node "<<link().path()<<" is not a base class!";
    throw std::runtime_error(ss.str());
  }
}

 std::string BaseClass::get_class() const
 {
   std::string value;
   attributes["NX_class"].read(value);
   return value;
 }

} // namespace nexus
} // namespace io
} // namespace pni
