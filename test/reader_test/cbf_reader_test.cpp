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
//************************************************************************
//
//  Created on: Sep 17, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include <boost/test/unit_test.hpp>
#include <pni/io/cbf/cbf_reader.hpp>

using namespace pni::core;
using namespace pni::io;

BOOST_AUTO_TEST_SUITE(cbf_reader_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_header)
    {
        BOOST_CHECK_THROW(cbf_reader("ii8.tiff"),file_error);

    }

BOOST_AUTO_TEST_SUITE_END()

