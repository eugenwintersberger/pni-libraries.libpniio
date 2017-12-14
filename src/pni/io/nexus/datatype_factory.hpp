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
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/core/types.hpp>

namespace pni {
namespace io {
namespace nexus {


//!
//! @brief creates HDF5 datatypes from type_id_t values
//!
//! This service class provides a static method constructing HDF5 datatypes
//! from type_id_t enumerations.
//!
class DatatypeFactory
{
  public:

    static hdf5::datatype::Datatype create(pni::core::type_id_t tid);
};


} // namespace nexus
} // namespace io
} // namespace pni
