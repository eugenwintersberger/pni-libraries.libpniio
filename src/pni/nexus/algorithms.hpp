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
// Created on: Dec 8, 2017
//
#pragma once

#include <pni/nexus/predicates.hpp>
#include <pni/nexus/containers.hpp>
#include <pni/types.hpp>
#include <pni/windows.hpp>

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
PNINEXUS_EXPORT NodeList search(const hdf5::node::Group &base,
                             const NodePredicate &predicate,
                             bool recursive=false);

//!
//! @brief return the type_id of a dataset
//!
//! If the underlying data type is unkonwn NONE is returned.
//!
//! @throws std::runtime_error in case of a failure
//! @param dataset reference to the dataset
//! @return type_id_t enumeration
//!
PNINEXUS_EXPORT pni::type_id_t get_type_id(const hdf5::node::Dataset &dataset);

//!
//! @brief return the type_id of an attribute
//!
//! If the underlying data type is unkonwn NONE is returned.
//!
//! @throws std::runtime_error in case of a failure
//! @param attribute reference to the attribute
//! @return type_id_t enumeration
//!
PNINEXUS_EXPORT pni::type_id_t get_type_id(const hdf5::attribute::Attribute &attribute);

//!
//! @brief get the current dimensions of an attribute
//!
//! If the attribute is scalar {1} is returned. Otherwise the current dimensions of
//! the attribute are returned.
//!
//! @throws std::runtime_error in case of a failure
//! @param attribute reference to the attribute
//! @return instance of hdf5::Dimensions with the current dimensions
//!
PNINEXUS_EXPORT hdf5::Dimensions get_dimensions(const hdf5::attribute::Attribute &attribute);

//!
//! @brief get the current dimensions of a dataset
//!
//! If the dataset is scalar {1} is returned. Otherwise the current dimensions of
//! the dataset are returned.
//!
//! @throws std::runtime_error in case of a failure
//! @param dataset reference to the dataset
//! @return instance of hdf5::Dimensions with the current dimensions
//!
PNINEXUS_EXPORT hdf5::Dimensions get_dimensions(const hdf5::node::Dataset &dataset);


} // namespace nexus
} // namespace io
} // namespace pni
