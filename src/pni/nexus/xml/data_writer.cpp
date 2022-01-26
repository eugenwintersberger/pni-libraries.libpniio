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
// Created on: Dec 13, 2017
//
#include <pni/nexus/xml/data_writer.hpp>
#include <pni/parsers.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni {
namespace nexus {
namespace xml {

template<typename T,typename OBJ>
void write_data(const std::string &data,const OBJ &object)
{
  pni::parser<std::vector<T>> parser;
  object.write(parser(data));
}

template<typename OBJ>
void write_string_data(const std::string &data,const OBJ &object)
{
  object.write(data);
}

template<typename OBJ>
void write_bool_data(const std::string &data,const OBJ &object)
{
  pni::parser<std::vector<hdf5::datatype::EBool>> parser;
  object.write(parser(data));
}

template<typename OBJ>
void extend_simple_scalar(const OBJ &){
}

void extend_simple_scalar(const hdf5::node::Dataset &object){
  auto dataspace = object.dataspace();
  if(dataspace.size() == 0){
    hdf5::Dimensions chunk = object.creation_list().chunk();
    if(chunk.size() == 1 && chunk[0] == 1){
      object.extent(0, 1);
    }
  }
}

template<typename OBJ>
void write_data(const Node &node,const OBJ &object)
{
  using namespace pni;
  type_id_t type_id = type_id_from_str(node.attribute("type").str_data());
  std::string data = node.str_data();

  if(data.empty()) return;
  extend_simple_scalar(object);

  switch(type_id)
  {
    case type_id_t::UInt8: write_data<uint8>(data,object); break;
    case type_id_t::Int8:  write_data<int8>(data,object);  break;
    case type_id_t::UInt16: write_data<uint16>(data,object); break;
    case type_id_t::Int16: write_data<int16>(data,object);   break;
    case type_id_t::UInt32: write_data<uint32>(data,object); break;
    case type_id_t::Int32:  write_data<int32>(data,object);  break;
    case type_id_t::UInt64: write_data<uint64>(data,object); break;
    case type_id_t::Int64:  write_data<int64>(data,object);  break;
    case type_id_t::Float32: write_data<float32>(data,object); break;
    case type_id_t::Float64: write_data<float64>(data,object); break;
    case type_id_t::Float128: write_data<float128>(data,object); break;
    case type_id_t::String:   write_string_data(data,object); break;
    case type_id_t::EBool:   write_bool_data(data,object); break;
    default:
    {
      std::stringstream ss;
      ss<<"Unsupported datat type: "<<type_id;
      throw std::runtime_error(ss.str());
    }
  }
}



DataWriter::DataWriter(const Node &node):
    node_(node)
{}

void DataWriter::write(const hdf5::node::Dataset &dataset) const
{
  write_data(node_,dataset);
}

void DataWriter::write(const hdf5::attribute::Attribute &attribute) const
{
  write_data(node_,attribute);
}

} // namespace xml
} // namespace nexus
} // namespace pni
