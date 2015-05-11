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

#include <boost/exception/diagnostic_information.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include "element_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(element_parser_test);

using namespace boost::spirit;

//-----------------------------------------------------------------------------
void element_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void element_parser_test::tearDown() {}


//----------------------------------------------------------------------------
void element_parser_test::test_current()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input(".");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    
    CPPUNIT_ASSERT(output.first == ".");
    CPPUNIT_ASSERT(output.second.empty());
}

//----------------------------------------------------------------------------
void element_parser_test::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("..");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    
    CPPUNIT_ASSERT(output.first == "..");
    CPPUNIT_ASSERT(output.second.empty());
}

//----------------------------------------------------------------------------
void element_parser_test::test_full()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("name:class");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    
    CPPUNIT_ASSERT(output.first == "name");
    CPPUNIT_ASSERT(output.second == "class");
}

//----------------------------------------------------------------------------
void element_parser_test::test_name()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("name");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    
    CPPUNIT_ASSERT(output.first == "name");
    CPPUNIT_ASSERT(output.second.empty());
}

//----------------------------------------------------------------------------
void element_parser_test::test_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input(":class");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    
    CPPUNIT_ASSERT(output.first.empty());
    CPPUNIT_ASSERT(output.second == "class");
}

//----------------------------------------------------------------------------
void element_parser_test::test_errors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //not allowede
    set_input("/");
    CPPUNIT_ASSERT(!qi::parse(start_iter,stop_iter,parser,output));
    

    set_input(":.class");
    CPPUNIT_ASSERT_THROW(qi::parse(start_iter,stop_iter,parser,output),
                         expectation_error_type);
   
    
    set_input(":");
    CPPUNIT_ASSERT_THROW(qi::parse(start_iter,stop_iter,parser,output),
                         expectation_error_type);

    set_input(": bla");
    CPPUNIT_ASSERT_THROW(qi::parse(start_iter,stop_iter,parser,output),
                         expectation_error_type);

}
