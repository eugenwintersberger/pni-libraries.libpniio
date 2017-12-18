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
// Created on: Dec 18, 2017
//

#include <pni/io/nexus/path/path_object.hpp>

namespace pni {
namespace io {
namespace nexus {

PathObject::PathObject():
    type_(Type::NONE),
    attribute_(),
    group_(),
    dataset_()
{}

PathObject::PathObject(const hdf5::attribute::Attribute &attribute):
    type_(Type::ATTRIBUTE),
    attribute_(attribute),
    group_(),
    dataset_()
{}

PathObject::PathObject(const hdf5::node::Group &group):
    type_(Type::GROUP),
    attribute_(),
    group_(group),
    dataset_()
{}

PathObject::PathObject(const hdf5::node::Dataset &dataset):
    type_(Type::DATASET),
    attribute_(),
    group_(),
    dataset_(dataset)
{}

PathObject::Type PathObject::type() const noexcept
{
  return type_;
}

std::ostream &operator<<(std::ostream &stream,const PathObject::Type &type)
{
  switch(type)
  {
    case PathObject::Type::NONE: return stream<<"NONE";
    case PathObject::Type::ATTRIBUTE: return stream<<"ATTRIBUTE";
    case PathObject::Type::DATASET: return stream<<"DATASET";
    case PathObject::Type::GROUP: return stream<<"GROUP";
    default:
      return stream;
  }
}


bool is_dataset(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::DATASET;
}

bool is_attribute(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::ATTRIBUTE;
}

bool is_group(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::GROUP;
}



} // namespace nexus
} // namespace io
} // namespace pni
