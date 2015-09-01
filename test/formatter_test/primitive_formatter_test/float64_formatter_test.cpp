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
//  Created on: Feb 11, 2015
//      Author: Eugen Wintersberger
//

#include "formatters.hpp"
#include <boost/current_function.hpp>
#include "float64_formatter_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(float64_formatter_test);

//-----------------------------------------------------------------------------
void float64_formatter_test::setUp() { }

//-----------------------------------------------------------------------------
void float64_formatter_test::tearDown() {}

//-----------------------------------------------------------------------------
void float64_formatter_test::test_format()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    string result = format(input_type(1.2));
    CPPUNIT_ASSERT(result=="1.2e00");

    result = format(input_type(-1.29387702983e-11));
    CPPUNIT_ASSERT(result=="-1.29387702983e-11");
}


