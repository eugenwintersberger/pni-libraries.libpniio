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
// Created on: Jan 2, 2018
//
#pragma once

#include <pni/io/nexus/nexus_object.hpp>
#include <h5cpp/hdf5.hpp>

namespace pni {
namespace io {
namespace nexus {
//!
//! @brief NeXus field class
//!
//! This class provides custom constructors for NeXus fields. Currently, the
//! only purpose of this class is to check whether or not the naming conventions
//! for the field name are kept.
//!
//! This class is derived from NeXusObject (which performs the name check)
//! and hdf5::node::Dataset.
//!
class Field : public NeXusObject,
              public hdf5::node::Dataset
{
  public:
    //!
    //! @brief default constructor
    //!
    //! Required for STL containers. Use compiler provided default
    //! implementation here.
    //!
    Field() = default;

    //!
    //! @brief constructor
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
    Field(const hdf5::node::Group &parent,
          const hdf5::Path &path,
          const hdf5::datatype::Datatype &type,
          const hdf5::dataspace::Dataspace &space,
          const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
          const hdf5::property::DatasetCreationList &dcpl = hdf5::property::DatasetCreationList(),
          const hdf5::property::DatasetAccessList &acpl = hdf5::property::DatasetAccessList()
          );

    //!
    //! @brief conversion constructor
    //!
    //! Constructs a NeXus field from a general HDF5 node.
    //!
    //! @param node reference to the HDF5 node
    //!
    Field(const hdf5::node::Node &node);

    //!
    //! @brief copy constructor
    //!
    //! Required for STL containers. We can use the compiler provided default
    //! implementation here.
    //!
    Field(const Field &) = default;
};


//!
//! @brief Chunked NeXus field
//!
//! This class is a descendent of NeXus Object and hdf5::node::ChunkedDataset.
//! It provides constructors to create a chunked field and checks the
//! NeXus naming convention at object creation time.
//!
class ChunkedField : public NeXusObject,
                     public hdf5::node::ChunkedDataset
{
  private:
    //!
    //! @brief construct a default chunk shape
    //!
    //! This static utility function is used to create a default chunk shape
    //! from an existing simple dataspace.
    //!
    //! @param space reference to the dataspace
    //! @return chunk shape for the datspace
    //!
    static hdf5::Dimensions default_chunk_shape(const hdf5::dataspace::Simple &space);

  public:
    //!
    //! @brief default constructor
    //!
    //! Required for STL containers. We use the compiler provided default
    //! implmentation.
    //!
    ChunkedField() = default;

    //!
    //! @brief copy constructor
    //!
    //! Required for STL containers and algorithms. Use the compiler provided
    //! default implementation.
    //!
    ChunkedField(const ChunkedField &) = default;

    //!
    //! @brief conversion constructor
    //!
    //! Constructs a ChunkedField from a general hdf5::node::Node instance.
    //!
    //! @param node reference to the original node
    //!
    ChunkedField(const hdf5::node::Node &node);

    //!
    //! @brief constructor
    //!
    //!
    //! @param parent reference to the parent group
    //! @param path reference to the new path of the field
    //! @param type reference to the data type of the field
    //! @param space reference to the data space of the field
    //! @param chunk_shape optional reference to the chunk shape of the field
    //! @param lcpl optional reference to a link creation property list
    //! @param dcpl optional reference to a dataset creation property list
    //! @param acpl optional reference to a dataset access property list
    //!
    ChunkedField(const hdf5::node::Group &parent,
                 const hdf5::Path &path,
                 const hdf5::datatype::Datatype &type,
                 const hdf5::dataspace::Simple &space,
                 const hdf5::Dimensions &chunk_shape = hdf5::Dimensions(),
                 const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
                 const hdf5::property::DatasetCreationList &dcpl = hdf5::property::DatasetCreationList(),
                 const hdf5::property::DatasetAccessList &acpl = hdf5::property::DatasetAccessList()
        );



};


} // namespace nexus
} // namespace io
} // namespace pni
