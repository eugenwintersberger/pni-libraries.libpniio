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

#include <pni/io/nexus/xml/object_builder.hpp>
#include <pni/io/nexus/xml/dataspace_builder.hpp>
#include <pni/io/nexus/xml/datatype_builder.hpp>
#include <pni/io/nexus/xml/dataset_creation_list_builder.hpp>
#include <pni/io/nexus/xml/data_writer.hpp>

namespace pni {
namespace io {
namespace nexus {
namespace xml {

class PNIIO_EXPORT FieldBuilder : public ObjectBuilder
{
  private:
    hdf5::dataspace::Simple construct_dataspace() const;

    DataspaceBuilder dataspace_builder_;
    DatatypeBuilder  datatype_builder_;
    DatasetCreationListBuilder dcpl_builder_;
    DataWriter writer_;

  public:
    FieldBuilder() = default;
    FieldBuilder(const Node &xml_node);
    FieldBuilder(const FieldBuilder &)=default;

    virtual void build(const hdf5::node::Node &parent) const;
};


} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
