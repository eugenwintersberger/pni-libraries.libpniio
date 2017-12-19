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
#pragma once

#include <h5cpp/hdf5.hpp>
#include <vector>
#include <list>
#include <pni/io/windows.hpp>

namespace pni {
namespace io {
namespace nexus {

class PathObjectList;

//!
//! @brief list of HDF5 nodes
//!
//! A specialization of std::list storing instances of hdf5::node::Node;
//!
class PNIIO_EXPORT NodeList : public std::vector<hdf5::node::Node>
{
  public:
    using std::vector<hdf5::node::Node>::vector;
};

//!
//! @brief list of HDF5 groups
//!
//! A specialization of std::list storing instances of hdf5::node::Group.
//!
class PNIIO_EXPORT GroupList : public std::vector<hdf5::node::Group>
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

    GroupList(const PathObjectList &list);
};



//!
//! @brief list of datasets
//!
//! A specialization of std::list storing instances of hdf5::node::Dataset;
//!
class PNIIO_EXPORT DatasetList : public std::vector<hdf5::node::Dataset>
{
  public:
    using std::vector<hdf5::node::Dataset>::vector;

    DatasetList(const PathObjectList &list);
};


} // namespace nexus
} // namespace io
} // namespace pni
