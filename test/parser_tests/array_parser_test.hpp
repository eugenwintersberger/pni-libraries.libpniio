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
 *  Created on: May 06, 2013
 *      Author: Eugen Wintersberger
 */

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/parsers/array_parser.hpp>
#include <pni/core/types.hpp>
#include <pni/core/slice.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

/*!
\brief testing the array parser

The parser should read int or float values with different start/stop symbols and
value delimiters. We also should test the case where we only want to parse a
bunch of values without start/stop symbols.

*/
class array_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(array_parser_test);
    CPPUNIT_TEST(test_int1_array);
    CPPUNIT_TEST(test_int2_array);
    CPPUNIT_TEST(test_int3_array);
    CPPUNIT_TEST(test_int4_array);
    CPPUNIT_TEST(test_int5_array);
    CPPUNIT_TEST(test_float1_array);
    CPPUNIT_TEST(test_float2_array);
    CPPUNIT_TEST(test_float3_array);
    CPPUNIT_TEST(test_float4_array);
	CPPUNIT_TEST_SUITE_END();

    //! the string iterator type
    typedef string::const_iterator iterator_t;
    //! the parser type
    typedef array_parser<iterator_t> array_parser_t;
    //! instance of the parser
    array_parser_t parser1,parser2,parser3,parser4;

    iterator_t start_iter,stop_iter;
    
    string int_str1;
    string int_str2;
    string int_str3;
    string int_str4;
    string int_str5;
    string float_str1;
    string float_str2;
    string float_str3;
    string float_str4;

    std::vector<int32> int_vec;
    std::vector<float64> float_vec;
    array a;
    
public:
	void setUp();
	void tearDown();
	void test_int1_array();
	void test_int2_array();
	void test_int3_array();
	void test_int4_array();
    void test_int5_array();
    void test_float1_array();
    void test_float2_array();
    void test_float3_array();
    void test_float4_array();
};


