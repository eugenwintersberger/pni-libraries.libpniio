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

//!
//! @brief type erasure for path addressable objects
//!
//! This is a very simple type erasure (though not implemented in the
//! classic scheme) for all objects which can be addressed with a
//! NeXus path. The current path implementation allows to address
//!
//! \li groups
//! \li datasets
//! \li and attributes
//!
//! while a common HDF5 path can only address the first two. Thus we
//! need a special return type for all path operations when
//! dereferencing objects in an HDF5 tree.
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

    //!
    //! @brief constructor
    //!
    //! Build a PathObject from an attribute. In this case type()
    //! will return Type::ATTRIBUTE.
    //!
    //! @param attribute reference to the original attribute
    //!
    PathObject(const hdf5::attribute::Attribute &attribute);

    //!
    //! @brief constructor
    //!
    //! Build a PathObject from a dataset. After construction
    //! type() will return Type::DATASET.
    //!
    //! @param dataset reference to the original dataset
    //!
    PathObject(const hdf5::node::Node &dataset);

    //!
    //! @brief copy constructor
    //!
    //! We use the compiler provided default implementation here.
    //!
    PathObject(const PathObject &) = default;

    //!
    //! @brief return type of the currently stored object
    //!
    //! Return the type of the currently stored object. If the
    //! object was default constructed NONE is returned.
    //!
    Type type() const noexcept;

    //!
    //! @brief implicit conversion to an attribute
    //!
    operator hdf5::attribute::Attribute() const noexcept
    {
      return attribute_;
    }

    //!
    //! @brief implicit conversion to a group
    //!
    operator hdf5::node::Group() const noexcept
    {
      return group_;
    }

    //!
    //! @brief implicit conversion to a dataset
    //!
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

//!
//! @brief container for PathObject
//!
//! Used in algorithms returning several instances of PathObject.
//! Can be used along with STL algorithms to filter particular
//! types.
//!
class PathObjectList : public std::list<PathObject>
{
  public:
    using std::list<PathObject>::list;
};

std::ostream &operator<<(std::ostream &stream,const PathObject::Type &type);

//!
//! @brief return true if object stores a dataset
//!
PNIIO_EXPORT bool is_dataset(const PathObject &object) noexcept;

//!
//! @brief return true if object stores an attribute
//!
PNIIO_EXPORT bool is_attribute(const PathObject &object) noexcept;

//!
//! @brief return true if object stores a group
//!
PNIIO_EXPORT bool is_group(const PathObject &object) noexcept;



} // namespace nexus
} // namespace io
} // namespace pni
