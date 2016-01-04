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
#include <boost/spirit/home/qi/parse.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath/parser.hpp>
#include <pni/io/nx/nxpath/utils.hpp>

using namespace boost::spirit;
using namespace pni::core;
using namespace pni::io::nx;
using namespace pni::io::nx::parsers;
    
typedef string::const_iterator iterator_type;
typedef nxpath_parser<iterator_type> nxpath_parser_type;
typedef boost::spirit::qi::expectation_failure<iterator_type> 
        expectation_error_type;

struct nxpath_parser_test_fixture
{
    nxpath_parser_type parser;

    iterator_type start_iter,stop_iter;
    string input;
    nxpath output;

    nxpath_parser_test_fixture():
        start_iter(),
        stop_iter(),
        input(),
        output()
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxpath_parser_test,nxpath_parser_test_fixture)

    void set_input(const string &value,iterator_type &start_iter,
                                       iterator_type &stop_iter)
    {
        start_iter = value.begin();
        stop_iter  = value.end();
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_element_path_only)
    {
        input = "/entry/:NXinstrument/detector:NXdetector";
        set_input(input,start_iter,stop_iter);

        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK(output.attribute().empty());
        BOOST_CHECK(is_absolute(output));
        BOOST_CHECK_EQUAL(output.size(),4);

        input = "entry/:NXinstrument/detector:NXdetector";
        set_input(input,start_iter,stop_iter);
        
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK(output.attribute().empty());
        BOOST_CHECK(!is_absolute(output));
        BOOST_CHECK_EQUAL(output.size(),3);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        input = "/:NXentry@datx";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK_EQUAL(output.front().first,"/");
        BOOST_CHECK_EQUAL(output.front().second ,"NXroot");
        BOOST_CHECK_EQUAL(output.attribute(),"datx");
        BOOST_CHECK_EQUAL(output.size(),2);


        output = nxpath();
        input = "/@name";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK(qi::parse(start_iter,stop_iter,parser,output));
        BOOST_CHECK(output.filename().empty());
        BOOST_CHECK_EQUAL(output.size(),1);
        BOOST_CHECK_EQUAL(output.attribute(),"name");

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        input = "/:NXentry:/:NXinstrument";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                         expectation_error_type);
                             
        input = ".../:NXinstrument";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                          expectation_error_type);
                            
        input = "/:NXinstrument/$hello";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                          expectation_error_type);
                            
        input = "/:NXinstrument/ llo/instrument";
        set_input(input,start_iter,stop_iter);
        BOOST_CHECK_THROW(qi::parse(start_iter,stop_iter,parser,output),
                          expectation_error_type);
    }

BOOST_AUTO_TEST_SUITE_END()
