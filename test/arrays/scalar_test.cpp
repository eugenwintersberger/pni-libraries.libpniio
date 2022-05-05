//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Sep 02, 2011
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
#include "../data_generator.hpp"
#include <typeinfo>
#include <pni/arrays/scalar.hpp>

using namespace pni;

template<typename GeneralT> struct scalar_fixture
{
    typedef random_generator<GeneralT> generator_type;
    generator_type generator;
    GeneralT v;

    scalar_fixture():
        generator(),
        v(generator())
    {}
};

#define PNINEXUS_SETUP_SCALAR_FIXTURE() \
    typedef scalar_fixture<GeneralT> fixture_type; \
    fixture_type fixture

BOOST_AUTO_TEST_SUITE(scalar_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,GeneralT,numeric_types)   
    {
        PNINEXUS_SETUP_SCALAR_FIXTURE();

        scalar<GeneralT> s;
        BOOST_CHECK_EQUAL(s.rank(),0u);
        BOOST_CHECK_EQUAL(s.size(),1u);

        //check the default constructor
        scalar<GeneralT> s1(fixture.v);
        BOOST_CHECK_EQUAL(GeneralT(s1),fixture.v);

        //copy construction
        scalar<GeneralT> s2 = s1;
        BOOST_CHECK_EQUAL(GeneralT(s2),GeneralT(s1));
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment,GeneralT,numeric_types)
    {
        PNINEXUS_SETUP_SCALAR_FIXTURE();

        scalar<GeneralT> s(fixture.v);
        scalar<GeneralT> a;

        a = s;
        BOOST_CHECK_EQUAL(GeneralT(a),GeneralT(s));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_access_unchecked,GeneralT,numeric_types)
    {
        PNINEXUS_SETUP_SCALAR_FIXTURE();

        scalar<GeneralT> s = fixture.v;
        BOOST_CHECK_EQUAL(s[0],fixture.v);
        BOOST_CHECK_EQUAL(s[1],fixture.v);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_access_checked,GeneralT,numeric_types)
    {
        PNINEXUS_SETUP_SCALAR_FIXTURE();

        scalar<GeneralT> s = fixture.v;
        BOOST_CHECK_EQUAL(s.at(0),fixture.v);
        BOOST_CHECK_EQUAL(s.at(1),fixture.v);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_comparison,GeneralT,numeric_types)
    {
        PNINEXUS_SETUP_SCALAR_FIXTURE();

        scalar<GeneralT> a = fixture.generator();
        scalar<GeneralT> b = a;
        scalar<GeneralT> c(fixture.generator());

        BOOST_CHECK(a==b);
        BOOST_CHECK(a==a);
        // BOOST_CHECK(a!=c); // it fails randomly
    }

BOOST_AUTO_TEST_SUITE_END()





