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
// Created on: Dec 11, 2017
//

#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus/xml/field_builder.hpp>
#include <pni/io/nexus/xml/dimensions.hpp>
#include <pni/io/nexus/xml/field_node.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/io/nexus/datatype_factory.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/types.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

hdf5::Dimensions FieldBuilder::dataset_shape() const
{
  return FieldNode::shape(node());
}

hdf5::Dimensions FieldBuilder::chunk_shape() const
{
  hdf5::Dimensions chunk_shape = FieldNode::chunk(node());

  if(chunk_shape.empty())
  {
    chunk_shape = dataset_shape();
    chunk_shape[0] = 1;

    // in the case of a 1D dataset
    if(chunk_shape.size() == 1)
      chunk_shape[0] == 1024*1024;
  }

  return chunk_shape;
}


hdf5::dataspace::Simple FieldBuilder::construct_dataspace() const
{
  using namespace pni::core;
  using namespace hdf5::dataspace;

  hdf5::Dimensions shape = dataset_shape();
  if(shape.empty())
    return Simple({1},{H5S_UNLIMITED});
  else
  {
    hdf5::Dimensions max_shape(shape.size(),H5S_UNLIMITED);
    return Simple(shape,max_shape);
  }
}

hdf5::property::DatasetCreationList FieldBuilder::construct_dcpl() const
{
  using namespace pni::core;
  using namespace hdf5::property;

  DatasetCreationList dcpl;

  //setting up the chunking
  dcpl.layout(DatasetLayout::CHUNKED);
  dcpl.chunk(chunk_shape());

  //setting up filters i required
  auto strategy = node().get_child_optional("strategy");
  if(strategy)
  {
    Node node = strategy.get();
    bool use_compression = false;
    bool use_shuffle     = false;
    long compression_rate = 0;

    if(node.has_attribute("compression"))
      use_compression = FieldNode::data_from_xml<bool_t>(
          node.attribute("compression"));

    if(node.has_attribute("shuffle"))
      use_shuffle = FieldNode::data_from_xml<bool_t>(
          node.attribute("shuffle"));

    if(node.has_attribute("rate"))
      compression_rate = FieldNode::data_from_xml<size_t>(
          node.attribute("rate"));

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

  return dcpl;
}

hdf5::datatype::Datatype FieldBuilder::construct_datatype() const
{
  return DatatypeFactory::create(FieldNode::type_id(node()));
}


FieldBuilder::FieldBuilder(const Node &xml_node):
    ObjectBuilder(xml_node)
{}

template<typename T>
std::vector<T> read_data(const Node &xml_node)
{

}


void FieldBuilder::build(const hdf5::node::Node &parent) const
{
  using namespace hdf5;
  using namespace pni::core;
  //construct the field object
  std::string    field_name  = FieldNode::name(node());

  property::LinkCreationList lcpl;
  hdf5::property::DatasetCreationList dcpl = construct_dcpl();
  hdf5::dataspace::Simple dataspace =construct_dataspace();
  hdf5::datatype::Datatype datatype = construct_datatype();

  hdf5::node::Dataset dataset(parent,field_name,datatype,dataspace,lcpl,dcpl);

  std::string    long_name   = FieldNode::long_name(node());
  if(!long_name.empty())
  {
    dataset.attributes.create<std::string>("long_name").write(long_name);
  }

  std::string    units       = FieldNode::unit(node());
  if(!units.empty())
  {
    dataset.attributes.create<std::string>("units").write(units);
  }

  //need to handle data if available
  std::string data = DataNode::read(node());
  if(!data.empty())
  {
    switch(IONode::type_id(node()))
    {
      case type_id_t::UINT8:
        dataset.write(node().data<std::vector<uint8>>());
        break;
      case type_id_t::INT8:
        dataset.write(node().data<std::vector<int8>>());
        break;
      case type_id_t::UINT16:
        dataset.write(node().data<std::vector<uint16>>());
        break;
      case type_id_t::INT16:
        dataset.write(node().data<std::vector<int16>>());
        break;
      case type_id_t::UINT32:
        dataset.write(node().data<std::vector<uint32>>());
        break;
      case type_id_t::INT32:
        dataset.write(node().data<std::vector<int32>>());
        break;
      case type_id_t::UINT64:
        dataset.write(node().data<std::vector<uint64>>());
        break;
      case type_id_t::INT64:
        dataset.write(node().data<std::vector<int64>>());
        break;
      case type_id_t::FLOAT32:
        dataset.write(node().data<std::vector<float32>>());
        break;
      case type_id_t::FLOAT64:
        dataset.write(node().data<std::vector<float64>>());
        break;
      case type_id_t::FLOAT128:
        dataset.write(node().data<std::vector<float128>>());
        break;
      case type_id_t::STRING:
        dataset.write(node().data<std::vector<std::string>>());
        break;
      default:
      {
        std::stringstream ss;
        ss<<"Unsupported datat type: "<<IONode::type_id(node());
        throw std::runtime_error(ss.str());
      }
    }
  }

  //process remaining optional attributes
  ObjectBuilder builder(node());
  builder.build(dataset);
}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
