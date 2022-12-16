//
// (c) Copyright 2017 DESY
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
// Created on: Dec 8, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <vector>
#include <list>
#include <pni/windows.hpp>

namespace pni {
namespace nexus {

class PathObjectList;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
//!
//! @brief list of HDF5 nodes
//!
//! A specialization of std::list storing instances of hdf5::node::Node;
//!
class PNINEXUS_EXPORT NodeList : public std::vector<hdf5::node::Node>
{
  public:
    using std::vector<hdf5::node::Node>::vector;
};

//!
//! @brief list of HDF5 groups
//!
//! A specialization of std::list storing instances of hdf5::node::Group.
//!
class PNINEXUS_EXPORT GroupList : public std::vector<hdf5::node::Group>
{
  public:
    using std::vector<hdf5::node::Group>::vector;

    //!
    //! @brief conversion constructor
    //!
    //! This constructor is deliberately not marked as explicit. It
    //! is used to convert a list of nodes to a list of groups.
    //! This will only work if all nodes are indeed groups. Otherwise
    //! an exception is thrown.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @param nodes reference to the original node list
    //!
    GroupList(const NodeList &nodes);


    //!
    //! @brief default constructor
    //!
    //! Use the compiler provided default implementation.
    //!
    GroupList() = default;
};



//!
//! @brief list of datasets
//!
//! A specialization of std::vector storing instances of hdf5::node::Dataset;
//!
class PNINEXUS_EXPORT DatasetList : public std::vector<hdf5::node::Dataset>
{
  public:
    using std::vector<hdf5::node::Dataset>::vector;

    //!
    //! @brief default constructor
    //!
    //! Use the compiler provided default implementation here
    //!
    DatasetList() = default;

    //!
    //! @brief implicit conversion constructor
    //!
    //! This constructor is deliberately not marked as explicit. It
    //! is used to convert a list of nodes to a list of groups.
    //! This will only work if all nodes are indeed groups. Otherwise
    //! an exception is thrown.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @param nodes reference to the original node list
    //!
    DatasetList(const NodeList &nodes);
};


class PNINEXUS_EXPORT AttributeList : public std::vector<hdf5::attribute::Attribute>
{
  public:
    using std::vector<hdf5::attribute::Attribute>::vector;
};
#ifdef _MSC_VER
#pragma warning(pop)
#endif
} // namespace nexus
} // namespace pni
