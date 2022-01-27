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
//  Created on: Dec 18, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif 
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/types/unchecked_convertible.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

using namespace pni;

BOOST_AUTO_TEST_SUITE(unchecked_convertible_test)

    //=========================================================================
    template<typename T> void always_fails()
    {
        BOOST_CHECK(!(unchecked_convertible<T,bool_t>::value));
        BOOST_CHECK(!(unchecked_convertible<T,hdf5::datatype::EBool>::value));
        BOOST_CHECK(!(unchecked_convertible<T,binary>::value));
        BOOST_CHECK(!(unchecked_convertible<T,string>::value));
    }

    //=========================================================================
    template<typename T> void uint_always_fails()
    {
        BOOST_CHECK(!(unchecked_convertible<T,uint8>::value));
        BOOST_CHECK(!(unchecked_convertible<T,uint16>::value));
        BOOST_CHECK(!(unchecked_convertible<T,uint32>::value));
        BOOST_CHECK(!(unchecked_convertible<T,uint64>::value));
    }

    //=========================================================================
    template<typename T> void int_always_fails()
    {
        BOOST_CHECK(!(unchecked_convertible<T,int8>::value));
        BOOST_CHECK(!(unchecked_convertible<T,int16>::value));
        BOOST_CHECK(!(unchecked_convertible<T,int32>::value));
        BOOST_CHECK(!(unchecked_convertible<T,int64>::value));
    }

    //=========================================================================
    template<typename T> void float_always_fails()
    {
        BOOST_CHECK(!(unchecked_convertible<T,float32>::value));
        BOOST_CHECK(!(unchecked_convertible<T,float64>::value));
        BOOST_CHECK(!(unchecked_convertible<T,float128>::value));
    }
    
    //=========================================================================
    template<typename T> void float_always_pass()
    {
        BOOST_CHECK((unchecked_convertible<T,float32>::value));
        BOOST_CHECK((unchecked_convertible<T,float64>::value));
        BOOST_CHECK((unchecked_convertible<T,float128>::value));
    }

    //=========================================================================
    template<typename T> void complex_always_pass()
    {
        BOOST_CHECK((unchecked_convertible<T,complex32>::value));
        BOOST_CHECK((unchecked_convertible<T,complex64>::value));
        BOOST_CHECK((unchecked_convertible<T,complex128>::value));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8)
    {
        BOOST_CHECK((unchecked_convertible<uint8,uint8>::value));
        BOOST_CHECK((unchecked_convertible<uint8,uint16>::value));
        BOOST_CHECK((unchecked_convertible<uint8,uint32>::value));
        BOOST_CHECK((unchecked_convertible<uint8,uint64>::value));

        BOOST_CHECK(!(unchecked_convertible<uint8,int8>::value));
        BOOST_CHECK((unchecked_convertible<uint8,int16>::value));
        BOOST_CHECK((unchecked_convertible<uint8,int32>::value));
        BOOST_CHECK((unchecked_convertible<uint8,int64>::value));

        float_always_pass<uint8>();
        complex_always_pass<uint8>();
        always_fails<uint8>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint16)
    {
        BOOST_CHECK(!(unchecked_convertible<uint16,uint8>::value));
        BOOST_CHECK((unchecked_convertible<uint16,uint16>::value));
        BOOST_CHECK((unchecked_convertible<uint16,uint32>::value));
        BOOST_CHECK((unchecked_convertible<uint16,uint64>::value));

        BOOST_CHECK(!(unchecked_convertible<uint16,int8>::value));
        BOOST_CHECK(!(unchecked_convertible<uint16,int16>::value));
        BOOST_CHECK((unchecked_convertible<uint16,int32>::value));
        BOOST_CHECK((unchecked_convertible<uint16,int64>::value));

        float_always_pass<uint16>();
        complex_always_pass<uint16>();
        always_fails<uint16>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint32)
    {
        BOOST_CHECK(!(unchecked_convertible<uint32,uint8>::value));
        BOOST_CHECK(!(unchecked_convertible<uint32,uint16>::value));
        BOOST_CHECK((unchecked_convertible<uint32,uint32>::value));
        BOOST_CHECK((unchecked_convertible<uint32,uint64>::value));

        BOOST_CHECK(!(unchecked_convertible<uint32,int8>::value));
        BOOST_CHECK(!(unchecked_convertible<uint32,int16>::value));
        BOOST_CHECK(!(unchecked_convertible<uint32,int32>::value));
        BOOST_CHECK((unchecked_convertible<uint32,int64>::value));

        float_always_pass<uint32>();
        complex_always_pass<uint32>();
        always_fails<uint32>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint64)
    {
        BOOST_CHECK(!(unchecked_convertible<uint64,uint8>::value));
        BOOST_CHECK(!(unchecked_convertible<uint64,uint16>::value));
        BOOST_CHECK(!(unchecked_convertible<uint64,uint32>::value));
        BOOST_CHECK((unchecked_convertible<uint64,uint64>::value));

        int_always_fails<uint64>();
        float_always_pass<uint64>();
        complex_always_pass<uint64>();
        always_fails<uint64>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_int8)
    {
        uint_always_fails<int8>();

        BOOST_CHECK((unchecked_convertible<int8,int8>::value));
        BOOST_CHECK((unchecked_convertible<int8,int16>::value));
        BOOST_CHECK((unchecked_convertible<int8,int32>::value));
        BOOST_CHECK((unchecked_convertible<int8,int64>::value));

        float_always_pass<int8>();
        complex_always_pass<int8>();
        always_fails<int8>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_int16)
    {
        uint_always_fails<int16>();

        BOOST_CHECK(!(unchecked_convertible<int16,int8>::value));
        BOOST_CHECK((unchecked_convertible<int16,int16>::value));
        BOOST_CHECK((unchecked_convertible<int16,int32>::value));
        BOOST_CHECK((unchecked_convertible<int16,int64>::value));

        float_always_pass<int16>();
        complex_always_pass<int16>();
        always_fails<int16>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_int32)
    {
        uint_always_fails<int32>();

        BOOST_CHECK(!(unchecked_convertible<int32,int8>::value));
        BOOST_CHECK(!(unchecked_convertible<int32,int16>::value));
        BOOST_CHECK((unchecked_convertible<int32,int32>::value));
        BOOST_CHECK((unchecked_convertible<int32,int64>::value));

        float_always_pass<int32>();
        complex_always_pass<int32>();
        always_fails<int32>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_int64)
    {
        uint_always_fails<int64>();

        BOOST_CHECK(!(unchecked_convertible<int64,int8>::value));
        BOOST_CHECK(!(unchecked_convertible<int64,int16>::value));
        BOOST_CHECK(!(unchecked_convertible<int64,int32>::value));
        BOOST_CHECK((unchecked_convertible<int64,int64>::value));

        float_always_pass<int64>();
        complex_always_pass<int64>();
        always_fails<int64>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_float32)
    {
        uint_always_fails<float32>();
        int_always_fails<float32>();

        float_always_pass<float32>();
        complex_always_pass<float32>();
        always_fails<float32>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_float64)
    {
        uint_always_fails<float64>();
        int_always_fails<float64>();

        BOOST_CHECK(!(unchecked_convertible<float64,float32>::value));
        BOOST_CHECK((unchecked_convertible<float64,float64>::value));
        BOOST_CHECK((unchecked_convertible<float64,float128>::value));
        
        BOOST_CHECK(!(unchecked_convertible<float64,complex32>::value));
        BOOST_CHECK((unchecked_convertible<float64,complex64>::value));
        BOOST_CHECK((unchecked_convertible<float64,complex128>::value));
        
        always_fails<float64>();

    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_float128)
    {
        uint_always_fails<float128>();
        int_always_fails<float128>();

        BOOST_CHECK(!(unchecked_convertible<float128,float32>::value));
        BOOST_CHECK(!(unchecked_convertible<float128,float64>::value));
        BOOST_CHECK((unchecked_convertible<float128,float128>::value));
        
        BOOST_CHECK(!(unchecked_convertible<float128,complex32>::value));
        BOOST_CHECK(!(unchecked_convertible<float128,complex64>::value));
        BOOST_CHECK((unchecked_convertible<float128,complex128>::value));
       
        always_fails<float128>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_complex32)
    {
        uint_always_fails<complex32>();
        int_always_fails<complex32>();

        float_always_fails<complex32>();

        BOOST_CHECK((unchecked_convertible<complex32,complex32>::value));
        BOOST_CHECK((unchecked_convertible<complex32,complex64>::value));
        BOOST_CHECK((unchecked_convertible<complex32,complex128>::value));

        always_fails<complex32>();
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_complex64)
    {
        uint_always_fails<complex64>();
        int_always_fails<complex64>();

        float_always_fails<complex64>(); 
        BOOST_CHECK(!(unchecked_convertible<complex64,complex32>::value));
        BOOST_CHECK((unchecked_convertible<complex64,complex64>::value));
        BOOST_CHECK((unchecked_convertible<complex64,complex128>::value));
        
        always_fails<complex64>();

    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_complex128)
    {
        uint_always_fails<complex128>();
        int_always_fails<complex128>();
        float_always_fails<complex128>();
        
        BOOST_CHECK(!(unchecked_convertible<complex128,complex32>::value));
        BOOST_CHECK(!(unchecked_convertible<complex128,complex64>::value));
        BOOST_CHECK((unchecked_convertible<complex128,complex128>::value));
       
        always_fails<complex128>();
    }

BOOST_AUTO_TEST_SUITE_END()
