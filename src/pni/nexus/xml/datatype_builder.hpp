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
#pragma once

#include <pni/nexus/xml/node.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/windows.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

//!
//! @brief builds datatypes from XML nodes
//!
//! This class provides a function to construct an HDF5 datatype from the
//! `type` attribute of an XML node.
//!
class PNINEXUS_EXPORT DatatypeBuilder
{
  private:
    Node node_;
  public:
    //!
    //! @brief default constructor
    //!
    //! Use compiler provided default implementation here.
    //!
    DatatypeBuilder() = default;

    //!
    //! @brief copy constructor
    //!
    //! Use compiler provided default implementation here
    //!
    DatatypeBuilder(const DatatypeBuilder &) = default;

    //!
    //! @brief constructor
    //!
    //! @param node reference to the node
    //!
    explicit DatatypeBuilder(const Node &node) noexcept;

    //!
    //! @brief create a new datatype
    //!
    //! This function returns the new datatype. If the datatype
    //! is not supported an exception will be thrown. Furthermore, an
    //! exception is thrown if the node does not have a `type` attribute.
    //!
    //! @throws std::runtime_error in case of an unsupported data type
    //! @return new instance of an HDF5 datatype
    //!
    hdf5::datatype::Datatype build() const;
};


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
