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
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
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
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Int8),"int8");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UInt8),"uint8");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int16_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Int16),"int16");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint16_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UInt16),"uint16");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Int32),"int32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UInt32),"uint32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_int64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Int64),"int64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_uint64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::UInt64),"uint64");
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Float32),"float32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Float64),"float64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float128_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Float128),"float128");
    }
  
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex32_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Complex32),"complex32");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex64_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Complex64),"complex64");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex128_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Complex128),"complex128");
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_string_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::String),"string");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_binary_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Binary),"binary");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_ibool_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::Bool) , "ibool");
    }
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_ebool_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::EBool) , "bool");
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_none_str_from_type_id)
    {
        BOOST_CHECK_EQUAL(str_from_type_id(type_id_t::None) , "none");
    }

BOOST_AUTO_TEST_SUITE_END()
