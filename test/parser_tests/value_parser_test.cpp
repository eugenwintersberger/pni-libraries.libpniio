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

#include "value_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(value_parser_test);

//-----------------------------------------------------------------------------
void value_parser_test::setUp() 
{
    int_str1 = "1023";
    int_str2 = "  1023 ";
    float_str1 = "1.234";
    float_str2 = "  1.234 ";
    float_str3 = "-1.e-8";
    float_str4 = "  -1.e-8    ";
}

//-----------------------------------------------------------------------------
void value_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void value_parser_test::test_integer1_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str1.begin();
    stop_iter  = int_str1.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.as<int32>() == 1023);

}

//-----------------------------------------------------------------------------
void value_parser_test::test_integer2_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str2.begin();
    stop_iter  = int_str2.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT32);
    CPPUNIT_ASSERT(v.as<int32>() == 1023);

}
//-----------------------------------------------------------------------------
void value_parser_test::test_float1_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = float_str1.begin();
    stop_iter  = float_str1.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::FLOAT64);
    check_equality(v.as<float64>(),1.234);
}

//-----------------------------------------------------------------------------
void value_parser_test::test_float2_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = float_str2.begin();
    stop_iter  = float_str2.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::FLOAT64);
    check_equality(v.as<float64>(),1.234);
}

//-----------------------------------------------------------------------------
void value_parser_test::test_float3_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = float_str3.begin();
    stop_iter  = float_str3.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::FLOAT64);
    check_equality(v.as<float64>(),-1.e-8);
}

//-----------------------------------------------------------------------------
void value_parser_test::test_float4_parser()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = float_str4.begin();
    stop_iter  = float_str4.end();

    parse(start_iter,stop_iter,parser,v);

    CPPUNIT_ASSERT(v.type_id() == type_id_t::FLOAT64);
    check_equality(v.as<float64>(),-1.e-8);
}

