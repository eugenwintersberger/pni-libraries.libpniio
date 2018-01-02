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

class Field : public NeXusObject,
              public hdf5::node::Dataset
{
  public:
    Field() = default;
    Field(const hdf5::node::Group &parent,
          const hdf5::Path &path,
          const hdf5::datatype::Datatype &type,
          const hdf5::dataspace::Dataspace &space,
          const hdf5::property::LinkCreationList &lcpl = hdf5::property::LinkCreationList(),
          const hdf5::property::DatasetCreationList &dcpl = hdf5::property::DatasetCreationList(),
          const hdf5::property::DatasetAccessList &acpl = hdf5::property::DatasetAccessList()
          );
    Field(const hdf5::node::Node &node);
    Field(const Field &field) = default;
};

class ChunkedField : public NeXusObject,
                     public hdf5::node::ChunkedDataset
{
  private:
    static hdf5::Dimensions default_chunk_shape(const hdf5::dataspace::Simple &space);

  public:
    ChunkedField() = default;
    ChunkedField(const ChunkedField &) = default;
    ChunkedField(const hdf5::node::Node &node);
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
