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
//      Authors:
//              Eugen Wintersberger <eugen.wintersberger@desy.de>
//              Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Dec 8, 2017
//

#include <pni/nexus/algorithms.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <algorithm>
#include <functional>



namespace pni {
namespace nexus {

template<typename ITERT>
NodeList search_(ITERT begin,ITERT end,
                                 const NodePredicate &predicate)
{
  pni::nexus::NodeList result;
  std::copy_if(begin,end,std::back_inserter(result),std::cref(predicate));
  return result;
}

NodeList search(const hdf5::node::Group &base,
                const NodePredicate &predicate,
                bool recursive)
{
  using hdf5::node::RecursiveNodeIterator;
  using hdf5::node::NodeIterator;

  if(recursive)
  {
    return search_(RecursiveNodeIterator::begin(base),
                   RecursiveNodeIterator::end(base),
                   predicate);
  }
  else
  {
    return search_(NodeIterator::begin(base),
                   NodeIterator::end(base),
                   predicate);
  }
}

pni::type_id_t get_type_id(const hdf5::datatype::Datatype &datatype)
{
  using hdf5::datatype::create;
  using namespace pni;
  if(datatype == create<uint8>())
    return type_id_t::UInt8;
  else if(datatype==create<int8>())
    return type_id_t::Int8;
  else if(datatype==create<uint16>())
    return type_id_t::UInt16;
  else if(datatype==create<int16>())
    return type_id_t::Int16;
  else if(datatype==create<uint32>())
    return type_id_t::UInt32;
  else if(datatype==create<int32>())
    return type_id_t::Int32;
  else if(datatype==create<uint64>())
    return type_id_t::UInt64;
  else if(datatype==create<int64>())
    return type_id_t::Int64;
  else if(datatype==create<float32>())
    return type_id_t::Float32;
  else if(datatype==create<float64>())
    return type_id_t::Float64;
  else if(datatype==create<float128>())
    return type_id_t::Float128;
  else if(datatype.get_class() == hdf5::datatype::Class::String)
    return type_id_t::String;
  else if(datatype.get_class() == hdf5::datatype::Class::Enum
          && hdf5::datatype::is_bool(hdf5::datatype::Enum(datatype)))
    return type_id_t::EBool;
  else
    return type_id_t::None;
}

pni::type_id_t get_type_id(const hdf5::node::Dataset &dataset)
{
  return get_type_id(dataset.datatype());
}

pni::type_id_t get_type_id(const hdf5::attribute::Attribute &attribute)
{
  return get_type_id(attribute.datatype());
}

hdf5::Dimensions get_dimensions(const hdf5::dataspace::Dataspace &dataspace)
{
  if(dataspace.type()==hdf5::dataspace::Type::Scalar)
  {
    return hdf5::Dimensions{1};
  }
  else
  {
    return hdf5::dataspace::Simple(dataspace).current_dimensions();
  }
}

hdf5::Dimensions get_dimensions(const hdf5::attribute::Attribute &attribute)
{
  return get_dimensions(attribute.dataspace());
}

hdf5::Dimensions get_dimensions(const hdf5::node::Dataset &dataset)
{
  return get_dimensions(dataset.dataspace());
}


} // namespace nexus
} // namespace pni
