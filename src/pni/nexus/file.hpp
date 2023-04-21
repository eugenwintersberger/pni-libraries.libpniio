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
// Created on: Dec 6, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>

#include <pni/nexus/version.hpp>
#include <pni/windows.hpp>

namespace pni {
namespace nexus {

//!
//! @brief checks if a file is a NeXus file
//!
//! Predicate function checking if the given path references a NeXus file.
//! For this to be true the path has to first refer to an HDF5 file.
//! If this is the case the file will be opened and checked for the attributes
//! required by the NeXus standard.
//!
//! @param path reference to the path of a particular file system object
//! @return true if the reference object is a NeXus file, flase otherwise
//!
PNINEXUS_EXPORT bool is_nexus_file(const fs::path &path);

//!
//! @brief create a new NeXus file
//!
//! This function is basically an enhancement of the standard hdf5::file::create function.
//! In addition of creating a new HDF5 file it also adds all the attributes to the root
//! group of the file required by the NeXus standard. The arguments are the same as for
//! hdf5::file::create.
//!
//! The only mandatory argument is the path to the new file. By default, an exception will
//! be thrown if the file already exists in order to prohibit the user from accidentally
//! overwriting an existing file. To change this behavior the AccessFlags must be
//! passed as a second argument. References to file creation and file access property
//! lists can be passed as third and fourth argument.
//!
//! For more detailed information see the h5cpp documentation.
//!
//! @throws std::runtime_error in case of a failure
//!
//! @param path  reference to the path ot the new file
//! @param flags access flags for the new file
//! @param fcpl  reference to a file creation property list
//! @param fapl  reference to a file access property list
//! @return instance of hdf5::file::File
//!
PNINEXUS_EXPORT
hdf5::file::File create_file(const fs::path &path,
                             hdf5::file::AccessFlags flags = hdf5::file::AccessFlags::Exclusive,
                             const hdf5::property::FileCreationList &fcpl = hdf5::property::FileCreationList(),
                             const hdf5::property::FileAccessList &fapl = hdf5::property::FileAccessList());

PNINEXUS_EXPORT
hdf5::file::File create_file(const fs::path &path,
                             hdf5::file::AccessFlagsBase flags,
                             const hdf5::property::FileCreationList &fcpl = hdf5::property::FileCreationList(),
                             const hdf5::property::FileAccessList &fapl = hdf5::property::FileAccessList());

//!
//! @brief open an existing NeXus file
//!
//! Function opening an existing NeXus file. This functions checks whether
//! or not a file is a valid NeXus file. If this is not the case an exception
//! will be thrown. In order to open a file without this check just use the
//! hdf5::file::open function from the h5cpp library.
//!
//! @throws std::runtime_error in case of a failure
//!
//! @param path  reference to the file's path
//! @param flags access flags for the file
//! @param fapl  reference to the file access property list
//! @return instance of hdf5::file::File
//!
PNINEXUS_EXPORT
hdf5::file::File open_file(const fs::path &path,
                      hdf5::file::AccessFlags flags = hdf5::file::AccessFlags::ReadOnly,
                      const hdf5::property::FileAccessList &fapl = hdf5::property::FileAccessList());

PNINEXUS_EXPORT
hdf5::file::File open_file(const fs::path &path,
                      hdf5::file::AccessFlagsBase flags,
                      const hdf5::property::FileAccessList &fapl = hdf5::property::FileAccessList());

} // namespace nexus
} // namespace pni
