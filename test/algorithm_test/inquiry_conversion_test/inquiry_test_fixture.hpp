//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/algorithms/close.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../../base_fixture.hpp"

struct inquiry_test_fixture : base_fixture
{
    pni::io::nx::h5::nxobject group;
    pni::io::nx::h5::nxobject attribute;
    pni::io::nx::h5::nxobject field;

    inquiry_test_fixture(const pni::core::string &filename);

    virtual ~inquiry_test_fixture();
};


