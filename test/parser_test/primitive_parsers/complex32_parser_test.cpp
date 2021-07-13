//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jan 28, 2015
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <pni/parsers/complex_parser.hpp>
#include <pni/exceptions.hpp>
#include <pni/types.hpp>
#include "parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

#define NUM_RES 1.e-6

struct complex32_parser_test_fixture : parser_test_fixture<complex32>
{};

BOOST_FIXTURE_TEST_SUITE(complex32_parser_test,complex32_parser_test_fixture)

    typedef float32 base_type;

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value_for_j)
    {
        result_type result = p("1.0+j2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("-1.0+j2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("1.0-j2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);

        result = p("-1.0-j2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value_for_i)
    {
        result_type result = p("1.0+i2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("-1.0+i2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("1.0-i2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);

        result = p("-1.0-i2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value_for_I)
    {
        result_type result = p("1.0+I2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("-1.0+I2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(+2.0),result.imag(),NUM_RES);

        result = p("1.0-I2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(+1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);

        result = p("-1.0-I2.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-2.0),result.imag(),NUM_RES);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("1.+A5."),parser_error);
        BOOST_CHECK_THROW(p("1.e+2-Ie"),parser_error);
        BOOST_CHECK_THROW(p("1.e+3-I1e+x"),parser_error);
        BOOST_CHECK_THROW(p("1.+j-1"),parser_error);
        BOOST_CHECK_THROW(p("1.+j+1"),parser_error);
        BOOST_CHECK_THROW(p("1.j2"),parser_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_complex_zero)
    {
        result_type result = p("0.+i0.");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(),NUM_RES);

        result = p("0.+I0.");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(),NUM_RES);

        result = p("0.+j0.");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(),NUM_RES);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_real_only)
    {
        result_type result = p("1.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(),NUM_RES);

        result = p("-1.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(), NUM_RES);

        result = p("+1.0");
        BOOST_CHECK_CLOSE_FRACTION(base_type(1.0),result.real(),NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.imag(),NUM_RES);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_imag_only)
    {
        result_type result = p("-i1.e+6");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(),  NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(-1e+6),result.imag(),NUM_RES);

        result = p("+i1.e+6");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(), NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(1e+6),result.imag(),NUM_RES);

        result = p("i2.e+6");
        BOOST_CHECK_CLOSE_FRACTION(base_type(0.0),result.real(), NUM_RES);
        BOOST_CHECK_CLOSE_FRACTION(base_type(2e+6),result.imag(),NUM_RES);
    }

BOOST_AUTO_TEST_SUITE_END()
