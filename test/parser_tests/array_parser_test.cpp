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

#include "array_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_parser_test);

//-----------------------------------------------------------------------------
void array_parser_test::setUp() 
{ 
    //setting up the integer strings
    int_str1 = "[1,2,3,4,5]";
    int_str2 = "(1;2;3;4;5)";
    int_str3 = "1;2;3;4;5";
    int_str4 = "1 2    3 4   5"; 
    float_str1 = "[1.34,-2.e+2,3.342,4.,5.34]";
    float_str2 = "(1.34;-2.e+2;3.342;4.;5.34)";
    float_str3 = "1.34;-2.e+2;3.342;4.;5.34";
    float_str4 = "   1.34 -2.e+2  3.342 4  5.34 ";

    //seting upt the integer vector
    int_vec = std::vector<int32>{1,2,3,4,5};

    //setting up the float vector
    float_vec = std::vector<float64>{1.34,-2.e+2,3.342,4,5.34};
}

//-----------------------------------------------------------------------------
void array_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void array_parser_test::test_int1_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str1.begin();
    stop_iter  = int_str1.end();
    parse(start_iter,stop_iter,array_parser_t(),a);

    auto viter = int_vec.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<int32>(),*(viter++));

}

//-----------------------------------------------------------------------------
void array_parser_test::test_int2_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str2.begin();
    stop_iter  = int_str2.end();
    parse(start_iter,stop_iter,array_parser_t('(',')',';'),a);

    auto viter = int_vec.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<int32>(),*(viter++));

}

//-----------------------------------------------------------------------------
void array_parser_test::test_int3_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str3.begin();
    stop_iter  = int_str3.end();
    parse(start_iter,stop_iter,array_parser_t(';'),a);

    auto viter = int_vec.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<int32>(),*(viter++));

}

//-----------------------------------------------------------------------------
void array_parser_test::test_int4_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = int_str4.begin();
    stop_iter  = int_str4.end();
    parse(start_iter,stop_iter,array_parser_t(' '),a);

    auto viter = int_vec.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<int32>(),*(viter++));

}
//-----------------------------------------------------------------------------
void array_parser_test::test_float1_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    start_iter = float_str1.begin();
    stop_iter = float_str1.end();
    parse(start_iter,stop_iter,array_parser_t(),a);

    auto viter = float_vec.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<float64>(),*(viter++));
}
