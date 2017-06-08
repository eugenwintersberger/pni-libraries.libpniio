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
//  Created on: Jan 29, 2015
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <pni/io/parsers/value_parser.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include "parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

struct value_parser_test_fixture : parser_test_fixture<value>
{};

BOOST_FIXTURE_TEST_SUITE(value_parser_test,value_parser_test_fixture)

    typedef value result_type;

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_int_value)
    {
        result_type v = p("1234");
        type_id_t tid = type_id_t::INT64;
        BOOST_CHECK_EQUAL(v.type_id(),tid);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_float_value)
    {
        result_type v = p("1.234e+3");
        type_id_t tid = type_id_t::FLOAT64;
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(1.234e+3,v.as<float64>(),1.e-8);

        v = p("1.2");
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(1.2,v.as<float64>(),1.e-8);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_complex_value)
    {
        result_type v = p("1.3+I3.4");
        type_id_t tid = type_id_t::COMPLEX64;
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(1.3,v.as<complex64>().real(),1.e-8);
        BOOST_CHECK_CLOSE_FRACTION(3.4,v.as<complex64>().imag(),1.e-8);

        v = p("-j3.9");
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(0.0,v.as<complex64>().real(),1.e-8);
        BOOST_CHECK_CLOSE_FRACTION(-3.9,v.as<complex64>().imag(),1.e-8);

        v = p("j3.9");
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(0.0,v.as<complex64>().real(),1.e-8);
        BOOST_CHECK_CLOSE_FRACTION(3.9,v.as<complex64>().imag(),1.e-8);

        v = p("1.+i4.");
        BOOST_CHECK_EQUAL(v.type_id(),tid);
        BOOST_CHECK_CLOSE_FRACTION(1.0,v.as<complex64>().real(),1.e-8);
        BOOST_CHECK_CLOSE_FRACTION(4.0,v.as<complex64>().imag(),1.e-8);

    }

BOOST_AUTO_TEST_SUITE_END()
