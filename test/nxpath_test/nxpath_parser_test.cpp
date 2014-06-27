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

#include <boost/exception/diagnostic_information.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include "nxpath_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_parser_test);

using namespace boost::spirit;

//-----------------------------------------------------------------------------
void nxpath_parser_test::setUp() 
{ 
    output = nxpath();
}

//-----------------------------------------------------------------------------
void nxpath_parser_test::tearDown() {}


//-----------------------------------------------------------------------------
void nxpath_parser_test::test_element_path_only()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;


    set_input("/entry/:NXinstrument/detector:NXdetector");

    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    CPPUNIT_ASSERT(output.filename().empty());
    CPPUNIT_ASSERT(output.attribute().empty());
    CPPUNIT_ASSERT(output.is_absolute());
    CPPUNIT_ASSERT(output.size()==4);

    set_input("entry/:NXinstrument/detector:NXdetector");
    
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    CPPUNIT_ASSERT(output.filename().empty());
    CPPUNIT_ASSERT(output.attribute().empty());
    CPPUNIT_ASSERT(!output.is_absolute());
    CPPUNIT_ASSERT(output.size()==3);
}

//----------------------------------------------------------------------------
void nxpath_parser_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_input("/:NXentry@datx");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    CPPUNIT_ASSERT(output.front().first == "/");
    CPPUNIT_ASSERT(output.front().second == "NXroot");
    CPPUNIT_ASSERT(output.attribute() == "datx");
    CPPUNIT_ASSERT(output.size() == 2);


    output = nxpath();
    set_input("/@name");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
    CPPUNIT_ASSERT(output.filename().empty());
    CPPUNIT_ASSERT(output.size()==1);
    CPPUNIT_ASSERT(output.attribute() == "name");

}
