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

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief list of HDF5 groups
//!
//! A specialization of std::list storing instances of hdf5::node::Group.
//!
class GroupList : public std::list<hdf5::node::Group>
{
  public:
    using std::list<hdf5::node::Group>::list;
};

//!
//! @brief list of HDF5 nodes
//!
//! A specialization of std::list storing instances of hdf5::node::Node;
//!
class NodeList : public std::list<hdf5::node::Node>
{
  public:
    using std::list<hdf5::node::Node>::list;
};

//!
//! @brief list of datasets
//!
//! A specialization of std::list storing instances of hdf5::node::Dataset;
//!
class DatasetList : public std::list<hdf5::node::Dataset>
{
  public:
    using std::list<hdf5::node::Dataset>::list;
};


} // namespace nexus
} // namespace io
} // namespace pni
