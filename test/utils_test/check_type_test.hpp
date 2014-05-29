//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 9, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <type_traits>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nexus_utils.hpp>

using namespace pni::core;
using namespace pni::io::nx;


template<typename TA>
class check_type_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(check_type_test<TA>);
        CPPUNIT_TEST(test_type<uint8>);
        CPPUNIT_TEST(test_type<int8>);
        CPPUNIT_TEST(test_type<uint16>);
        CPPUNIT_TEST(test_type<int16>);
        CPPUNIT_TEST(test_type<uint32>);
        CPPUNIT_TEST(test_type<int32>);
        CPPUNIT_TEST(test_type<uint64>);
        CPPUNIT_TEST(test_type<int64>);
        CPPUNIT_TEST(test_type<float32>);
        CPPUNIT_TEST(test_type<float64>);
        CPPUNIT_TEST(test_type<float128>);
        CPPUNIT_TEST(test_type<complex32>);
        CPPUNIT_TEST(test_type<complex64>);
        CPPUNIT_TEST(test_type<complex128>);
        CPPUNIT_TEST(test_type<string>);
        CPPUNIT_TEST(test_type<binary>);
        CPPUNIT_TEST(test_type<bool_t>);
        
        CPPUNIT_TEST(test_type_throw<uint8>);
        CPPUNIT_TEST(test_type_throw<int8>);
        CPPUNIT_TEST(test_type_throw<uint16>);
        CPPUNIT_TEST(test_type_throw<int16>);
        CPPUNIT_TEST(test_type_throw<uint32>);
        CPPUNIT_TEST(test_type_throw<int32>);
        CPPUNIT_TEST(test_type_throw<uint64>);
        CPPUNIT_TEST(test_type_throw<int64>);
        CPPUNIT_TEST(test_type_throw<float32>);
        CPPUNIT_TEST(test_type_throw<float64>);
        CPPUNIT_TEST(test_type_throw<float128>);
        CPPUNIT_TEST(test_type_throw<complex32>);
        CPPUNIT_TEST(test_type_throw<complex64>);
        CPPUNIT_TEST(test_type_throw<complex128>);
        CPPUNIT_TEST(test_type_throw<string>);
        CPPUNIT_TEST(test_type_throw<binary>);
        CPPUNIT_TEST(test_type_throw<bool_t>);
        
        CPPUNIT_TEST(test_str<uint8>);
        CPPUNIT_TEST(test_str<int8>);
        CPPUNIT_TEST(test_str<uint16>);
        CPPUNIT_TEST(test_str<int16>);
        CPPUNIT_TEST(test_str<uint32>);
        CPPUNIT_TEST(test_str<int32>);
        CPPUNIT_TEST(test_str<uint64>);
        CPPUNIT_TEST(test_str<int64>);
        CPPUNIT_TEST(test_str<float32>);
        CPPUNIT_TEST(test_str<float64>);
        CPPUNIT_TEST(test_str<float128>);
        CPPUNIT_TEST(test_str<complex32>);
        CPPUNIT_TEST(test_str<complex64>);
        CPPUNIT_TEST(test_str<complex128>);
        CPPUNIT_TEST(test_str<string>);
        CPPUNIT_TEST(test_str<binary>);
        CPPUNIT_TEST(test_str<bool_t>);
        
        CPPUNIT_TEST(test_str_throw<uint8>);
        CPPUNIT_TEST(test_str_throw<int8>);
        CPPUNIT_TEST(test_str_throw<uint16>);
        CPPUNIT_TEST(test_str_throw<int16>);
        CPPUNIT_TEST(test_str_throw<uint32>);
        CPPUNIT_TEST(test_str_throw<int32>);
        CPPUNIT_TEST(test_str_throw<uint64>);
        CPPUNIT_TEST(test_str_throw<int64>);
        CPPUNIT_TEST(test_str_throw<float32>);
        CPPUNIT_TEST(test_str_throw<float64>);
        CPPUNIT_TEST(test_str_throw<float128>);
        CPPUNIT_TEST(test_str_throw<complex32>);
        CPPUNIT_TEST(test_str_throw<complex64>);
        CPPUNIT_TEST(test_str_throw<complex128>);
        CPPUNIT_TEST(test_str_throw<string>);
        CPPUNIT_TEST(test_str_throw<binary>);
        CPPUNIT_TEST(test_str_throw<bool_t>);
        CPPUNIT_TEST_SUITE_END();
        
        h5::nxfile file;
        h5::nxfield field;
        
    public:
        void setUp();
        void tearDown();
       
        
        template<typename TB> void test_type();
        template<typename TB> void test_type_throw();
        template<typename TB> void test_str();
        template<typename TB> void test_str_throw();

};

//-----------------------------------------------------------------------------
template<typename TA>
void check_type_test<TA>::setUp()
{
    file = h5::nxfile::create_file("check_type_test.nx",true);
    field = file.root().create_field<TA>("test");
}

//-----------------------------------------------------------------------------
template<typename TA>
void check_type_test<TA>::tearDown()
{
    field.close();
    file.close();
}

//-----------------------------------------------------------------------------
template<typename TA>
template<typename TB>
void check_type_test<TA>::test_type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    bool res = std::is_same<TA,TB>::value == check_type<TB>(field);
    CPPUNIT_ASSERT(res);

}

//-----------------------------------------------------------------------------
template<typename TA>
template<typename TB>
void check_type_test<TA>::test_type_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    if(std::is_same<TA,TB>::value)
        CPPUNIT_ASSERT_NO_THROW(check_type<TB>(field,EXCEPTION_RECORD));
    else
        CPPUNIT_ASSERT_THROW(check_type<TB>(field,EXCEPTION_RECORD),
                             type_error);
}

//-----------------------------------------------------------------------------
template<typename TA>
template<typename TB>
void check_type_test<TA>::test_str()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_id_t id = type_id_map<TB>::type_id;
    string s = str_from_type_id(id);

    bool res = std::is_same<TA,TB>::value == check_type(field,s);
    CPPUNIT_ASSERT(res);

}

//-----------------------------------------------------------------------------
template<typename TA>
template<typename TB>
void check_type_test<TA>::test_str_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_id_t id = type_id_map<TB>::type_id;
    string s = str_from_type_id(id);

    if(std::is_same<TA,TB>::value)
        CPPUNIT_ASSERT_NO_THROW(check_type(field,s,EXCEPTION_RECORD));
    else
        CPPUNIT_ASSERT_THROW(check_type(field,s,EXCEPTION_RECORD),type_error);

}

