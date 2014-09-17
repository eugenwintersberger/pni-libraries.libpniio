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
//************************************************************************
//
//  Created on: Sep 17, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include <boost/current_function.hpp>
#include <boost/lexical_cast.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "cbf_reader_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(cbf_reader_test);

//-----------------------------------------------------------------------------
void cbf_reader_test::setUp() { }

//-----------------------------------------------------------------------------
void cbf_reader_test::tearDown() { }

//-----------------------------------------------------------------------------
void cbf_reader_test::test_read_header()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_THROW(cbf_reader("reader_test.cpp"),file_error);

}

