//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Dec 20, 2014
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>
#include<h5cpp/contrib/nexus/ebool.hpp>

#include <pni/types/convertible.hpp>

using namespace pni;

class convertible_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(convertible_test);
        CPPUNIT_TEST(test_uint8);
        CPPUNIT_TEST(test_uint16);
        CPPUNIT_TEST(test_uint32);
        CPPUNIT_TEST(test_uint64);
        CPPUNIT_TEST(test_int8);
        CPPUNIT_TEST(test_int16);
        CPPUNIT_TEST(test_int32);
        CPPUNIT_TEST(test_int64);
        CPPUNIT_TEST(test_float32);
        CPPUNIT_TEST(test_float64);
        CPPUNIT_TEST(test_float128);
        CPPUNIT_TEST(test_complex32);
        CPPUNIT_TEST(test_complex64);
        CPPUNIT_TEST(test_complex128);
        CPPUNIT_TEST_SUITE_END();

        //--------------------------------------------------------------------
        template<typename GeneralT> void always_fails()
        {
            CPPUNIT_ASSERT(!(convertible<GeneralT,bool_t>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,hdf5::datatype::EBool>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,binary>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,string>::value));
        }

        //--------------------------------------------------------------------
        template<typename GeneralT> void uint_always_fails()
        {
            CPPUNIT_ASSERT(!(convertible<GeneralT,uint8>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,uint16>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,uint32>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,uint64>::value));
        }

        //--------------------------------------------------------------------
        template<typename GeneralT> void int_always_fails()
        {
            CPPUNIT_ASSERT(!(convertible<GeneralT,int8>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,int16>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,int32>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,int64>::value));
        }

        //--------------------------------------------------------------------
        template<typename GeneralT> void float_always_fails()
        {
            CPPUNIT_ASSERT(!(convertible<GeneralT,float32>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,float64>::value));
            CPPUNIT_ASSERT(!(convertible<GeneralT,float128>::value));
        }
        
        //--------------------------------------------------------------------
        template<typename GeneralT> void float_always_pass()
        {
            CPPUNIT_ASSERT((convertible<GeneralT,float32>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,float64>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,float128>::value));
        }

        //--------------------------------------------------------------------
        template<typename GeneralT> void complex_always_pass()
        {
            CPPUNIT_ASSERT((convertible<GeneralT,complex32>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,complex64>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,complex128>::value));
        }
        
        //--------------------------------------------------------------------
        template<typename GeneralT> void uint_always_pass()
        {
            CPPUNIT_ASSERT((convertible<GeneralT,uint8>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,uint16>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,uint32>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,uint64>::value));
        }

        //--------------------------------------------------------------------
        template<typename GeneralT> void int_always_pass()
        {
            CPPUNIT_ASSERT((convertible<GeneralT,int8>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,int16>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,int32>::value));
            CPPUNIT_ASSERT((convertible<GeneralT,int64>::value));
        }
    public:
        void setUp();
        void tearDown();
        void test_uint8();
        void test_uint16();
        void test_uint32();
        void test_uint64();
        void test_int8();
        void test_int16();
        void test_int32();
        void test_int64();
        void test_float32();
        void test_float64();
        void test_float128();
        void test_complex32();
        void test_complex64();
        void test_complex128();

};
