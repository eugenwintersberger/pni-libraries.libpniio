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
///

#include <boost/exception/diagnostic_information.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include "filepath_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(filepath_parser_test);

using namespace boost::spirit;

//-----------------------------------------------------------------------------
void filepath_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void filepath_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void filepath_parser_test::test_valid_path()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("hello.world:// ");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,filename));

    CPPUNIT_ASSERT(filename=="hello.world");

    set_input("/usr/share/data/hello.nxs://");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,filename));
    CPPUNIT_ASSERT(filename=="/usr/share/data/hello.nxs");

    set_input("://");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,filename));
    CPPUNIT_ASSERT(filename=="");
}

//-----------------------------------------------------------------------------
void filepath_parser_test::test_invalid_path()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("/hello.world ");

    CPPUNIT_ASSERT_THROW(qi::parse(start_iter,stop_iter,parser,filename),
                         qi::expectation_failure<iterator_type>);
}

