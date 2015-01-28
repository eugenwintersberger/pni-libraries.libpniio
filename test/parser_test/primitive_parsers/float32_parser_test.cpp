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
//  Created on: Jan 27, 2015
//      Author: Eugen Wintersberger
//

#include "float32_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(float32_parser_test);

//-----------------------------------------------------------------------------
void float32_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void float32_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void float32_parser_test::test_regular_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type v = p.parse("12");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(12,v,1.e-8);

    v = p.parse("-1.234e+4");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.234e+4,v,1.e-8);
}

//-----------------------------------------------------------------------------
void float32_parser_test::test_overflow()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(p.parse("1.ab"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse(" 1."),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1. "),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.E+100"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("-1.E+100"),parser_error);
    result_type v = p.parse("1.E-200");
    CPPUNIT_ASSERT_THROW(p.parse("1.E-100"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("-1.E-100"),parser_error);
    
}

