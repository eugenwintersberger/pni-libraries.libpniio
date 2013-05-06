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
#include "EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_parser_test);

//-----------------------------------------------------------------------------
void array_parser_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void array_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void array_parser_test::test_int_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<int32> v{1,2,3,4,5};
    string s1 = "[1,2,3,4,5]";
    iterator_t start,stop;
    array a;

    start = s1.begin();
    stop = s1.end();
    parse(start,stop,parser,a);

    auto viter = v.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<int32>(),*(viter++));

}

//-----------------------------------------------------------------------------
void array_parser_test::test_float_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    std::vector<float64> v{1.34,-2.e+2,3.342,4,5.34};
    string s1 = "[1.34,-2.e+2,3.342,4.,5.34]";
    iterator_t start,stop;
    array a;

    start = s1.begin();
    stop = s1.end();
    parse(start,stop,parser,a);

    auto viter = v.begin();
    auto aiter = a.begin();
    while(aiter != a.end())
        check_equality((aiter++)->as<float64>(),*(viter++));


}
