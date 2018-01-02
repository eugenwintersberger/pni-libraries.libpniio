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

#include <string>
#include <h5cpp/hdf5.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief base class for NeXus objects
//!
//! This class does nothing but checking whether
class NeXusObject
{
  public:
    NeXusObject() = default;
    NeXusObject(const hdf5::Path &path);
    NeXusObject(const NeXusObject &) = default;
};

} // namespace nexus
} // namespace io
} // namespace pni
