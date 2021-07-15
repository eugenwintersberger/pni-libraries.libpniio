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

using namespace pni;

BOOST_AUTO_TEST_SUITE(str_from_type_id_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int8_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::INT8),"int8");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UINT8),"uint8");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int16_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::INT16),"int16");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint16_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UINT16),"uint16");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::INT32),"int32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UINT32),"uint32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::INT64),"int64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UINT64),"uint64");
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::FLOAT32),"float32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::FLOAT64),"float64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float128_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::FLOAT128),"float128");
    }
  
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::COMPLEX32),"complex32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::COMPLEX64),"complex64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex128_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::COMPLEX128),"complex128");
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_string_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::STRING),"string");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_binary_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::BINARY),"binary");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_bool_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::BOOL) , "bool");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_none_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::NONE) , "none");
    }

BOOST_AUTO_TEST_SUITE_END()
