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

#include <pni/io/nexus/xml/datatype_builder.hpp>
#include <pni/io/nexus/datatype_factory.hpp>
#include <stdexcept>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

DatatypeBuilder::DatatypeBuilder(const Node &node) noexcept:
    node_(node)
{
}

hdf5::datatype::Datatype DatatypeBuilder::build() const
{
  if(!node_.has_attribute("type"))
  {
    throw std::runtime_error("Node has no type attribute!");
  }

  std::string type_code = node_.attribute("type").str_data();

  //need to handle the special case of a boolean type
  if(type_code == "bool_t") type_code = "bool";

  return DatatypeFactory::create(pni::core::type_id_from_str(type_code));
}



} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
