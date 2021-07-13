//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Nov 15, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/tiff/tiff_reader.hpp>
#include <pni/image_info.hpp>

using namespace pni::core;
using namespace pni::io;

BOOST_AUTO_TEST_SUITE(tiff_reader_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_header)
    {
        tiff_reader reader("iui8.tiff");
        BOOST_CHECK(reader.nimages() == 1);

        image_info info = reader.info(0);
        BOOST_CHECK(info.ny() == 4);
        BOOST_CHECK(info.nx() == 2);
        BOOST_CHECK(info.npixels() == 8);
        BOOST_CHECK(info.bit_per_pixel() == 8);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo = info.get_channel(0);
        BOOST_CHECK(cinfo.bits() == 8);
        BOOST_CHECK(cinfo.type_id() == type_id_t::UINT8);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_data_ui8)
    {
        std::vector<uint8> data{1,2,3,4,2,4,6,8};
        tiff_reader reader("iui8.tiff");
        BOOST_CHECK(reader.nimages() == 1);

        image_info info;
        BOOST_CHECK_NO_THROW(info = reader.info(0));
        BOOST_CHECK(info.nx() == 2);
        BOOST_CHECK(info.ny() == 4);
        BOOST_CHECK(info.npixels() == 8);
        BOOST_CHECK(info.bit_per_pixel() == 8);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo;
        BOOST_CHECK_NO_THROW(cinfo = info.get_channel(0));
        BOOST_CHECK(cinfo.bits() == 8);
        BOOST_CHECK(cinfo.type_id() == type_id_t::UINT8);
        
        auto image = reader.image<std::vector<uint8>>(0);
        BOOST_CHECK(image.size() == data.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
                                      data.begin(),data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_data_i8)
    {
        std::vector<int8> data{-1,2,-3,4,2,-4,6,-8};
        tiff_reader reader("ii8.tiff");
        image_info info;
        BOOST_CHECK_NO_THROW(info = reader.info(0));
        BOOST_CHECK(info.nx() == 2);
        BOOST_CHECK(info.ny() == 4);
        BOOST_CHECK(info.npixels() == 8);
        BOOST_CHECK(info.bit_per_pixel() == 8);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo;
        BOOST_CHECK_NO_THROW(cinfo = info.get_channel(0));
        BOOST_CHECK(cinfo.bits() == 8);
        BOOST_CHECK(cinfo.type_id() == type_id_t::INT8);
        
        
        auto image = reader.image<std::vector<int8>>(0);
        BOOST_CHECK(image.size() == data.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
                                      data.begin(),data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_data_i32)
    {
        std::vector<int32> data{-100,200,-300,400,
                                200,-400,600,-800};

        tiff_reader reader("ii32.tiff");
        BOOST_CHECK(reader.nimages() == 1);
        image_info info;
        BOOST_CHECK_NO_THROW(info = reader.info(0));
        BOOST_CHECK(info.nx() == 2);
        BOOST_CHECK(info.ny() == 4);
        BOOST_CHECK(info.npixels() == 8);
        BOOST_CHECK(info.bit_per_pixel() == 32);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo;
        BOOST_CHECK_NO_THROW(cinfo = info.get_channel(0));
        BOOST_CHECK(cinfo.bits() == 32);
        BOOST_CHECK(cinfo.type_id() == type_id_t::INT32);

        auto image = reader.image<std::vector<int32>>(0);

        BOOST_CHECK(image.size() == data.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
                                      data.begin(),data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_data_ui32)
    {
        std::vector<uint32> data{100,200,300,400,
                                200,400,600,800};

        tiff_reader reader("ui32.tiff");
        BOOST_CHECK(reader.nimages() == 1);
        image_info info;
        BOOST_CHECK_NO_THROW(info = reader.info(0));
        BOOST_CHECK(info.nx() == 2);
        BOOST_CHECK(info.ny() == 4);
        BOOST_CHECK(info.npixels() == 8);
        BOOST_CHECK(info.bit_per_pixel() == 32);
        BOOST_CHECK(info.nchannels() == 1);

        image_channel_info cinfo;
        BOOST_CHECK_NO_THROW(cinfo = info.get_channel(0));
        BOOST_CHECK(cinfo.bits() == 32);
        BOOST_CHECK(cinfo.type_id() == type_id_t::UINT32);

        auto image = reader.image<std::vector<uint32>>(0);
        BOOST_CHECK(image.size() == data.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
                                      data.begin(),data.end());
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_read_data_float64)
    {
        std::vector<float64> data{-100,200,-300,400,
                                200,-400,600,-800};

        tiff_reader reader("ii32.tiff");
        auto image = reader.image<std::vector<float64>>(0);

        BOOST_CHECK(image.size() == data.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(image.begin(),image.end(),
                                      data.begin(),data.end());
 
    
    }

BOOST_AUTO_TEST_SUITE_END()
