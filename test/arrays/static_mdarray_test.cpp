//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 29, 2013
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
#include <pni/arrays.hpp>

#include "array_types.hpp"
#include "../data_generator.hpp"
#include "../compiler_version.hpp"

using namespace pni;

#if GCC_VERSION > 40800


template<typename AT> struct static_mdarray_test_fixture
{
    typedef AT array_type;
    typedef typename array_type::value_type value_type;
    typedef typename array_type::map_type map_type;

    typedef random_generator<value_type> generator_type;

    generator_type generator;
    shape_t shape;

    static_mdarray_test_fixture():
        generator(),
        shape(shape_t{2,3,5})
    {}
};


BOOST_AUTO_TEST_SUITE(static_mdarray_test)
    
    typedef all_static_arrays<2,3,5> array_types;

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_default_constructor,AT,array_types)
    {
        AT a;
        BOOST_CHECK_EQUAL(a.size(),30u);
        BOOST_CHECK_EQUAL(a.rank(),3u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_constructor,AT,array_types)
    {
        typedef static_mdarray_test_fixture<AT> fixture_type;
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b = a;
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
        BOOST_CHECK_EQUAL(b.size(),a.size());
        BOOST_CHECK_EQUAL(b.rank(),a.rank());
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_constructor,AT,array_types)
    {
        typedef static_mdarray_test_fixture<AT> fixture_type;
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b(a);
        AT c(std::move(b));
        
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),c.begin(),c.end());
        BOOST_CHECK_EQUAL(c.size(),a.size());
        BOOST_CHECK_EQUAL(c.rank(),a.rank());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,AT,array_types)
    {
        typedef static_mdarray_test_fixture<AT> fixture_type;
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b;
        
        b = a;
        BOOST_CHECK_EQUAL(b.size(),a.size());
        BOOST_CHECK_EQUAL(b.rank(),a.rank());
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment,AT,array_types)
    {
        typedef static_mdarray_test_fixture<AT> fixture_type;
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b(a);
        AT c;
        
        c = std::move(b);
        BOOST_CHECK_EQUAL(c.size(),a.size());
        BOOST_CHECK_EQUAL(c.rank(),a.rank());
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),c.begin(),c.end());

    }

BOOST_AUTO_TEST_SUITE_END()
#endif

