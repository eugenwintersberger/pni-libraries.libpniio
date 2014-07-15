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
// ============================================================================
//
// Created on: Jul 14, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "h5datatype_test.hpp"
#include <boost/current_function.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(h5datatype_test);


//----------------------------------------------------------------------------
void h5datatype_test::setUp()
{
}

//----------------------------------------------------------------------------
void h5datatype_test::tearDown()
{
}

//----------------------------------------------------------------------------
void h5datatype_test::test_type_id()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::UINT8))==type_id_t::UINT8);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::INT8))==type_id_t::INT8);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::UINT16))==type_id_t::UINT16);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::INT16))==type_id_t::INT16);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::UINT32))==type_id_t::UINT32);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::INT32))==type_id_t::INT32);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::UINT64))==type_id_t::UINT64);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::INT64))==type_id_t::INT64);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::FLOAT32))==type_id_t::FLOAT32);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::FLOAT64))==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::FLOAT128))==type_id_t::FLOAT128);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::COMPLEX32))==
                   type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::COMPLEX64))==
                   type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::COMPLEX128))==
                   type_id_t::COMPLEX128);

    CPPUNIT_ASSERT(type_id(get_type(type_id_t::BOOL)) == type_id_t::BOOL);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::STRING)) == type_id_t::STRING);
    CPPUNIT_ASSERT(type_id(get_type(type_id_t::BINARY)) == type_id_t::BINARY);
}
