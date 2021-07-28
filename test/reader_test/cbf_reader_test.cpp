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
//************************************************************************
//
//  Created on: Sep 17, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include <boost/test/unit_test.hpp>
#include <pni/cbf/cbf_reader.hpp>
#include <pni/image_info.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(cbf_reader_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_header)
    {
        BOOST_CHECK_THROW(cbf_reader("ii8.tiff"),file_error);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_laos)
    {
        cbf_reader reader("LAOS3_05461.cbf");
        
        BOOST_CHECK(reader.nimages() == 1);

        image_info info = reader.info(0);
        BOOST_CHECK(info.ny() == 487);
        BOOST_CHECK(info.nx() == 195);
        BOOST_CHECK(info.bit_per_pixel() == 32);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo = info.get_channel(0);
        BOOST_CHECK(cinfo.bits() == 32);
        BOOST_CHECK(cinfo.type_id() == type_id_t::INT32);

    }

BOOST_AUTO_TEST_SUITE_END()

