//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 22, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/included/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/types/type_conversion.hpp>

using namespace pni;


BOOST_AUTO_TEST_SUITE(is_convertible_test)

    //=========================================================================
    void always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::Bool));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Binary));
        BOOST_CHECK(!is_convertible(sid,type_id_t::String));
    }

    //=========================================================================
    void uint_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::UInt8));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UInt16));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UInt32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UInt64));
    }

    //=========================================================================
    void int_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::Int8));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Int16));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Int32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Int64));
    }

    //=========================================================================
    void float_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::Float32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Float64));
        BOOST_CHECK(!is_convertible(sid,type_id_t::Float128));
    }

    //=========================================================================
    void float_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::Float32));
        BOOST_CHECK(is_convertible(sid,type_id_t::Float64));
        BOOST_CHECK(is_convertible(sid,type_id_t::Float128));
    }

    //=========================================================================
    void complex_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::Complex32));
        BOOST_CHECK(is_convertible(sid,type_id_t::Complex64));
        BOOST_CHECK(is_convertible(sid,type_id_t::Complex128));
    }

    //=========================================================================
    void uint_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::UInt8));
        BOOST_CHECK(is_convertible(sid,type_id_t::UInt16));
        BOOST_CHECK(is_convertible(sid,type_id_t::UInt32));
        BOOST_CHECK(is_convertible(sid,type_id_t::UInt64));
    }

    //=========================================================================
    void int_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::Int8));
        BOOST_CHECK(is_convertible(sid,type_id_t::Int16));
        BOOST_CHECK(is_convertible(sid,type_id_t::Int32));
        BOOST_CHECK(is_convertible(sid,type_id_t::Int64));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8)
    {
        uint_always_pass(type_id_t::UInt8);
        int_always_pass(type_id_t::UInt8);
        float_always_pass(type_id_t::UInt8);
        complex_always_pass(type_id_t::UInt8);
        always_fails(type_id_t::UInt8);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint16)
    {
        uint_always_pass(type_id_t::UInt16);
        int_always_pass(type_id_t::UInt16);
        float_always_pass(type_id_t::UInt16);
        complex_always_pass(type_id_t::UInt16);
        always_fails(type_id_t::UInt16);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint32)
    {
        uint_always_pass(type_id_t::UInt32);
        int_always_pass(type_id_t::UInt32);
        float_always_pass(type_id_t::UInt32);
        complex_always_pass(type_id_t::UInt32);
        always_fails(type_id_t::UInt32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint64)
    {
        uint_always_pass(type_id_t::UInt64);
        int_always_pass(type_id_t::UInt64);
        float_always_pass(type_id_t::UInt64);
        complex_always_pass(type_id_t::UInt64);
        always_fails(type_id_t::UInt64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int8)
    {
        uint_always_pass(type_id_t::Int64);
        int_always_pass(type_id_t::Int64);
        float_always_pass(type_id_t::Int64);
        complex_always_pass(type_id_t::Int64);
        always_fails(type_id_t::Int64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int16)
    {
        uint_always_pass(type_id_t::Int16);
        int_always_pass(type_id_t::Int16);
        float_always_pass(type_id_t::Int16);
        complex_always_pass(type_id_t::Int16);
        always_fails(type_id_t::Int16);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int32)
    {
        uint_always_pass(type_id_t::Int32);
        int_always_pass(type_id_t::Int32);
        float_always_pass(type_id_t::Int32);
        complex_always_pass(type_id_t::Int32);
        always_fails(type_id_t::Int32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int64)
    {
        uint_always_pass(type_id_t::Int64);
        int_always_pass(type_id_t::Int64);
        float_always_pass(type_id_t::Int64);
        complex_always_pass(type_id_t::Int64);
        always_fails(type_id_t::Int64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float32)
    {
        uint_always_fails(type_id_t::Float32);
        int_always_fails(type_id_t::Float32);
        float_always_pass(type_id_t::Float32);
        complex_always_pass(type_id_t::Float32);
        always_fails(type_id_t::Float32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float64)
    {
        uint_always_fails(type_id_t::Float64);
        int_always_fails(type_id_t::Float64);
        float_always_pass(type_id_t::Float64);
        complex_always_pass(type_id_t::Float64);
        always_fails(type_id_t::Float64);

    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float128)
    {
        uint_always_fails(type_id_t::Float128);
        int_always_fails(type_id_t::Float128);
        float_always_pass(type_id_t::Float128);
        complex_always_pass(type_id_t::Float128);
        always_fails(type_id_t::Float128);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex32)
    {
        uint_always_fails(type_id_t::Complex32);
        int_always_fails(type_id_t::Complex32);
        float_always_fails(type_id_t::Complex32);

        complex_always_pass(type_id_t::Complex32);
        always_fails(type_id_t::Complex32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex64)
    {
        uint_always_fails(type_id_t::Complex64);
        int_always_fails(type_id_t::Complex64);
        float_always_fails(type_id_t::Complex64);

        complex_always_pass(type_id_t::Complex64);
        always_fails(type_id_t::Complex64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex128)
    {
        uint_always_fails(type_id_t::Complex128);
        int_always_fails(type_id_t::Complex128);
        float_always_fails(type_id_t::Complex128);

        complex_always_pass(type_id_t::Complex128);
        always_fails(type_id_t::Complex128);
    }

BOOST_AUTO_TEST_SUITE_END()
