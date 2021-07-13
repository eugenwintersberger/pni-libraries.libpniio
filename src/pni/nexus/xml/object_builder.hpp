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

#include <pni/nexus/object_builder.hpp>
#include <pni/nexus/xml/node.hpp>
#include <pni/windows.hpp>
#include <memory>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

class PNIIO_EXPORT ObjectBuilder : public pni::io::nexus::ObjectBuilder
{
  private:
    Node xml_node_;
  public:
    using UniquePointer = std::unique_ptr<ObjectBuilder>;
    ObjectBuilder() = default;
    ObjectBuilder(const Node &xml_node);
    ObjectBuilder(const ObjectBuilder &) = default;
    virtual ~ObjectBuilder();

    const Node &node() const noexcept;

    virtual void build(const hdf5::node::Node &parent) const;

};


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
