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
// ===========================================================================
//
//  Created on: May 15, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif 
#include "../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>
#include <pni/arrays/slice.hpp>
#include <iostream>

using namespace pni;

BOOST_AUTO_TEST_SUITE(slice_test)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_construction)
{
    BOOST_CHECK_THROW(slice(1,0),range_error);
    BOOST_CHECK_THROW(slice(1,1),range_error);
    BOOST_CHECK_THROW(slice(1,10,100),range_error);
   
    //test construction without stride
    size_t f=1,l=10;
    slice s(f,l);
    BOOST_CHECK_EQUAL(s.first(),f);
    BOOST_CHECK_EQUAL(s.last(),l);
    BOOST_CHECK_EQUAL(s.stride(),1u);

    //test construction with stride
    size_t stride = 2;
    slice s1(f,l,stride);
    BOOST_CHECK_EQUAL(s1.first(),f);
    BOOST_CHECK_EQUAL(s1.last(),l);
    BOOST_CHECK_EQUAL(s1.stride(),stride);

    //test copy construction
    slice s2(s1);
    BOOST_CHECK_EQUAL(s2.first(),s1.first());
    BOOST_CHECK_EQUAL(s2.last(),s1.last());
    BOOST_CHECK_EQUAL(s2.stride(),s1.stride());

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_assignment)
{
    size_t f=20,l=100,stride=13;
    slice s(f,l,stride);
    slice s1(f,l);

    BOOST_CHECK_NO_THROW(s1 = s);
    BOOST_CHECK_EQUAL(s1.first(), s.first());
    BOOST_CHECK_EQUAL(s1.last(),s.last());
    BOOST_CHECK_EQUAL(s1.stride(),s.stride());

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_functions)
{
    size_t f=20,l=100,stride=13;
    slice s(f,l,stride);

    BOOST_CHECK_EQUAL(size(s),7u);
    BOOST_CHECK_EQUAL(span(s),80u);

    slice s1(1,3,2);
    BOOST_CHECK_EQUAL(size(s1),1u);
    BOOST_CHECK_EQUAL(span(s1),2u);
}

BOOST_AUTO_TEST_SUITE_END()
