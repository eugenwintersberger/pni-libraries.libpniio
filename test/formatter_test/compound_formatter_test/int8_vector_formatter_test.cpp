//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Feb 11, 2015
//      Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//               Jan Kotanski <jan.kotanski@desy.de>
//

#include <boost/test/included/unit_test.hpp>
#include <pni/types.hpp>
#include <pni/formatters.hpp>

using namespace pni;


struct int8_vector_formatter_fixture
{
    typedef int8                       element_type;
    typedef std::vector<element_type>  input_type;

    input_type     input;

    int8_vector_formatter_fixture():
        input(input_type{1,2,3,4})
    {}
};

BOOST_FIXTURE_TEST_SUITE(int8_vector_formatter_test,int8_vector_formatter_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        BOOST_CHECK(format(input) == "+1 +2 +3 +4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_sep)
    {
        container_io_config config(';');
        BOOST_CHECK(format(input,config) == "+1;+2;+3;+4");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_costum_start_stop)
    {
        container_io_config config('(',')');
        BOOST_CHECK(format(input,config) == "(+1 +2 +3 +4)");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full_costum)
    {
        container_io_config config('[',']',';');
        BOOST_CHECK(format(input,config) == "[+1;+2;+3;+4]");
    }

BOOST_AUTO_TEST_SUITE_END()
