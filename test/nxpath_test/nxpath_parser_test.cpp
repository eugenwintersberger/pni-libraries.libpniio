//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 11, 2014
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath/parser.hpp>
#include <pni/io/nx/nxpath/utils.hpp>
#include <pni/io/exceptions.hpp>

using namespace pni::core;
using namespace pni::io::nx;



BOOST_AUTO_TEST_SUITE(nxpath_parser_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_element_path_only)
    {
        string input = "/entry/:NXinstrument/detector:NXdetector";
        nxpath output;
        BOOST_CHECK_NO_THROW(output = parsers::parse_path(input));

        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK(output.attribute().empty());
        BOOST_CHECK(is_absolute(output));
        BOOST_CHECK_EQUAL(output.size(),4);

        input = "entry/:NXinstrument/detector:NXdetector";
        BOOST_CHECK_NO_THROW(output = parsers::parse_path(input));

        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK(output.attribute().empty());
        BOOST_CHECK(!is_absolute(output));
        BOOST_CHECK_EQUAL(output.size(),3);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        string input = "/:NXentry@datx";
        nxpath output;

        BOOST_CHECK_NO_THROW(output = parsers::parse_path(input));
        BOOST_CHECK_EQUAL(output.front().first,"/");
        BOOST_CHECK_EQUAL(output.front().second ,"NXroot");
        BOOST_CHECK_EQUAL(output.attribute(),"datx");
        BOOST_CHECK_EQUAL(output.size(),2);

        input = "/@name";
        BOOST_CHECK_NO_THROW(output = parsers::parse_path(input));
        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK_EQUAL(output.size(),1);
        BOOST_CHECK_EQUAL(output.attribute(),"name");

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        string input = "/:NXentry:/:NXinstrument";

        BOOST_CHECK_THROW(parsers::parse_path(input),pni::io::parser_error);

        input = ".../:NXinstrument";
        BOOST_CHECK_THROW(parsers::parse_path(input),pni::io::parser_error);

        input = "/:NXinstrument/$hello";
        BOOST_CHECK_THROW(parsers::parse_path(input),pni::io::parser_error);

        input = "/:NXinstrument/ llo/instrument";
        BOOST_CHECK_THROW(parsers::parse_path(input),pni::io::parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()
