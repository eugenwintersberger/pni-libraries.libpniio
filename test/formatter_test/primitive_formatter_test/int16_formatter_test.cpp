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
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/types.hpp>
#include <pni/formatters/scalar_format.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(int16_formatter_test)

    BOOST_AUTO_TEST_CASE(test)
    {
        typedef int16 input_type;
        BOOST_CHECK(format(input_type(12)) == "+12");
        BOOST_CHECK(format(input_type(-100)) == "-100");
        BOOST_CHECK(format(input_type(0)) == "+0");
        BOOST_CHECK(format(input_type(32767)) == "+32767");
        BOOST_CHECK(format(input_type(-32768)) == "-32768");
    }

BOOST_AUTO_TEST_SUITE_END()
