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
//  Created on: Jan 29, 2015
//      Author: Eugen Wintersberger
//

#include "complex128_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(complex128_parser_test);

#define NUM_RES 1.e-12

//-----------------------------------------------------------------------------
void complex128_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void complex128_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void complex128_parser_test::test_regular_value_for_j()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = p.parse("1.0+j2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("-1.0+j2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("1.0-j2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
    
    result = p.parse("-1.0-j2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
}

//-----------------------------------------------------------------------------
void complex128_parser_test::test_regular_value_for_i()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = p.parse("1.0+i2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("-1.0+i2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("1.0-i2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
    
    result = p.parse("-1.0-i2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
}

//-----------------------------------------------------------------------------
void complex128_parser_test::test_regular_value_for_I()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = p.parse("1.0+I2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("-1.0+I2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+2.0),result.imag(),NUM_RES);

    result = p.parse("1.0-I2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(+1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
    
    result = p.parse("-1.0-I2.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-2.0),result.imag(),NUM_RES);
}
//-----------------------------------------------------------------------------
void complex128_parser_test::test_invalid_input()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT_THROW(p.parse("1.+A5."),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.e+2-Ie"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.e+3-I1e+x"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.+j-1"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.+j+1"),parser_error);
    CPPUNIT_ASSERT_THROW(p.parse("1.j2"),parser_error);
}

//----------------------------------------------------------------------------
void complex128_parser_test::test_complex_zero()
{
    result_type result = p.parse("0.+i0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(),NUM_RES);
    
    result = p.parse("0.+I0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(),NUM_RES);
    
    result = p.parse("0.+j0.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(),NUM_RES);
}

//----------------------------------------------------------------------------
void complex128_parser_test::test_real_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = p.parse("1.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(),NUM_RES);

    result = p.parse("-1.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(), NUM_RES);
    
    result = p.parse("+1.0");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(1.0),result.real(),NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.imag(),NUM_RES);
}

//----------------------------------------------------------------------------
void complex128_parser_test::test_imag_only()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type result = p.parse("-i1e+6");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(),  NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-1e+6),result.imag(),NUM_RES);
    
    result = p.parse("+i1e+6");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(), NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(1e+6),result.imag(),NUM_RES);
    
    result = p.parse("i2e+6");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(0.0),result.real(), NUM_RES);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(2e+6),result.imag(),NUM_RES);
}
