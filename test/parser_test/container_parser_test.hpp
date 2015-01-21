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
//  Created on: Jan 20, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/parsers/container_parser.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

class container_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(container_parser_test);
    CPPUNIT_TEST(test_simple);
    CPPUNIT_TEST(test_overflow);
	CPPUNIT_TEST_SUITE_END();

    typedef string::const_iterator iterator_t;
    typedef std::vector<uint8> result_type;
    typedef container_parser<iterator_t,result_type> parser_type;
    parser_type parser;

    iterator_t start_iter,stop_iter;

    result_type parse(const string &s)
    {
        iterator_t start_iter = s.begin();
        iterator_t stop_iter  = s.end();
        result_type result; 

        boost::spirit::qi::parse(start_iter,stop_iter,parser,result);

        return result;
    }

    

public:
	void setUp();
	void tearDown();
    void test_simple();
    void test_overflow();
};




