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
//  Created on: Dec 4, 2014
//      Author: Eugen Wintersberger
//

#include "float_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(float_fixture);

//-----------------------------------------------------------------------------
void float_fixture::setUp() { }

//-----------------------------------------------------------------------------
void float_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void float_fixture::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<float32> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.234,decoder.decode("1.234"),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10.34e-3,decoder.decode("-10.34e-3"),1.e-6);
    CPPUNIT_ASSERT_THROW(decoder.decode("1.e+300"),pni::core::range_error);
    CPPUNIT_ASSERT_THROW(decoder.decode("-1.e+300"),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void float_fixture::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<float64> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.234,decoder.decode("1.234"),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10.34e-3,decoder.decode("-10.34e-3"),1.e-8);
    CPPUNIT_ASSERT_THROW(decoder.decode("1.e+400"),pni::core::range_error);
    CPPUNIT_ASSERT_THROW(decoder.decode("-1.e+400"),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void float_fixture::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<float128> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.234,decoder.decode("1.234"),1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10.34e-3,decoder.decode("-10.34e-3"),1.e-8);

    //cannot test this currently
    //CPPUNIT_ASSERT_THROW(decoder.decode("40000000000"),pni::core::range_error);
    //CPPUNIT_ASSERT_THROW(decoder.decode("-40000000000"),pni::core::range_error);
}

