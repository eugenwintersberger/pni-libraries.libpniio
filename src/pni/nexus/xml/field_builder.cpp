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
// Created on: Dec 11, 2017
//

#include <h5cpp/hdf5.hpp>
#include <pni/nexus/xml/field_builder.hpp>
#include <pni/nexus/xml/node.hpp>
#include <pni/arrays.hpp>
#include <pni/types.hpp>

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

hdf5::dataspace::Simple FieldBuilder::construct_empty_dataspace() const
{
  hdf5::dataspace::Simple space({0},{1});
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
    dcpl_builder_(xml_node),
    writer_(xml_node)
{}

template<typename T>
std::vector<T> read_data(const Node &xml_node)
{

}


void FieldBuilder::build(const hdf5::node::Node &parent) const
{
  using namespace hdf5;
  using namespace pni;
  //construct the field object
  std::string    field_name  = node().name();

  try{
    const hdf5::node::Group & parent_group = dynamic_cast<const hdf5::node::Group &>(parent);
    if(parent_group.nodes.exists(field_name)){
      std::stringstream ss;
      ss << "The '" << field_name << "' field at '" << parent.link().path() << "' already exists";
      throw std::runtime_error(ss.str());
    }
  }
  catch(const std::bad_cast&){
    std::stringstream ss;
    ss << "The '" << parent.link().path() << "' node is not of the Group type";
    throw std::runtime_error(ss.str());
  }

  property::LinkCreationList lcpl;
  hdf5::property::DatasetCreationList dcpl;
  hdf5::datatype::Datatype datatype = datatype_builder_.build();
  hdf5::dataspace::Dataspace dataspace = hdf5::dataspace::Scalar();

  bool is_string = ((datatype.get_class() == hdf5::datatype::Class::VARLENGTH)
		    ||
		    (datatype.get_class() == hdf5::datatype::Class::STRING));

  auto has_dimension_node = node().get_child_optional("dimensions");
  if( (!is_string) || has_dimension_node)
  {
    dcpl = dcpl_builder_.build();
    if(has_dimension_node){
      dataspace = construct_dataspace();
    }
    else {
      dataspace = construct_empty_dataspace();
    }
  }
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
  writer_.write(dataset);


  //process remaining optional attributes
  ObjectBuilder builder(node());
  builder.build(dataset);
}

} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
