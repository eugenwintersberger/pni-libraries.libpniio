//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Apr 27, 2015
//      Author: Eugen Wintersberger
//


#include <pni/types.hpp>
#include <boost/test/unit_test.hpp>
#include <pni/formatters/scalar_format.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(value_formatter_test)
    typedef value input_type;

    BOOST_AUTO_TEST_CASE(test_uint8)
    {
        typedef uint8 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_int8)
    {
        typedef int8 itype;

        BOOST_CHECK(format(input_type(itype(12))) == "+12");
        BOOST_CHECK(format(input_type(itype(-12))) == "-12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_uint16)
    {
        typedef uint16 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_int16)
    {
        typedef int16 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "+12");
        BOOST_CHECK(format(input_type(itype(-12))) == "-12");
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_uint32)
    {
        typedef uint32 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_int32)
    {
        typedef int32 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "+12");
        BOOST_CHECK(format(input_type(itype(-12))) == "-12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_uint64)
    {
        typedef uint64 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_int64)
    {
        typedef int64 itype;
        BOOST_CHECK(format(input_type(itype(12))) == "+12");
        BOOST_CHECK(format(input_type(itype(-12))) == "-12");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_float32)
    {
        typedef float32 itype;
        BOOST_CHECK(format(input_type(itype(1.23e+4))) == "+1.230000000e+04");
        BOOST_CHECK(format(input_type(itype(-1.23e-4))) == "-1.230000053e-04");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_float64)
    {
        typedef float64 itype;
        BOOST_CHECK(format(input_type(itype(1.23e+4))) == "+1.23000000000000000e+04");
        BOOST_CHECK(format(input_type(itype(1.23e+123))) == "+1.23000000000000006e+123");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_float128)
    {
        typedef float128 itype;
        BOOST_CHECK(format(input_type(itype(1.23e+4))) == "+1.23000000000000000e+04");
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_complex32)
    {
        typedef complex32 itype;
        BOOST_CHECK(format(input_type(itype(1.23e+4,4.2))) == "+1.230000000e+04+I4.199999809e+00");
        BOOST_CHECK(format(input_type(itype(-1.23e-4))) == "-1.230000053e-04+I0.000000000e+00");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_complex64)
    {
        typedef complex64 itype;

        BOOST_CHECK(format(input_type(itype(1.23e+4,-4.2e+3))) == "+1.23000000000000000e+04-I4.20000000000000000e+03");
        BOOST_CHECK(format(input_type(itype(0.0,-1.23e+123))) == "+0.00000000000000000e+00-I1.23000000000000006e+123");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_complex128)
    {
        typedef complex128 itype;
        BOOST_CHECK(format(input_type(itype(1.23e+4,-4.2e+3))) == "+1.23000000000000000e+04-I4.20000000000000000e+03");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_bool)
    {
        bool_t v = true;
        value eev(v);
        //format(eev);
        // BOOST_CHECK(format(value(v)) == "true");
        // BOOST_CHECK(format(value(v)) == "true");
        // v = false;
        // BOOST_CHECK(format(input_type(v)) == "false");
    }

    BOOST_AUTO_TEST_CASE(test_ebool)
    {
        hdf5::datatype::EBool ev = hdf5::datatype::EBool::True;
        BOOST_CHECK(format(input_type(ev)) == "true");
        ev = hdf5::datatype::EBool::False;
        BOOST_CHECK(format(input_type(ev)) == "false");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_string)
    {
        typedef string itype;

        BOOST_CHECK(format(input_type(itype("hello world"))) == "hello world");
    }

BOOST_AUTO_TEST_SUITE_END()
