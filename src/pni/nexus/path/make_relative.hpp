//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/types.hpp>
#include <pni/nexus/path/path.hpp>
#include <pni/windows.hpp>

namespace pni{
namespace nexus{

//!
//! @brief make a relative path
//!
//! Take a given path and make it relative with respect to a particular
//! other path (typically the path of a parent object).
//!
//! @code
//! nexus::Path entry = nexus::Path::from_string("/:NXentry");
//! nexus::Path det   = nexus::Path::from_string("/:NXentry/:NXinstrument/:NXdetector");
//!
//! nexus::Path det_rel = nexus::make_relative(entry,det);
//! std::cout<<det_rel<<std::endl;
//! // output: :NXinstrument/:NXdetector
//! @endcode
//!
//! For this procedure to work both paths must be absolute as we need a
//! common starting point (which would be the root group). In the case that
//! Both
//!
//! * both paths must be absolute (as we need a common starting point which
//!   would be the root group
//! * if boths paths have a file section it must be equal
//! * if
//!
//! @param parent_path reference to the path to which we want to create a
//!                    relative one
//! @param orig_path reference to the original path
//!
//! @return new instance of `Path` relative to `parent_path`
//!
//!
PNINEXUS_EXPORT Path make_relative(const Path &parent_path,const Path &orig_path);


} // namespace nexus
} // namespace pni
