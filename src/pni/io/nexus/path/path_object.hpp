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
#pragma once

#include <cstdint>
#include <iostream>
#include <h5cpp/hdf5.hpp>
#include <pni/io/windows.hpp>
#include <vector>

namespace pni {
namespace io {
namespace nexus {


class PNIIO_EXPORT PathObject
{
  public:
    enum class Type : uint8_t
    {
       NONE = 1,
       ATTRIBUTE = 2,
       GROUP = 3,
       DATASET = 4

    };

    //!
    //! @brief default constructor
    //!
    //! We need default construction for container types. When a
    //! PathObject is default constructed its type is Type::NONE.
    //! In this case no conversion to any other object could be
    //! achieved.
    //!
    PathObject();


    PathObject(const hdf5::attribute::Attribute &attribute);
    PathObject(const hdf5::node::Dataset &dataset);
    PathObject(const hdf5::node::Group &group);

    PathObject(const PathObject &) = default;

    Type type() const noexcept;

    operator hdf5::attribute::Attribute() const noexcept
    {
      return attribute_;
    }

    operator hdf5::node::Group() const noexcept
    {
      return group_;
    }

    operator hdf5::node::Dataset() const noexcept
    {
      return dataset_;
    }

  private:
    Type type_;
    hdf5::attribute::Attribute attribute_;
    hdf5::node::Group group_;
    hdf5::node::Dataset dataset_;



};

class PathObjectList : public std::list<PathObject>
{
  public:
    using std::list<PathObject>::list;
};

std::ostream &operator<<(std::ostream &stream,const PathObject::Type &type);

PNIIO_EXPORT bool is_dataset(const PathObject &object) noexcept;
PNIIO_EXPORT bool is_attribute(const PathObject &object) noexcept;
PNIIO_EXPORT bool is_group(const PathObject &object) noexcept;



} // namespace nexus
} // namespace io
} // namespace pni
