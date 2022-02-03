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
//  Created on: Dec 27, 2014
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
#include <boost/test/tools/floating_point_comparison.hpp>
#include <pni/types/convert.hpp>

using namespace pni;

typedef int16 source_type;

BOOST_AUTO_TEST_SUITE(convert_int16_test)

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_uint8)
    {
        typedef uint8 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(1)),target_type(1));
        BOOST_CHECK_THROW(convert<target_type>(source_type(-1)),range_error);
        BOOST_CHECK_THROW(convert<target_type>(source_type(1000)),range_error);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_uint16)
    {
        typedef uint16 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_THROW(convert<target_type>(source_type(-1)),range_error);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_uint32)
    {
        typedef uint32 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_THROW(convert<target_type>(source_type(-1)),range_error);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_uint64)
    {
        typedef uint64 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_THROW(convert<target_type>(source_type(-1)),range_error);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_int8)
    {
        typedef int8 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(-20)),
                          target_type(-20));

        BOOST_CHECK_THROW(convert<target_type>(source_type(-1000)),
                          range_error);
        BOOST_CHECK_THROW(convert<target_type>(source_type(1000)),
                          range_error);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_int16)
    {
        typedef int16 target_type;
        
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(-20)),
                          target_type(-20));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_int32)
    {
        typedef int32 target_type;
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(-20)),
                          target_type(-20));
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_int64)
    {
        typedef int64 target_type;
        
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
        BOOST_CHECK_EQUAL(convert<target_type>(source_type(19)),
                          target_type(19));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_float32)
    {
        typedef float32 target_type;
        
        BOOST_CHECK_CLOSE(target_type(19),
                          convert<target_type>(source_type(19)),1.e-6);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_float64)
    {
        typedef float64 target_type;
        
        BOOST_CHECK_CLOSE(target_type(19),
                          convert<target_type>(source_type(19)), 1.e-16);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_float128)
    {
        typedef float128 target_type;
        BOOST_CHECK_CLOSE(target_type(19),
                          convert<target_type>(source_type(19)),1.e-16);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_complex32)
    {
        typedef complex32 target_type;
        typedef float32   base_type;
       
        auto value = convert<target_type>(source_type(19));
        BOOST_CHECK_CLOSE(base_type(19),value.real(),1.e-6);
        BOOST_CHECK_CLOSE(base_type(0),value.imag(),1.e-6);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_complex64)
    {
        typedef complex64 target_type;
        typedef float64   base_type;
        
        auto value = convert<target_type>(source_type(19));
        BOOST_CHECK_CLOSE(base_type(19),value.real(),1.e-16);
        BOOST_CHECK_CLOSE(base_type(0),value.imag(),1.e-16);
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_to_complex128)
    {
        typedef complex128 target_type;
        typedef float128   base_type;
        
        auto value = convert<target_type>(source_type(19));
        BOOST_CHECK_CLOSE(base_type(19),value.real(),1.e-16);
        BOOST_CHECK_CLOSE(base_type(0),value.imag(),1.e-16);
    }

BOOST_AUTO_TEST_SUITE_END()
