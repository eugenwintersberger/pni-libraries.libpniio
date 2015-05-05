/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Nov 15, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <vector>
#include <pni/core/types.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "tiff_reader_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(tiff_reader_test);

//-----------------------------------------------------------------------------
void tiff_reader_test::setUp() { }

//-----------------------------------------------------------------------------
void tiff_reader_test::tearDown() { }

//-----------------------------------------------------------------------------
void tiff_reader_test::test_read_header()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    tiff_reader reader("iui8.tiff");
    CPPUNIT_ASSERT(reader.nimages() == 1);

    image_info info = reader.info(0);
    CPPUNIT_ASSERT(info.ny() == 4);
    CPPUNIT_ASSERT(info.nx() == 2);
    
    CPPUNIT_ASSERT(info.npixels() == 8);
    CPPUNIT_ASSERT(info.bit_per_pixel() == 8);
    CPPUNIT_ASSERT(info.nchannels() == 1);

    image_channel_info cinfo = info.get_channel(0);
    CPPUNIT_ASSERT(cinfo.bits() == 8);
    CPPUNIT_ASSERT(cinfo.type_id() == type_id_t::UINT8);
}

//-----------------------------------------------------------------------------
void tiff_reader_test::test_read_data_ui8()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<uint8> data{1,2,3,4,2,4,6,8};
    tiff_reader reader("iui8.tiff");
    
    auto image = reader.image<std::vector<uint8>>(0);
    CPPUNIT_ASSERT(image.size()==data.size());
    CPPUNIT_ASSERT(std::equal(image.begin(),image.end(),data.begin()));
}

//-----------------------------------------------------------------------------
void tiff_reader_test::test_read_data_i8()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<int8> data{-1,2,-3,4,2,-4,6,-8};
    tiff_reader reader("ii8.tiff");
    
    auto image = reader.image<std::vector<int8>>(0);
    CPPUNIT_ASSERT(image.size()==data.size());
    CPPUNIT_ASSERT(std::equal(image.begin(),image.end(),data.begin()));
}

//-----------------------------------------------------------------------------
void tiff_reader_test::test_read_data_i32()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    std::vector<int32> data{-100,200,-300,400,
                            200,-400,600,-800};

    tiff_reader reader("ii32.tiff");
    auto image = reader.image<std::vector<int32>>(0);

    CPPUNIT_ASSERT(image.size()==data.size());
    CPPUNIT_ASSERT(std::equal(image.begin(),image.end(),data.begin()));
}

//-----------------------------------------------------------------------------
void tiff_reader_test::test_read_data_float64()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    std::vector<float64> data{-100,200,-300,400,
                            200,-400,600,-800};

    tiff_reader reader("ii32.tiff");
    auto image = reader.image<std::vector<float64>>(0);

    CPPUNIT_ASSERT(image.size()==data.size());
    CPPUNIT_ASSERT(std::equal(image.begin(),image.end(),data.begin()));
}
