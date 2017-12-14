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
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus/xml/field_builder.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <pni/io/nexus/xml/object_builder.hpp>
#include <pni/io/nexus/algorithms.hpp>
#include <boost/filesystem.hpp>

struct BuilderFixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;

    BuilderFixture(const boost::filesystem::path &nexus_file,
                   const boost::filesystem::path &xml_file);

    virtual ~BuilderFixture();
};
