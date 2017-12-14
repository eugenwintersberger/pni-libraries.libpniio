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

#include <pni/io/nexus/predicates.hpp>

namespace pni {
namespace io {
namespace nexus {

NodePredicate::~NodePredicate()
{}

IsBaseClass::IsBaseClass(const std::string &name):
    class_name_(name)
{}

IsBaseClass::~IsBaseClass()
{}

bool IsBaseClass::operator()(const hdf5::node::Node &node) const
{
  if(!hdf5::node::is_group(node)) return false;

  if(!node.attributes.exists("NX_class")) return false;

  if(!class_name_.empty())
  {
    std::string value;
    node.attributes["NX_class"].read(value);
    return value==class_name_;
  }
  else
  {
    return true;
  }
}

IsTransformation::IsTransformation():
    IsBaseClass("NXtransformations")
{}

IsEntry::IsEntry():
    IsBaseClass("NXentry")
{}

IsSubentry::IsSubentry():
    IsBaseClass("NXsubentry")
{}

IsDetector::IsDetector():
    IsBaseClass("NXdetector")
{}

IsInstrument::IsInstrument():
    IsBaseClass("NXinstrument")
{}

IsSample::IsSample():
    IsBaseClass("NXsample")
{}

IsData::IsData():
    IsBaseClass("NXdata")
{}




} // namespace nexus
} // namespace io
} // namespace pni
