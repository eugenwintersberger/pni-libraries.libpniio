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
//
//  Created on: Jan 14, 2016
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../algorithm_test_fixture.hpp"

struct io_test_fixture : algorithm_test_fixture
{
    pni::io::nx::h5::nxobject o_scalar_attribute;
    pni::io::nx::h5::nxobject o_mdim_attribute;
    pni::io::nx::h5::nxobject o_scalar_field;
    pni::io::nx::h5::nxobject o_mdim_field;
    pni::io::nx::h5::nxattribute scalar_attribute;
    pni::io::nx::h5::nxattribute mdim_attribute;
    pni::io::nx::h5::nxfield scalar_field;
    pni::io::nx::h5::nxfield mdim_field;

    static const pni::core::shape_t shape; 

    
    io_test_fixture(const pni::core::string &fname);
    virtual ~io_test_fixture();
};
