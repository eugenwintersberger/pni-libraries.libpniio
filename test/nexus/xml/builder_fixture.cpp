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
// Created on: Dec 14, 2017
//

#include "builder_fixture.hpp"

BuilderFixture::BuilderFixture(const boost::filesystem::path &nexus_file,
                               const boost::filesystem::path &xml_file)
{
  using namespace pni::io;
  using pni::core::type_id_t;
  file = hdf5::file::create(nexus_file,
                            hdf5::file::AccessFlags::TRUNCATE);
  root_group = file.root();

  nexus::xml::Node n = nexus::xml::Node::from_file(xml_file);
  nexus::xml::ObjectBuilder builder(n);
  builder.build(root_group);


}

BuilderFixture::~BuilderFixture()
{}
