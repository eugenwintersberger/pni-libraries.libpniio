//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ============================================================================
//
//  Created on: Feb 08, 2012
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
#include <iostream>
#include <pni/types.hpp>

using namespace pni;


BOOST_AUTO_TEST_SUITE(binary_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_construction)
    {
        binary bvalue = 8; 
        BOOST_CHECK_EQUAL(bvalue,8);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_comparison)
    {
        binary v1 = 8;
        binary v2 = 10;
        binary v3 = 8;

        BOOST_CHECK_NE(v1,v2);
        BOOST_CHECK_EQUAL(v1,v3);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        binary v1;

        v1 = 10;

        binary v2 = 10;
        BOOST_CHECK_EQUAL(v1,v2);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_compatability)
    {
        typedef binary_t<uint8> binary_type;
        uint8 rv;
        binary_type bv = 10;
       
        //this should work
        rv = bv;
        BOOST_CHECK_EQUAL(rv,bv);
        rv = 100;
        bv = rv;
        BOOST_CHECK_EQUAL(bv,rv);

        //should not work
        float64 f64 = 12.3445;
        bv = f64;

        uint8 *rptr = new uint8[10];
        binary_type *bptr = new binary_type[10];

		//the number range for the loop is ok for uint8
        for(uint8 i=0;i<10;i++)
        {
            rptr[i] = i;
            bptr[i] = i;
        }

        for(size_t i=0;i<10;i++) 
            BOOST_CHECK_EQUAL(rptr[i],bptr[i]);


        delete [] rptr;
        delete [] bptr;
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_io_operator)
    {
        binary  b = 'a';

        BOOST_CHECK_EQUAL(b,'a');
        b = 'x';
        BOOST_CHECK_EQUAL(b,'x');

        binary::storage_type bvalue;

        bvalue = b;
        BOOST_CHECK_EQUAL(bvalue,'x');
        
        int8 ivalue = 'z';
        b = ivalue;
    }

BOOST_AUTO_TEST_SUITE_END()
