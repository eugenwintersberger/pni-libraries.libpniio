//
// (c) Copyright 2018 DESY
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
// Created on: Jan 3, 2018
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/windows.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief base class factory
//!
//! Factory class for base classes.
//!
class PNINEXUS_EXPORT BaseClassFactory
{
  public:

    //!
    //! @brief create a new base class
    //!
    //! Create a new HDF5 group which satisfies the requirements of a base
    //! class. The function checks if the name of the group compiles
    //! with the NeXus standard.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @param parent reference to the parent group on which to create the
    //!               base class
    //! @param path reference to the path to the base class
    //! @param class_name reference to the class name of the base class
    //! @param lcpl optional reference to a link creation property list
    //! @param gcpl optional reference to a group creation property list
    //! @param gapl optional reference to a group access property list
    //! @return an instance of hdf5::node::Group
    //!
    static hdf5::node::Group create(const hdf5::node::Group &parent,
                                    const hdf5::Path &path,
                                    const std::string &class_name,
                                    const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
                                    const hdf5::property::GroupCreationList &gcpl = hdf5::property::GroupCreationList(),
                                    const hdf5::property::GroupAccessList &gapl = hdf5::property::GroupAccessList());
};

} // namespace nexus
} // namespace io
} // namespace pni
