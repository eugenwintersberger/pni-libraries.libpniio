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
//  Created on: Jun 26, 2017
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#include "../boost_unit_test.hpp"
#include <vector>
#include <pni/types.hpp>
#include <pni/tiff/tiff_reader.hpp>
#include <pni/image_info.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(tiff_reader_test)

    BOOST_AUTO_TEST_CASE(test_read)
    {
      std::vector<uint32> data{0,1,2,3,4,5,6,7};
      
      tiff_reader reader("idl_file.tif");
      image_info info;
      BOOST_CHECK_NO_THROW(info = reader.info(0));
      BOOST_CHECK(info.nx() == 4);
      BOOST_CHECK(info.ny() == 2);
      BOOST_CHECK(info.bit_per_pixel() == 32);
      
      auto image = reader.image<std::vector<uint32>>(0);
      BOOST_CHECK(image.size() == data.size());
      BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
				    data.begin(),data.end());
    }

BOOST_AUTO_TEST_SUITE_END()
