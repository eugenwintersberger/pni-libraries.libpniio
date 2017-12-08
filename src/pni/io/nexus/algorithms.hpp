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
// Created on: Dec 8, 2017
//
#pragma once

#include <pni/io/nexus/predicates.hpp>
#include <pni/io/nexus/containers.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief search for nodes satisfying a predicate
//!
//! @param base reference to the group where to start the search
//! @param predicate the predicate to select a node
//! @param recursive if true perform a recursive search
//! @return an instance of NodeList with all nodes satisfying the predicate
//!
NodeList search(const hdf5::node::Group &base,
                const NodePredicate &predicate,
                bool recursive=false);


} // namespace nexus
} // namespace io
} // namespace pni
