//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Oct 15, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/types.hpp>
#include <pni/types/type_id_map.hpp>
#include <iostream>

using namespace pni;

BOOST_AUTO_TEST_SUITE(type_id_map_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_uint8)
    {
        BOOST_CHECK(type_id_map<uint8>::type_id == type_id_t::UINT8);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_int8)
    {
        BOOST_CHECK(type_id_map<int8>::type_id == type_id_t::INT8);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_uint16)
    {
        BOOST_CHECK(type_id_map<uint16>::type_id == type_id_t::UINT16);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_int16)
    {
        BOOST_CHECK(type_id_map<int16>::type_id == type_id_t::INT16);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_uint32)
    {
        BOOST_CHECK(type_id_map<uint32>::type_id == type_id_t::UINT32);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_int32)
    {
        BOOST_CHECK(type_id_map<int32>::type_id == type_id_t::INT32);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_uint64)
    {
        BOOST_CHECK(type_id_map<uint64>::type_id == type_id_t::UINT64);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_int64)
    {
        BOOST_CHECK(type_id_map<int64>::type_id == type_id_t::INT64);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_float32)
    {
        BOOST_CHECK(type_id_map<float32>::type_id == type_id_t::FLOAT32);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_float64)
    {
        BOOST_CHECK(type_id_map<float64>::type_id == type_id_t::FLOAT64);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_float128)
    {
        BOOST_CHECK(type_id_map<float128>::type_id == type_id_t::FLOAT128);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_complex32)
    {
        BOOST_CHECK(type_id_map<complex32>::type_id == type_id_t::COMPLEX32);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_complex64)
    {
        BOOST_CHECK(type_id_map<complex64>::type_id == type_id_t::COMPLEX64);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_complex128)
    {
        BOOST_CHECK(type_id_map<complex128>::type_id == type_id_t::COMPLEX128);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_map_string)
    {
        BOOST_CHECK(type_id_map<string>::type_id == type_id_t::STRING);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_map_binary)
    {
        BOOST_CHECK(type_id_map<binary>::type_id == type_id_t::BINARY);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_map_bool)
    {
        BOOST_CHECK(type_id_map<bool_t>::type_id == type_id_t::BOOL);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_map_none)
    {
        BOOST_CHECK(type_id_map<none>::type_id == type_id_t::NONE);
    }


BOOST_AUTO_TEST_SUITE_END()
