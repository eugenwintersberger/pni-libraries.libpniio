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
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "convertible_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(convertible_test);

//-----------------------------------------------------------------------------
void convertible_test::setUp(){ }

//-----------------------------------------------------------------------------
void convertible_test::tearDown(){ }

//-----------------------------------------------------------------------------
void convertible_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    uint_always_pass<uint8>();
    int_always_pass<uint8>();
    float_always_pass<uint8>();
    complex_always_pass<uint8>();
    always_fails<uint8>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    uint_always_pass<uint16>();
    int_always_pass<uint16>();
    float_always_pass<uint16>();
    complex_always_pass<uint16>();
    always_fails<uint16>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<uint32>();
    int_always_pass<uint32>();
    float_always_pass<uint32>();
    complex_always_pass<uint32>();
    always_fails<uint32>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<uint64>();
    int_always_pass<uint64>();
    float_always_pass<uint64>();
    complex_always_pass<uint64>();
    always_fails<uint64>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int8>();
    int_always_pass<int8>();
    float_always_pass<int8>();
    complex_always_pass<int8>();
    always_fails<int8>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int16>();
    int_always_pass<int16>();
    float_always_pass<int16>();
    complex_always_pass<int16>();
    always_fails<int16>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int32>();
    int_always_pass<int32>();
    float_always_pass<int32>();
    complex_always_pass<int32>();
    always_fails<int32>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int64>();
    int_always_pass<int64>();
    float_always_pass<int64>();
    complex_always_pass<int64>();
    always_fails<int64>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float32>();
    int_always_fails<float32>();
    float_always_pass<float32>();
    complex_always_pass<float32>();
    always_fails<float32>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float64>();
    int_always_fails<float64>();
    float_always_pass<float64>();
    complex_always_pass<float64>();
    always_fails<float64>();

}

//-----------------------------------------------------------------------------
void convertible_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float128>();
    int_always_fails<float128>();

    float_always_pass<float128>();
    complex_always_pass<float128>();
    always_fails<float128>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex32>();
    int_always_fails<complex32>();
    float_always_fails<complex32>();

    complex_always_pass<complex32>();
    always_fails<complex32>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex64>();
    int_always_fails<complex64>();
    float_always_fails<complex64>(); 
    complex_always_pass<complex64>();
    always_fails<complex64>();
}

//-----------------------------------------------------------------------------
void convertible_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex128>();
    int_always_fails<complex128>();
    float_always_fails<complex128>();
    
    complex_always_pass<complex128>();
   
    always_fails<complex128>();
}
