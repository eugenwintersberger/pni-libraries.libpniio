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
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/tiff/tiff_reader.hpp>

using namespace pni::core;
using namespace pni::io;

class tiff_reader_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(tiff_reader_test);
        CPPUNIT_TEST(test_read_header);
        CPPUNIT_TEST(test_read_data_ui8);
        CPPUNIT_TEST(test_read_data_i8);
        CPPUNIT_TEST(test_read_data_i32);
        CPPUNIT_TEST_SUITE_END();

        
    public:
        void setUp();
        void tearDown();
        
        void test_read_header();
        void test_read_data_ui8();
        void test_read_data_i8();
        void test_read_data_i32();
};

