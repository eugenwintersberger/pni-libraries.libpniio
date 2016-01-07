//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
#pragma once

#include "nxfield_test_fixture.hpp"

struct nxattribute_test_fixture : nxfield_test_fixture
{
    pni::io::nx::h5::nxgroup group;
    pni::io::nx::h5::nxfield field;

    nxattribute_test_fixture(const pni::core::string &filename):
        nxfield_test_fixture(filename),
        group(root.create_group("test_group")),
        field(root.create_field<pni::core::float64>("test_field",default_shape))
    {}

    ~nxattribute_test_fixture()
    {
        group.close();
        field.close();
    }

    void get_parent(pni::io::nx::h5::nxgroup &parent);
    void get_parent(pni::io::nx::h5::nxfield &parent);
};
