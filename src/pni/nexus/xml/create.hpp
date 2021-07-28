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
// Created on: Dec 14, 2017
//
#pragma once

#include <boost/filesystem.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/windows.hpp>


namespace pni {
namespace nexus {
namespace xml {

//!
//! @brief create NeXus objects from an XML file
//!
//! Reads the content of an XML file and creates NeXus objects below a parent
//! object.
//!
//! @param parent reference to the parent object
//! @param xml_file reference to the path of the XML file
//!
PNINEXUS_EXPORT void create_from_file(const hdf5::node::Node &parent,const boost::filesystem::path &xml_file);


//!
//! @brief create NeXus objects from XML data
//!
//! Reads XML data from a string and creates NeXus objects from it below a
//! parent object.
//!
//! @param parent reference to the parent object
//! @param xml_data reference to the data string
//!
PNINEXUS_EXPORT void create_from_string(const hdf5::node::Node &parent,const std::string &xml_data);


} // namespace xml
} // namespace nexus
} // namespace pni
