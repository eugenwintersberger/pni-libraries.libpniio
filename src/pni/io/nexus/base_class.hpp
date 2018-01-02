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
// Created on: Dec 7, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/io/windows.hpp>
#include <pni/io/nexus/nexus_object.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief representation of a NeXus base class
//!
//! A NeXus base class is in fact an HDF5 group with an NX_class attribute
//! attached to it which tells the user what particular type of group he or
//! she is dealing with.
//!
//! This is a very thing utility class which provides the full interface of a
//! HDF5 group. But requires a value for NX_class to be set.
//!
class PNIIO_EXPORT BaseClass : public NeXusObject,
                               public hdf5::node::Group
{
  public:
    BaseClass() = default;
    BaseClass(const hdf5::node::Node &node);
    BaseClass(const hdf5::node::Group &parent,
              const hdf5::Path &path,
              const std::string &class_name,
              const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
              const hdf5::property::GroupCreationList &gcpl = hdf5::property::GroupCreationList(),
              const hdf5::property::GroupAccessList &gapl = hdf5::property::GroupAccessList());

    std::string get_class() const;
};

} // namespace nexus
} // namespace io
} // namespace pni
