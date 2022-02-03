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
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//

#include <boost/test/included/unit_test.hpp>
#include <pni/formatters/scalar_format.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(bool_formatter_test)

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test)
    {
        BOOST_CHECK(format(bool_t(true)) == "true");
        BOOST_CHECK(format(bool_t(false)) == "false");
        BOOST_CHECK(format(hdf5::datatype::EBool(true)) == "true");
        BOOST_CHECK(format(hdf5::datatype::EBool(false)) == "false");
    }


BOOST_AUTO_TEST_SUITE_END()


