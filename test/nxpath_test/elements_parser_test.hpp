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

#pragma once

#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath/parser.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using namespace pni::io::nx::parsers;

//!
//! \ingroup test_code
//! \brief test elements_parser
//! 
//! Test the elements parser component for the Nexus path parser.
//!
class elements_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(elements_parser_test);
    CPPUNIT_TEST(test_relative);
    CPPUNIT_TEST(test_relative_current);
    CPPUNIT_TEST(test_relative_parent);
    CPPUNIT_TEST(test_errors);
	CPPUNIT_TEST_SUITE_END();


    typedef string::const_iterator iterator_type;
    typedef elements_parser<iterator_type> elements_parser_type;
    typedef boost::spirit::qi::expectation_failure<iterator_type> 
            expectation_error_type;
    elements_parser_type parser;

    iterator_type start_iter,stop_iter;
    string input;
    nxpath::elements_type output;
    nxpath::element_type element;

    void set_input(const string &value)
    {
        input = value;
        start_iter = input.begin();
        stop_iter  = input.end();
    }
public:
	void setUp();
	void tearDown();


    //------------------------------------------------------------------------
    //!
    //! \brief test root group parsing
    //!
    //! Test parsing only the root group.
    //!
    void test_relative();
    void test_relative_current();
    void test_relative_parent();

    void test_errors();


};


