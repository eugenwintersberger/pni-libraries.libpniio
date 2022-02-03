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

using namespace pni;

template<typename AT> struct fix_mdarray_test_fixture
{
    typedef AT array_type;
    typedef typename array_type::map_type map_type;
    typedef typename array_type::storage_type storage_type;
    typedef typename array_type::value_type value_type;
        
    typedef random_generator<value_type> generator_type;
    generator_type generator;

    shape_t shape;

    fix_mdarray_test_fixture():
        generator(),
        shape(shape_t{2,3,5})
    {}
};


BOOST_AUTO_TEST_SUITE(fix_mdarray_test)
    
    typedef all_fixed_dim_arrays<3> array_types;

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_default_construction,AT,array_types)
    {
        AT a;
        BOOST_CHECK_EQUAL(a.size(),0u);
        BOOST_CHECK_EQUAL(a.rank(),3u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_standard_construction,AT,array_types)
    {
        typedef fix_mdarray_test_fixture<AT> fixture_type;
        typedef typename fixture_type::map_type map_type;
        typedef typename fixture_type::storage_type storage_type; 

        fixture_type fixture; 

        auto map = map_utils<map_type>::create(fixture.shape);
        storage_type storage(map.max_elements());
        std::generate(storage.begin(),storage.end(),fixture.generator);
        AT a(map,storage);

        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),
                                      storage.begin(),storage.end());
        BOOST_CHECK_EQUAL(a.size(),storage.size());
        BOOST_CHECK_EQUAL(a.rank(),map.rank());

        AT b(std::move(map),std::move(storage));
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
        BOOST_CHECK_EQUAL(b.size(),a.size());
        BOOST_CHECK_EQUAL(b.rank(),a.rank());

        BOOST_CHECK_EQUAL(storage.size(),0u);
        BOOST_CHECK_EQUAL(map.max_elements(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_constructor,AT,array_types)
    {
        typedef fix_mdarray_test_fixture<AT> fixture_type; 
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b = a;
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
        BOOST_CHECK_EQUAL(a.size(),b.size());
        BOOST_CHECK_EQUAL(a.rank(),b.rank());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_constructor,AT,array_types)
    {
        typedef fix_mdarray_test_fixture<AT> fixture_type; 
        typedef typename fixture_type::map_type map_type;
        typedef typename fixture_type::storage_type storage_type;
        fixture_type fixture;
    
        auto map = map_utils<map_type>::create(fixture.shape);
        storage_type storage(map.max_elements());
        std::generate(storage.begin(),storage.end(),fixture.generator);

        AT a(map,storage);
        AT b = std::move(a);

        BOOST_CHECK_EQUAL_COLLECTIONS(b.begin(),b.end(),
                                      storage.begin(),storage.end());
        BOOST_CHECK_EQUAL(b.size(),storage.size());
        BOOST_CHECK_EQUAL(b.rank(),map.rank());

        BOOST_CHECK_EQUAL(a.size(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,AT,array_types)
    {
        typedef fix_mdarray_test_fixture<AT> fixture_type; 
        fixture_type fixture;

        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        auto b = AT::create(fixture.shape);

        b = a;
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
        BOOST_CHECK_EQUAL(a.size(),b.size());
        BOOST_CHECK_EQUAL(a.rank(),b.rank());

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment,AT,array_types)
    {
        typedef fix_mdarray_test_fixture<AT> fixture_type; 
        fixture_type fixture;
        
        auto a = AT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        AT b(a);
        auto c = AT::create(fixture.shape);

        c = std::move(b);

        BOOST_CHECK_EQUAL_COLLECTIONS(c.begin(),c.end(),
                                      a.begin(),a.end());
        BOOST_CHECK_EQUAL(c.size(),a.size());
        BOOST_CHECK_EQUAL(c.rank(),a.rank());

        BOOST_CHECK_EQUAL(b.size(),0u);
    }

BOOST_AUTO_TEST_SUITE_END()
