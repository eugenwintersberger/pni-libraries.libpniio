//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 10, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <pni/nexus/path/path.hpp>
#include <pni/windows.hpp>
#include <utility>


namespace pni{
namespace io{
namespace nexus{

//add here an additional namespace to avoid namespace polution from the boost
//spirit framework.
namespace parsers{

//------------------------------------------------------------------------
//!
//! @brief parser string to path
//!
//! Parse a string input and generate a path instance from it.
//!
//! @throws parser_error in case of a parser problem
//!
//! @param input string from which to construct the path
//! @return Path instance
//!
PNINEXUS_EXPORT Path parse_path(const pni::string &input);

} // namespace parsers

} // namespace nexus
} // namespace io
} // namespace pni
