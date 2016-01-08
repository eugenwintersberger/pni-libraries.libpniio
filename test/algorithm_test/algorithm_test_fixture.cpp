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

#include "algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

algorithm_test_fixture::algorithm_test_fixture(const string &filename):
    base_fixture(filename),
    group(root),
    attribute(root.attributes["NX_class"]),
    field(root.create_field<uint32>("data")),
    o_group(group),
    o_attribute(attribute),
    o_field(field)
{}

algorithm_test_fixture::~algorithm_test_fixture()
{
    close(group);
    close(attribute);
    close(field);
    close(o_group);
    close(o_attribute);
    close(o_field);
}
