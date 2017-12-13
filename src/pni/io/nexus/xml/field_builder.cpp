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
#include <pni/io/nexus/xml/field_node.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/types.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {





hdf5::dataspace::Simple FieldBuilder::construct_dataspace() const
{
  hdf5::dataspace::Simple space = dataspace_builder_.build();
  hdf5::Dimensions current_dimensions = space.current_dimensions();
  hdf5::Dimensions max_dimensions(current_dimensions);
  max_dimensions.front() = H5S_UNLIMITED;
  space.dimensions(current_dimensions,max_dimensions);
  return space;
}


FieldBuilder::FieldBuilder(const Node &xml_node):
    ObjectBuilder(xml_node),
    dataspace_builder_(xml_node),
    datatype_builder_(xml_node),
    dcpl_builder_(xml_node)
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
  std::string    field_name  = node().name();

  property::LinkCreationList lcpl;
  hdf5::property::DatasetCreationList dcpl = dcpl_builder_.build();
  hdf5::dataspace::Simple dataspace = construct_dataspace();
  hdf5::datatype::Datatype datatype = datatype_builder_.build();

  hdf5::node::Dataset dataset(parent,field_name,datatype,dataspace,lcpl,dcpl);

  if(node().has_attribute("long_name"))
  {
    dataset.attributes.create<std::string>("long_name")
        .write(node().attribute("long_name").str_data());
  }

  if(node().has_attribute("units"))
  {
    dataset.attributes.create<std::string>("units").
        write(node().attribute("units").str_data());
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
