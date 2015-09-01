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
//  Created on: Apr 27, 2015
//      Author: Eugen Wintersberger
//


#include <pni/core/types.hpp>
#include <boost/current_function.hpp>
#include "formatters.hpp"
#include "value_formatter_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(value_formatter_test);

using namespace pni::core;

//-----------------------------------------------------------------------------
void value_formatter_test::setUp() { }

//-----------------------------------------------------------------------------
void value_formatter_test::tearDown() {}

//-----------------------------------------------------------------------------
void value_formatter_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint8 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int8 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
    CPPUNIT_ASSERT(format(input_type(itype(-12)))=="-12");
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint16 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int16 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
    CPPUNIT_ASSERT(format(input_type(itype(-12)))=="-12");
}
//-----------------------------------------------------------------------------
void value_formatter_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint32 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int32 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
    CPPUNIT_ASSERT(format(input_type(itype(-12)))=="-12");
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint64 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int64 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(12)))=="12");   
    CPPUNIT_ASSERT(format(input_type(itype(-12)))=="-12");
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float32 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4)))=="1.23e04");     
    CPPUNIT_ASSERT(format(input_type(itype(-1.23e-4)))=="-1.23e-04");       
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float64 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4)))=="1.23e04");   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+123)))=="1.23e123");  
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float128 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4)))=="1.23e04");       
}
//-----------------------------------------------------------------------------
void value_formatter_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex32 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4,4.2)))=="1.23e04+I4.2e00");      
    CPPUNIT_ASSERT(format(input_type(itype(-1.23e-4)))=="-1.23e-04+I0.0e00");       
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex64 itype;
   
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4,-4.2e+3)))=="1.23e04-I4.2e03");   
    CPPUNIT_ASSERT(format(input_type(itype(0.0,-1.23e+123)))=="0.0e00-I1.23e123");  
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex128 itype;
       
    CPPUNIT_ASSERT(format(input_type(itype(1.23e+4,-4.2e+3)))=="1.23e04-I4.2e03");       
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef bool itype;
       
    bool_t v = true;
    CPPUNIT_ASSERT(format(input_type(v))=="true"); 
    v = false;      
    CPPUNIT_ASSERT(format(input_type(v))=="false");       
}

//-----------------------------------------------------------------------------
void value_formatter_test::test_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef string itype;
       
    CPPUNIT_ASSERT(format(input_type(itype("hello world")))=="hello world");       
}
