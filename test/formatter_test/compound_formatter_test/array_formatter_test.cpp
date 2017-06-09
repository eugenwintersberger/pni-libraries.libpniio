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
//  Created on: Apr 28, 2015
//      Author: Eugen Wintersberger
//


#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/test/unit_test.hpp>
#include <pni/io/formatters.hpp>

using namespace pni::core;
using namespace pni::io;

struct array_formatter_test_fixture
{
    typedef array  input_type;
    typedef dynamic_array<int8> array_type;
    input_type     input;

    array_formatter_test_fixture():
        input(input_type(array_type::create(shape_t{4},
                                   array_type::storage_type{1,2,3,4})))
    {}
};

BOOST_FIXTURE_TEST_SUITE(array_formatter_test,array_formatter_test_fixture)


    BOOST_AUTO_TEST_CASE(test_default)
    {
        BOOST_CHECK_EQUAL(format(input),"+1 +2 +3 +4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_sep)
    {
        BOOST_CHECK_EQUAL(format(input,container_io_config(';')),"+1;+2;+3;+4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_start_stop)
    {
        BOOST_CHECK_EQUAL(format(input,container_io_config('(',')')),"(+1 +2 +3 +4)");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full_costum)
    {
        BOOST_CHECK_EQUAL(format(input,container_io_config('[',']',';')),"[+1;+2;+3;+4]");
    }

BOOST_AUTO_TEST_SUITE_END()
