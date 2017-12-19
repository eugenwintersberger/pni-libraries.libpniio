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

#include <sstream>
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

PathObject::PathObject(const hdf5::node::Node &node):
    type_(Type::NONE),
    attribute_(),
    group_(),
    dataset_()
{
  switch(node.type())
  {
    case hdf5::node::Type::DATASET:
      dataset_ = node;
      type_ = Type::DATASET;
      break;
    case hdf5::node::Type::GROUP:
      group_ = node;
      type_ = Type::GROUP;
      break;
    default:
      std::stringstream ss;
      ss<<"HDF5 node ["<<node.link().path()<<"] is neither a dataset nor a group"
        <<" and thus cannot be converted to an instance of PathObject!";
      throw std::runtime_error(ss.str());
  }
}

PathObject::Type PathObject::type() const noexcept
{
  return type_;
}

PathObject::operator hdf5::attribute::Attribute() const
{
  if(type() != Type::ATTRIBUTE)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to an attribute!";
    throw std::runtime_error(ss.str());
  }
  return attribute_;
}

PathObject::operator hdf5::node::Group() const
{
  if(type() != Type::GROUP)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to a group!";
    throw std::runtime_error(ss.str());
  }
  return group_;
}

PathObject::operator hdf5::node::Dataset() const
{
  if(type() != Type::DATASET)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to a dataset!";
    throw std::runtime_error(ss.str());
  }
  return dataset_;
}

PathObject::operator hdf5::node::Node() const
{
  if(type()==Type::DATASET)
    return dataset_;
  else if(type() == Type::GROUP)
    return group_;
  else
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
        <<"converted to a dataset!";
    throw std::runtime_error(ss.str());
  }
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
