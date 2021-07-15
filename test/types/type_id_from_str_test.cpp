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

BOOST_AUTO_TEST_SUITE(type_id_from_str_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("uint8"),type_id_t::UINT8);
        BOOST_CHECK_EQUAL(type_id_from_str("ui8"),type_id_t::UINT8);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int8_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("int8"),type_id_t::INT8);
        BOOST_CHECK_EQUAL(type_id_from_str("i8"),type_id_t::INT8);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int16_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("i16"),type_id_t::INT16);
        BOOST_CHECK_EQUAL(type_id_from_str("int16"),type_id_t::INT16);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_uint16_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("uint16"),type_id_t::UINT16);
        BOOST_CHECK_EQUAL(type_id_from_str("ui16"),type_id_t::UINT16);
    }
    
    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_int32_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("i32"),type_id_t::INT32);
        BOOST_CHECK_EQUAL(type_id_from_str("int32"),type_id_t::INT32);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_uint32_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("uint32"),type_id_t::UINT32);
        BOOST_CHECK_EQUAL(type_id_from_str("ui32"),type_id_t::UINT32);
    }
   
    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_int64_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("i64"),type_id_t::INT64);
        BOOST_CHECK_EQUAL(type_id_from_str("int64"),type_id_t::INT64);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_uint64_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("uint64"),type_id_t::UINT64);
        BOOST_CHECK_EQUAL(type_id_from_str("ui64"),type_id_t::UINT64);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_float32_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("float32"),type_id_t::FLOAT32);
        BOOST_CHECK_EQUAL(type_id_from_str("f32"),type_id_t::FLOAT32);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_float64_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("float64"),type_id_t::FLOAT64);
        BOOST_CHECK_EQUAL(type_id_from_str("f64"),type_id_t::FLOAT64);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_float128_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("float128"),type_id_t::FLOAT128);
        BOOST_CHECK_EQUAL(type_id_from_str("f128"),type_id_t::FLOAT128);
    }
    
    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_complex32_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("complex32"),type_id_t::COMPLEX32);
        BOOST_CHECK_EQUAL(type_id_from_str("c32"),type_id_t::COMPLEX32);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_complex64_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("complex64"),type_id_t::COMPLEX64);
        BOOST_CHECK_EQUAL(type_id_from_str("c64"),type_id_t::COMPLEX64);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_complex128_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("complex128"),type_id_t::COMPLEX128);
        BOOST_CHECK_EQUAL(type_id_from_str("c128"),type_id_t::COMPLEX128);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_string_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("string"),type_id_t::STRING);
        BOOST_CHECK_EQUAL(type_id_from_str("str"),type_id_t::STRING);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_binary_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("binary"),type_id_t::BINARY);
    }

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_boold_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("bool"),type_id_t::BOOL);
    }
    
    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
    BOOST_AUTO_TEST_CASE(test_none_id_from_str)
    {
        BOOST_CHECK_EQUAL(type_id_from_str("none"),type_id_t::NONE);
    }

BOOST_AUTO_TEST_SUITE_END()
