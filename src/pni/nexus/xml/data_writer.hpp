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

#include <pni/arrays.hpp>
#include <pni/types.hpp>
#include <pni/nexus/xml/node.hpp>
#include <h5cpp/hdf5.hpp>

namespace pni {
namespace nexus {
namespace xml {

class DataWriter
{
  private:
    Node node_;
  public:
    DataWriter() = default;
    DataWriter(const DataWriter &)=default;
    DataWriter(const Node &node);

    void write(const hdf5::node::Dataset &dataset) const ;
    void write(const hdf5::attribute::Attribute &attribute) const;
};


} // namespace xml
} // namespace nexus
} // namespace pni
