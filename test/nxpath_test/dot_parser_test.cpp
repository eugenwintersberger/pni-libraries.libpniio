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
//  Created on: Jun 19, 2014
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath/parser.hpp>

using namespace pni::core;
using namespace pni::io::nx;
using namespace pni::io::nx::parsers;
using namespace boost::spirit;

typedef string::const_iterator iterator_type;
typedef dot_parser<iterator_type> parser_type;
typedef boost::spirit::qi::expectation_failure<iterator_type> 
        expectation_error_type;

struct dot_parser_test_fixture
{
    parser_type parser;
    iterator_type start_iter,stop_iter;
    string input;
    string output;
    
    dot_parser_test_fixture():
        parser(),
        start_iter(),
        stop_iter(),
        input(),
        output()
    {}

};

BOOST_FIXTURE_TEST_SUITE(dot_parser_test,dot_parser_test_fixture)

    void set_input(const string &value,iterator_type &start_iter,
                                       iterator_type &stop_iter)
    {
        start_iter = value.begin();
        stop_iter  = value.end();
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_one)
    {
        input = "."; 
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK_EQUAL(output, ".");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_two)
    {
        input = ".."; 
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK_EQUAL(output,"..");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_many)
    {
        input = "...";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK_EQUAL(output,"..");
    }

BOOST_AUTO_TEST_SUITE_END()

