/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 9, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "utils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(utils_test);

//-----------------------------------------------------------------------------
void utils_test::setUp() { }

//-----------------------------------------------------------------------------
void utils_test::tearDown() { }

//-----------------------------------------------------------------------------
void utils_test::test_str2typeid()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(str2typeid["uint8"] == type_id_t::UINT8);
    CPPUNIT_ASSERT(str2typeid["int8"] == type_id_t::INT8);
    CPPUNIT_ASSERT(str2typeid["uint16"] == type_id_t::UINT16);
    CPPUNIT_ASSERT(str2typeid["int16"] == type_id_t::INT16);
    CPPUNIT_ASSERT(str2typeid["uint32"] == type_id_t::UINT32);
    CPPUNIT_ASSERT(str2typeid["int32"] == type_id_t::INT32);
    CPPUNIT_ASSERT(str2typeid["uint64"] == type_id_t::UINT64);
    CPPUNIT_ASSERT(str2typeid["int64"] == type_id_t::INT64);

    CPPUNIT_ASSERT(str2typeid["float32"] == type_id_t::FLOAT32);
    CPPUNIT_ASSERT(str2typeid["float64"] == type_id_t::FLOAT64);
    CPPUNIT_ASSERT(str2typeid["float128"] == type_id_t::FLOAT128);

    CPPUNIT_ASSERT(str2typeid["complex32"] == type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(str2typeid["complex64"] == type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(str2typeid["complex128"] == type_id_t::COMPLEX128);

    CPPUNIT_ASSERT(str2typeid["string"] == type_id_t::STRING);
    CPPUNIT_ASSERT(str2typeid["binary"] == type_id_t::BINARY);
    CPPUNIT_ASSERT(str2typeid["bool"] == type_id_t::BOOL);

}

//-----------------------------------------------------------------------------
void utils_test::test_typeid2str()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(typeid2str[type_id_t::UINT8] == "uint8");
    CPPUNIT_ASSERT(typeid2str[type_id_t::INT8]  == "int8");
    CPPUNIT_ASSERT(typeid2str[type_id_t::UINT16] == "uint16");
    CPPUNIT_ASSERT(typeid2str[type_id_t::INT16]  == "int16");
    CPPUNIT_ASSERT(typeid2str[type_id_t::UINT32] == "uint32");
    CPPUNIT_ASSERT(typeid2str[type_id_t::INT32]  == "int32");
    CPPUNIT_ASSERT(typeid2str[type_id_t::UINT64] == "uint64");
    CPPUNIT_ASSERT(typeid2str[type_id_t::INT64]  == "int64");

    CPPUNIT_ASSERT(typeid2str[type_id_t::FLOAT32] == "float32");
    CPPUNIT_ASSERT(typeid2str[type_id_t::FLOAT64] == "float64");
    CPPUNIT_ASSERT(typeid2str[type_id_t::FLOAT128] == "float128");

    CPPUNIT_ASSERT(typeid2str[type_id_t::COMPLEX32] == "complex32");
    CPPUNIT_ASSERT(typeid2str[type_id_t::COMPLEX64] == "complex64");
    CPPUNIT_ASSERT(typeid2str[type_id_t::COMPLEX128] == "complex128");

    CPPUNIT_ASSERT(typeid2str[type_id_t::STRING] == "string");
    CPPUNIT_ASSERT(typeid2str[type_id_t::BINARY] == "binary");
    CPPUNIT_ASSERT(typeid2str[type_id_t::BOOL] == "bool");

}
