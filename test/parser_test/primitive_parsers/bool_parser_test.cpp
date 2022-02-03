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
//  Created on: Jan 28, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#include <boost/test/included/unit_test.hpp>
#include <pni/parsers/bool_parser.hpp>
#include <pni/exceptions.hpp>
#include <pni/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include "parser_test_fixture.hpp"

using namespace pni;

struct bool_parser_test_fixture : parser_test_fixture<bool_t>
{};

struct ebool_parser_test_fixture : parser_test_fixture<hdf5::datatype::EBool>
{};

BOOST_FIXTURE_TEST_SUITE(bool_parser_test,bool_parser_test_fixture)

    BOOST_AUTO_TEST_CASE(test_true)
    {
        BOOST_CHECK(p("true"));
        BOOST_CHECK(p("True"));
        BOOST_CHECK(p("TRUE"));
        BOOST_CHECK(p("1"));
    }

    BOOST_AUTO_TEST_CASE(test_false)
    {
        BOOST_CHECK(!p("false"));
        BOOST_CHECK(!p("False"));
        BOOST_CHECK(!p("FALSE"));
        BOOST_CHECK(!p("0"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("abc"),parser_error);
        BOOST_CHECK_THROW(p("TruE"),parser_error);
        BOOST_CHECK_THROW(p("FalSe"),parser_error);
        BOOST_CHECK_THROW(p("Xtrue"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ebool_parser_test,ebool_parser_test_fixture)

    BOOST_AUTO_TEST_CASE(test_true)
    {
        BOOST_CHECK(p("true"));
        BOOST_CHECK(p("True"));
        BOOST_CHECK(p("TRUE"));
        BOOST_CHECK(p("1"));
    }

    BOOST_AUTO_TEST_CASE(test_false)
    {
        BOOST_CHECK(!p("false"));
        BOOST_CHECK(!p("False"));
        BOOST_CHECK(!p("FALSE"));
        BOOST_CHECK(!p("0"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("abc"),parser_error);
        BOOST_CHECK_THROW(p("TruE"),parser_error);
        BOOST_CHECK_THROW(p("FalSe"),parser_error);
        BOOST_CHECK_THROW(p("Xtrue"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()
