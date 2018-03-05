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
#include <pni/io/nexus/containers.hpp>

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
       DATASET = 4,
       LINK = 5

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
    //! @brief constructor
    //!
    //! Build a PathObject from a link.
    //!
    PathObject(const hdf5::node::Link &link);

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
    //! @brief provides implicit conversion to an attribute
    //!
    //! Returns the stored object as an HDF5 attribute. If the stored
    //! instance is not an HDF5 attribute an exception will be thrown.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre the object stored in the PathObject instance
    //!      is an instance of hdf5::attribute::Attribute
    //!
    operator hdf5::attribute::Attribute() const;

    //!
    //! @brief implicit conversion to a group
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre the object stored in the PathObject instance is
    //!      an instance of hdf5::node::Group
    //!
    operator hdf5::node::Group() const;

    //!
    //! @brief implicit conversion to a dataset
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre the object stored in PathObject instance is
    //!      an instance of hdf5::node::Dataset.
    //!
    operator hdf5::node::Dataset() const;

    //!
    //! @brief implicit conversion to a general HDF5 node type
    //!
    //! Provides implicit conversion to an HDF5 node instance. If the
    //! object stored is neither a group or a dataset an exception
    //! will be thrown.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre the object stored in the PathObject instance is
    //!      an instance of hdf5::node::Dataset of hdf5::node::Group.
    //!
    operator hdf5::node::Node() const;

    explicit operator hdf5::node::Link() const;

  private:
    Type type_;
    hdf5::attribute::Attribute attribute_;
    hdf5::node::Group group_;
    hdf5::node::Dataset dataset_;
    hdf5::node::Link link_;
};

#ifdef _MSC_VER
PNIIO_EXPORT bool operator==(const PathObject &a,const PathObject &b);
PNIIO_EXPORT bool operator<(const PathObject &a,const PathObject &b);
#endif

//!
//! @brief container for PathObject
//!
//! Used in algorithms returning several instances of PathObject.
//! Can be used along with STL algorithms to filter particular
//! types.
//!
class PNIIO_EXPORT PathObjectList : public std::list<PathObject>
{
  public:
    using std::list<PathObject>::list;

    //!
    //! @brief implicit conversion to a NodeList
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre all instances in the PathObjectList must store instances
    //!      of datasets or groups.
    //!
    operator NodeList() const;

    //!
    //! @brief implicit conversion to an AttributeList
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre all instances in the PathObjectList must store attributes
    //!
    operator AttributeList() const;

    //!
    //! @brief implicit conversion to a GroupList
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre all instances in the PathObjectList must store groups
    //!
    operator GroupList() const;

    //!
    //! @brief implicit conversion to a DatasetList
    //!
    //! @throws std::runtime_error in case of a failure
    //! @pre all instances in the PathObjetList must store datasets
    //!
    operator DatasetList() const;
};

PNIIO_EXPORT std::ostream &operator<<(std::ostream &stream,const PathObject::Type &type);

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
