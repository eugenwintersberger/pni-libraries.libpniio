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
//  Created on: Apr 29, 2015
//      Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//               Jan Kotanski <jan.kotanski@desy.de>
//

#include <pni/io/formatters.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <boost/test/unit_test.hpp>

using namespace pni::core;
using namespace pni::io;

struct mdarray_formatter_test_fixture
{
    typedef dynamic_array<int16>  input_type;
    input_type     input;

    mdarray_formatter_test_fixture():
        input(input_type::create(shape_t{4},
                                 input_type::storage_type{1,2,3,4}))
    {}
};


BOOST_FIXTURE_TEST_SUITE(mdarray_formatter_test,mdarray_formatter_test_fixture)

    BOOST_AUTO_TEST_CASE(test_default)
    {
        BOOST_CHECK(format(input) == "+1 +2 +3 +4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_sep)
    {
        BOOST_CHECK(format(input,container_io_config(';')) == "+1;+2;+3;+4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_start_stop)
    {
        BOOST_CHECK(format(input,container_io_config('(',')')) == "(+1 +2 +3 +4)");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full_costum)
    {

        BOOST_CHECK(format(input,container_io_config('[',']',';')) == "[+1;+2;+3;+4]");
    }

BOOST_AUTO_TEST_SUITE_END()
