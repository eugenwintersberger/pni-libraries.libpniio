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
#include "elements_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(elements_parser_test);

using namespace boost::spirit;

//-----------------------------------------------------------------------------
void elements_parser_test::setUp() 
{ 
    output.clear(); //need to clear the list before each run
}

//-----------------------------------------------------------------------------
void elements_parser_test::tearDown() {}



//----------------------------------------------------------------------------
void elements_parser_test::test_relative()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_input(":NXentry/:NXinstrument/lambda:NXdetector/data");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));
  
    CPPUNIT_ASSERT(output.size() == 4);
     
    element = output.front(); output.pop_front();
    CPPUNIT_ASSERT((element.first.empty()) && (element.second=="NXentry"));
    
    element = output.front(); output.pop_front();
    CPPUNIT_ASSERT(element.first.empty());
    CPPUNIT_ASSERT(element.second=="NXinstrument");
    
    element = output.front(); output.pop_front();
    CPPUNIT_ASSERT((element.first == "lambda") && 
                   (element.second=="NXdetector"));

    element = output.front(); output.pop_front();
    CPPUNIT_ASSERT((element.first == "data") && 
                   (element.second.empty()));

    //here we should have consumed all the components from the path
    CPPUNIT_ASSERT(output.size() == 0);
}

//----------------------------------------------------------------------------
void elements_parser_test::test_relative_current()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_input("./././lambda:NXdetector/data");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));

    CPPUNIT_ASSERT(output.size() == 5);

    for(size_t i=0;i<3;++i)
    {
        element = output.front(); output.pop_front();
        CPPUNIT_ASSERT((element.first == ".") && (element.second.empty()));
    }

    element = output.front();
    CPPUNIT_ASSERT((element.first == "lambda") && 
                   (element.second == "NXdetector"));

}

//----------------------------------------------------------------------------
void elements_parser_test::test_relative_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    set_input("../../../data:NXdata/");
    CPPUNIT_ASSERT(qi::parse(start_iter,stop_iter,parser,output));

    CPPUNIT_ASSERT(output.size() == 4);

    for(size_t i=0;i<3;++i)
    {
        element = output.front(); output.pop_front();
        CPPUNIT_ASSERT((element.first == "..") && (element.second.empty()));
    }

    element = output.front();
    CPPUNIT_ASSERT((element.first == "data") && 
                   (element.second == "NXdata"));


}


