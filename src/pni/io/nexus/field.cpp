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

#include <pni/io/nexus/field.hpp>

namespace pni {
namespace io {
namespace nexus {

Field::Field(const hdf5::node::Group &parent,
             const hdf5::Path &path,
             const hdf5::datatype::Datatype &type,
             const hdf5::dataspace::Dataspace &space,
             const hdf5::property::LinkCreationList &lcpl,
             const hdf5::property::DatasetCreationList &dcpl,
             const hdf5::property::DatasetAccessList &acpl):
                 NeXusObject(path),
                 hdf5::node::Dataset(parent,path,type,space,lcpl,dcpl,acpl)
{

}

Field::Field(const hdf5::node::Node &node):
    NeXusObject(),
    hdf5::node::Dataset(node)
{}

ChunkedField::ChunkedField(const hdf5::node::Node &node):
    NeXusObject(),
    hdf5::node::ChunkedDataset()
{
  *this = hdf5::node::Dataset(node);
}

hdf5::Dimensions ChunkedField::default_chunk_shape(const hdf5::dataspace::Simple &space)
{
  hdf5::Dimensions chunk_dims = space.current_dimensions();

  if(chunk_dims.size()==1)
  {
    chunk_dims.front() = 1024*1024;
  }
  else
  {
    chunk_dims.front() = 1;
  }

  return chunk_dims;
}

ChunkedField::ChunkedField(const hdf5::node::Group &parent,
                           const hdf5::Path &path,
                           const hdf5::datatype::Datatype &type,
                           const hdf5::dataspace::Simple &space,
                           const hdf5::Dimensions &chunk_shape,
                           const hdf5::property::LinkCreationList &lcpl,
                           const hdf5::property::DatasetCreationList &dcpl,
                           const hdf5::property::DatasetAccessList &acpl):
                               NeXusObject(path),
                               hdf5::node::ChunkedDataset()
{
  if(chunk_shape.empty())
    *this = hdf5::node::ChunkedDataset(parent,path,type,space,
                                       default_chunk_shape(space),
                                       lcpl,dcpl,acpl);
  else
    *this = hdf5::node::ChunkedDataset(parent,path,type,space,chunk_shape,lcpl,dcpl,acpl);

}


} // namespace nexus
} // namespace io
} // namespace pni
