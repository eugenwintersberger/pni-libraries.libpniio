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

#include "int_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(int_fixture);

//-----------------------------------------------------------------------------
void int_fixture::setUp() { }

//-----------------------------------------------------------------------------
void int_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void int_fixture::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<int8> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("1")==1);
    CPPUNIT_ASSERT(decoder.decode("-1") == -1);
    CPPUNIT_ASSERT_THROW(decoder.decode("2000"),pni::core::range_error);
    CPPUNIT_ASSERT_THROW(decoder.decode("-2000"),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void int_fixture::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<int16> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("1")==1);
    CPPUNIT_ASSERT(decoder.decode("-1")==-1);
    CPPUNIT_ASSERT_THROW(decoder.decode("70000"),pni::core::range_error);
    CPPUNIT_ASSERT_THROW(decoder.decode("-70000"),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void int_fixture::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<int32> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("1")==1);
    CPPUNIT_ASSERT(decoder.decode("-1")==-1);
    CPPUNIT_ASSERT_THROW(decoder.decode("40000000000"),pni::core::range_error);
    CPPUNIT_ASSERT_THROW(decoder.decode("-40000000000"),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void int_fixture::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<int64> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("1")==1);
    CPPUNIT_ASSERT(decoder.decode("-1")==-1);
    // we cannot do this check for now - need a better solution for this
    /*
    CPPUNIT_ASSERT_THROW(decoder.decode("100000000000000000000000"),
                         pni::core::range_error);
                         */
}
