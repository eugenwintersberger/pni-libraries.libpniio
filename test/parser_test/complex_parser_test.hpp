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
#include <pni/io/parsers/complex_parser.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

template<typename T>
class complex_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(complex_parser_test<T>);
    CPPUNIT_TEST(test_complex_zero);
    CPPUNIT_TEST(test_complex_value);
    CPPUNIT_TEST(test_real_only);
    CPPUNIT_TEST(test_imag_only);
	CPPUNIT_TEST_SUITE_END();

    typedef string::const_iterator iterator_t;
    typedef std::complex<T> result_type;
    typedef complex_parser<iterator_t,T> parser_type;
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
    void test_complex_zero();
    void test_complex_value();
    void test_real_only();
    void test_imag_only();
};

//-----------------------------------------------------------------------------
template<typename T> 
void complex_parser_test<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T>
void complex_parser_test<T>::tearDown() {}

//-----------------------------------------------------------------------------
template<typename T>
void complex_parser_test<T>::test_complex_zero()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = parse("0.+i0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.imag(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.real(),1.e-6);
    
    result = parse("0.+I0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.imag(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.real(),1.e-6);
    
    result = parse("0.+j0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.imag(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.real(),1.e-6);
}

//----------------------------------------------------------------------------
template<typename T>
void complex_parser_test<T>::test_complex_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = parse("1.0-j2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(1.0),result.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(-2.0),result.imag(),1.e-6);
}

//----------------------------------------------------------------------------
template<typename T>
void complex_parser_test<T>::test_real_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = parse("1.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(1.0),result.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.imag(),1.e-6);
}

//----------------------------------------------------------------------------
template<typename T>
void complex_parser_test<T>::test_imag_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = parse("-i1e+6");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(-1e+6),result.imag(),1.e-6);
    
    result = parse("-i1e+6");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(0.0),result.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(T(-1e+6),result.imag(),1.e-6);
}


