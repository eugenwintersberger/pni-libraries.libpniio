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

#include "io_test_fixture.hpp"
#include <pni/io/nx/algorithms/create_attribute.hpp>
#include <pni/io/nx/algorithms/create_field.hpp>
#include <pni/io/nx/algorithms/as_field.hpp>
#include <pni/io/nx/algorithms/as_attribute.hpp>

using namespace pni::core;
using namespace pni::io::nx;

const shape_t io_test_fixture::shape = {3,4};

io_test_fixture::io_test_fixture(const string &fname):
    algorithm_test_fixture(fname),
    o_scalar_attribute(create_attribute<string>(o_group,"scalar_attr")),
    o_mdim_attribute(create_attribute<uint16>(o_group,"mdim_attr",shape)),
    o_scalar_field(create_field<float32>(o_group,"scalar_field")),
    o_mdim_field(create_field<float64>(o_group,"mdim_field",shape)),
    scalar_attribute(as_attribute(o_scalar_attribute)),
    mdim_attribute(as_attribute(o_mdim_attribute)),
    scalar_field(as_field(o_scalar_field)),
    mdim_field(as_field(o_mdim_field))
{}

io_test_fixture::~io_test_fixture()
{
    
    close(o_scalar_attribute);
    close(o_mdim_attribute);
    close(o_scalar_field);
    close(o_mdim_field);
    close(scalar_attribute);
    close(mdim_attribute);
    close(scalar_field);
    close(mdim_field);
}
