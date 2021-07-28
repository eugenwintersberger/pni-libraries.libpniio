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

#include <pni/nexus/datatype_factory.hpp>
#include <sstream>
#include <stdexcept>

namespace pni {
namespace nexus {

hdf5::datatype::Datatype DatatypeFactory::create(pni::type_id_t tid)
{
  using namespace pni;
  switch(tid)
  {
    case type_id_t::UINT8: return hdf5::datatype::create<uint8>();
    case type_id_t::UINT16: return hdf5::datatype::create<uint16>();
    case type_id_t::UINT32: return hdf5::datatype::create<uint32>();
    case type_id_t::UINT64: return hdf5::datatype::create<uint64>();
    case type_id_t::INT8: return hdf5::datatype::create<int8>();
    case type_id_t::INT16: return hdf5::datatype::create<int16>();
    case type_id_t::INT32: return hdf5::datatype::create<int32>();
    case type_id_t::INT64: return hdf5::datatype::create<int64>();
    case type_id_t::FLOAT32: return hdf5::datatype::create<float32>();
    case type_id_t::FLOAT64: return hdf5::datatype::create<float64>();
    case type_id_t::FLOAT128: return hdf5::datatype::create<float128>();
    case type_id_t::STRING: return hdf5::datatype::create<std::string>();
    default:
    {
      std::stringstream ss;
      ss<<"Failure to construct HDF5 datatype from ID: "<<tid<<"!";
      throw std::runtime_error(ss.str());
    }

  }
}


} // namespace nexus
} // namespace pni
