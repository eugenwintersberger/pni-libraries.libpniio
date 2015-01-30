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

#include "value_parser_test.hpp"
#include "../../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(value_parser_test);

//-----------------------------------------------------------------------------
void value_parser_test::setUp() { }

//-----------------------------------------------------------------------------
void value_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void value_parser_test::test_int_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type v = p("1234");
    CPPUNIT_ASSERT(v.type_id() == type_id_t::INT64);
}

//-----------------------------------------------------------------------------
void value_parser_test::test_float_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    result_type v = p("1.234e+3");
    CPPUNIT_ASSERT(v.type_id()==type_id_t::FLOAT64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.234e+3,v.as<float64>(),1.e-8);

    v = p("1.2");
    CPPUNIT_ASSERT(v.type_id()==type_id_t::FLOAT64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.2,v.as<float64>(),1.e-8);
}

//-----------------------------------------------------------------------------
void value_parser_test::test_complex_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    result_type v = p("1.3+I3.4");
    CPPUNIT_ASSERT(v.type_id() == type_id_t::COMPLEX64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.3,v.as<complex64>().real(),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.4,v.as<complex64>().imag(),1.e-8);

    v = p("-j3.9");
    CPPUNIT_ASSERT(v.type_id() == type_id_t::COMPLEX64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,v.as<complex64>().real(),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-3.9,v.as<complex64>().imag(),1.e-8);
    
    v = p("j3.9");
    CPPUNIT_ASSERT(v.type_id() == type_id_t::COMPLEX64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,v.as<complex64>().real(),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.9,v.as<complex64>().imag(),1.e-8);

    v = p("1+i4");
    CPPUNIT_ASSERT(v.type_id() == type_id_t::COMPLEX64);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,v.as<complex64>().real(),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0,v.as<complex64>().imag(),1.e-8);

}







