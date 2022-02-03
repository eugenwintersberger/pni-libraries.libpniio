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
//  Created on: Oct 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/included/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/arrays.hpp>
#include "array_types.hpp"
#include "../data_generator.hpp"

using namespace pni;

template<typename AT> struct dynamic_array_test_fixture
{
    typedef AT array_type;
    typedef typename AT::map_type map_type; 
    typedef typename AT::storage_type storage_type;
    typedef typename array_type::value_type value_type;
    typedef random_generator<value_type> generator_type;
    
    generator_type generator;
    shape_t shape;

    dynamic_array_test_fixture():
        generator(),
        shape(shape_t{2,3,5})
    {}
};

BOOST_AUTO_TEST_SUITE(dynamic_mdarray_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_default_construction,AT,all_dynamic_arrays)
    {
        AT a;
        BOOST_CHECK_EQUAL(a.size(),0u);
        BOOST_CHECK_EQUAL(a.rank(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_standard_construction,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type; 
        fixture_type fixture;
        
        auto map = map_utils<typename fixture_type::map_type>::create(fixture.shape);
        BOOST_CHECK_EQUAL(map.max_elements(),30u);
        typename fixture_type::storage_type storage(map.max_elements()); 
        BOOST_CHECK_EQUAL(storage.size(),30u);
        AT a(map,storage);

        BOOST_CHECK_EQUAL(a.size(),storage.size());
        BOOST_CHECK_EQUAL(a.rank(),3u);

        AT a2(std::move(map),std::move(storage));
        BOOST_CHECK_EQUAL(a2.size(),a.size());
        BOOST_CHECK_EQUAL(a2.rank(),a.rank());
        BOOST_CHECK_EQUAL(map.rank(),0u);
        BOOST_CHECK_EQUAL(storage.size(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type; 
        fixture_type fixture;

        auto map = map_utils<typename fixture_type::map_type>::create(fixture.shape);
        typename fixture_type::storage_type storage(map.max_elements()); 
        AT a(map,storage);

        AT b(a);
        BOOST_CHECK_EQUAL(a.size(),b.size());
        BOOST_CHECK_EQUAL(a.rank(),b.rank());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_construction,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type; 
        fixture_type fixture;

        auto map = map_utils<typename fixture_type::map_type>::create(fixture.shape);
        typename fixture_type::storage_type storage(map.max_elements()); 
        AT a(map,storage);

        AT b(std::move(a));
        BOOST_CHECK_EQUAL(a.size(),0u);
        BOOST_CHECK_EQUAL(a.rank(),0u);
        BOOST_CHECK_EQUAL(b.size(),storage.size());
        BOOST_CHECK_EQUAL(b.rank(),3u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_fixed_dim_construction,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type;
        typedef typename fixture_type::value_type value_type;
        typedef fixed_dim_array<value_type,3> farray_type;

        fixture_type fixture; 

        auto farray = farray_type::create(fixture.shape);
        std::generate(farray.begin(),farray.begin(),fixture.generator);
        AT a(farray);
        auto s = a.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),fixture.shape.begin(),
                                      fixture.shape.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),
                                      farray.begin(),farray.end());

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_static_construction,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef static_array<value_type,2,3,5> sarray_type; 

        fixture_type fixture;

        auto sarray = sarray_type::create(fixture.shape);
        std::generate(sarray.begin(),sarray.end(),fixture.generator);
        AT a(sarray);
        auto s = a.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),fixture.shape.begin(),
                                      fixture.shape.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),
                                      sarray.begin(),sarray.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type;
        typedef typename fixture_type::map_type map_type;
        typedef typename fixture_type::storage_type storage_type; 

        fixture_type fixture;

        auto map = map_utils<map_type>::create(fixture.shape);
        storage_type storage(map.max_elements());
        AT a(std::move(map),std::move(storage));
        std::generate(a.begin(),a.end(),fixture.generator);

        AT b = a;
        BOOST_CHECK_EQUAL(b.size(),a.size());
        BOOST_CHECK_EQUAL(b.rank(),a.rank());
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),b.begin(),b.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type;
        typedef typename fixture_type::map_type map_type;
        typedef typename fixture_type::storage_type storage_type; 

        fixture_type fixture;

        auto map = map_utils<map_type>::create(fixture.shape);
        storage_type storage(map.max_elements());
        std::generate(storage.begin(),storage.end(),fixture.generator);
        AT a(map,storage);

        AT b = std::move(a);
        BOOST_CHECK_EQUAL(b.size(),storage.size());
        BOOST_CHECK_EQUAL(b.rank(),map.rank());
        BOOST_CHECK_EQUAL_COLLECTIONS(b.begin(),b.end(),
                                      storage.begin(),storage.end());
        
        BOOST_CHECK_EQUAL(a.size(),0u);
        BOOST_CHECK_EQUAL(a.rank(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_assign_from_fixed_dim,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type;
        typedef typename fixture_type::value_type value_type;
        typedef fixed_dim_array<value_type,3> farray_type;

        fixture_type fixture; 

        auto farray = farray_type::create(fixture.shape);
        std::generate(farray.begin(),farray.begin(),fixture.generator);
        auto a = AT::create(fixture.shape);
        a = farray;
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),
                                      farray.begin(),farray.end());
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_assign_from_static,AT,all_dynamic_arrays)
    {
        typedef dynamic_array_test_fixture<AT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef static_array<value_type,2,3,5> sarray_type; 

        fixture_type fixture;

        auto sarray = sarray_type::create(fixture.shape);
        std::generate(sarray.begin(),sarray.end(),fixture.generator);
        auto a = AT::create(fixture.shape);
        a = sarray;
        BOOST_CHECK_EQUAL_COLLECTIONS(a.begin(),a.end(),
                                      sarray.begin(),sarray.end());

    }
BOOST_AUTO_TEST_SUITE_END()


