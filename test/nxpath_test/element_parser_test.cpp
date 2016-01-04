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
typedef element_parser<iterator_type> element_parser_type;
typedef boost::spirit::qi::expectation_failure<iterator_type> 
        expectation_error_type;

struct element_parser_test_fixture
{
    element_parser_type parser;

    iterator_type start_iter,stop_iter;
    string input;
    nxpath::element_type output;

    element_parser_test_fixture():
        parser(),
        start_iter(),
        stop_iter(),
        input(),
        output()
    {}
};

BOOST_FIXTURE_TEST_SUITE(element_parser_test,element_parser_test_fixture)


    void set_input(const string &value,iterator_type &start_iter,
                                       iterator_type &stop_iter)
    {
        start_iter = value.begin();
        stop_iter  = value.end();
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_current)
    {
        input = ".";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK_EQUAL(output.first,".");
        BOOST_CHECK(output.second.empty());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_parent)
    {
        input = "..";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        
        BOOST_CHECK_EQUAL(output.first,"..");
        BOOST_CHECK(output.second.empty());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        input =  "name:class";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        
        BOOST_CHECK_EQUAL(output.first,"name");
        BOOST_CHECK_EQUAL(output.second,"class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_name)
    {
        input =  "name";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        
        BOOST_CHECK_EQUAL(output.first,"name");
        BOOST_CHECK(output.second.empty());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_class)
    {
        input =  ":class";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        
        BOOST_CHECK(output.first.empty());
        BOOST_CHECK_EQUAL(output.second,"class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        //not allowede
        input = "/";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(!qi::parse(start_iter,stop_iter,parser,output));
        
        input = ":.class";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                          expectation_error_type);
       
        input =  ":";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                          expectation_error_type);

        input = ": bla";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                             expectation_error_type);
    }

BOOST_AUTO_TEST_SUITE_END()
