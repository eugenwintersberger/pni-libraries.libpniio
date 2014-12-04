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

#include "bool_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(bool_fixture);

//-----------------------------------------------------------------------------
void bool_fixture::setUp() { }

//-----------------------------------------------------------------------------
void bool_fixture::tearDown() { } 

//-----------------------------------------------------------------------------
void bool_fixture::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<bool> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("true"));
    CPPUNIT_ASSERT(decoder.decode("1"));
    CPPUNIT_ASSERT(decoder.decode("True"));
    
    CPPUNIT_ASSERT(!decoder.decode("0"));
    CPPUNIT_ASSERT(!decoder.decode("false"));
    CPPUNIT_ASSERT(!decoder.decode("False"));

    CPPUNIT_ASSERT_THROW(decoder.decode("bla"),pni::core::value_error);
}

//-----------------------------------------------------------------------------
void bool_fixture::test_bool_t()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef xml::decoder<bool_t> decoder_type;
    decoder_type decoder;

    CPPUNIT_ASSERT(decoder.decode("true"));
    CPPUNIT_ASSERT(decoder.decode("1"));
    CPPUNIT_ASSERT(decoder.decode("True"));
    
    CPPUNIT_ASSERT(!decoder.decode("false"));
    CPPUNIT_ASSERT(!decoder.decode("0"));
    CPPUNIT_ASSERT(!decoder.decode("False"));
    
    CPPUNIT_ASSERT_THROW(decoder.decode("bla"),pni::core::value_error);
}


