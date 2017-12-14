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
// Created on: Dec 13, 2017
//
#include <pni/io/nexus/xml/dataset_creation_list_builder.hpp>
#include <pni/io/nexus/xml/dimension_node_handler.hpp>
#include <pni/io/parsers.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

DatasetCreationListBuilder::DatasetCreationListBuilder(const Node &node):
    node_(node),
    dataspace_builder_(node)
{}

void DatasetCreationListBuilder::set_chunking(hdf5::property::DatasetCreationList &dcpl) const
{
  dcpl.layout(hdf5::property::DatasetLayout::CHUNKED);

  //set the default chunk layout
  hdf5::Dimensions chunk = dataspace_builder_.build().current_dimensions();
  if(chunk.size()==1)
    chunk.front() = 1024*1024;
  else
    chunk.front() = 1;

  auto has_chunk_node = node_.get_child_optional("chunk");
  if(has_chunk_node)
  {
    Node chunk_node = has_chunk_node.get();
    hdf5::Dimensions chunk = DimensionNodeHandler::dimensions(chunk_node);
  }

  dcpl.chunk(chunk);

}

void DatasetCreationListBuilder::set_compression(hdf5::property::DatasetCreationList &dcpl) const
{
  //setting up filters i required
  auto has_strategy_node = node_.get_child_optional("strategy");
  if(has_strategy_node)
  {
    Node node = has_strategy_node.get();

    bool use_compression = false;
    bool use_shuffle     = false;
    long compression_rate = 0;

    if(node.has_attribute("compression"))
      use_compression = node.attribute("compression").data<pni::core::bool_t>();

    if(node.has_attribute("shuffle"))
      use_shuffle = node.attribute("shuffle").data<pni::core::bool_t>();

    if(node.has_attribute("rate"))
      compression_rate = node.attribute("rate").data<size_t>();

    if(use_compression)
    {
      if(use_shuffle)
      {
        hdf5::filter::Shuffle shuffle;
        shuffle(dcpl);
      }

      hdf5::filter::Deflate deflate(compression_rate);
      deflate(dcpl);
    }
  }
}

hdf5::property::DatasetCreationList DatasetCreationListBuilder::build() const
{
  using hdf5::property::DatasetCreationList;

  DatasetCreationList dcpl;
  set_chunking(dcpl);
  set_compression(dcpl);

  return dcpl;
}


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
