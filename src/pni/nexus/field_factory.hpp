//
// (c) Copyright 2018 DESY
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
// Created on: Jan 3, 2018
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/windows.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief factory class for fields
//!
//! This factory class provides two static factory functions creating
//! HDF5 datasets which comply to the NeXus rules. In particular
//! these functions take care that the name of the dataset is compatible
//! with the NeXus naming rules.
//!
class PNIIO_EXPORT FieldFactory
{
  public:

    //!
    //! @brief create a dataset
    //!
    //! Forwards all arguments to the hdf5::node::Dataset constructor after
    //! checking if the name of the field complies to the NeXus naming
    //! conventions. If this is not the case std::runtime_error is thrown.
    //!
    //! @throws std::runtime_error in case of a failure
    //!
    //! @param parent reference to the parent group
    //! @param path reference to the path of the new field
    //! @param type reference to the data type of the new field
    //! @param space reference to the data space of the new field
    //! @param lcpl optional reference to a link creation property list
    //! @param dcpl optional reference to a dataset creation property list
    //! @param acpl optional reference to a dataset access property list
    //!
    static hdf5::node::Dataset create(const hdf5::node::Group &parent,
                                      const hdf5::Path &path,
                                      const hdf5::datatype::Datatype &type,
                                      const hdf5::dataspace::Dataspace &space,
                                      const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
                                      const hdf5::property::DatasetCreationList &dcpl = hdf5::property::DatasetCreationList(),
                                      const hdf5::property::DatasetAccessList &acpl = hdf5::property::DatasetAccessList());

    //!
    //! @brief create a chunked dataset
    //!
    //! @throws std::runtime_error in case of a failure
    //!
    //! @param parent reference to the parent group
    //! @param path reference to the new path of the field
    //! @param type reference to the data type of the field
    //! @param space reference to the data space of the field
    //! @param chunk_shape reference to the chunk shape of the field
    //! @param lcpl optional reference to a link creation property list
    //! @param dcpl optional reference to a dataset creation property list
    //! @param acpl optional reference to a dataset access property list
    //!
    static hdf5::node::Dataset create(const hdf5::node::Group &parent,
                                      const hdf5::Path &path,
                                      const hdf5::datatype::Datatype &type,
                                      const hdf5::dataspace::Simple &space,
                                      const hdf5::Dimensions &chunk_shape,
                                      const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
                                      const hdf5::property::DatasetCreationList &dcpl = hdf5::property::DatasetCreationList(),
                                      const hdf5::property::DatasetAccessList &acpl = hdf5::property::DatasetAccessList());
};


} // namespace nexus
} // namespace io
} // namespace pni
