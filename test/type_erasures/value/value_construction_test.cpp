//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include "../../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/test/tools/floating_point_comparison.hpp>
#include <pni/type_erasures.hpp>

#include "../../data_generator.hpp"
#include "types.hpp"
#include "fixture.hpp"

using namespace pni;


BOOST_AUTO_TEST_SUITE(value_construction_test)

    BOOST_AUTO_TEST_CASE(test_default_construction)
    {
        value v;
        BOOST_CHECK_EQUAL(v.type_id(),type_id_t::None);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_make_construction,T,all_types)
    {
        value v = make_value<T>();
        BOOST_CHECK(v.type_id()==type_id_map<T>::type_id);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_value,T,all_types)
    {
        fixture<T> f;

        value v(f.value_1);
        BOOST_CHECK(v.type_id() == type_id_map<T>::type_id);
        BOOST_CHECK_EQUAL(v.as<T>(),f.value_1); 
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,T,all_types)
    {
        fixture<T> f;    
        value v1(f.value_1);
        value v2(v1);

        BOOST_CHECK_EQUAL(v1.type_id(),v2.type_id());
        BOOST_CHECK_EQUAL(v1.as<T>(),v2.as<T>());
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_1);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_construction,T,all_types)
    {
        fixture<T> f;
        value v1(f.value_1);
        value v2 = std::move(v1);

        BOOST_CHECK_EQUAL(v1.type_id(),type_id_t::None);
        BOOST_CHECK(v2.type_id()==type_id_map<T>::type_id);
        BOOST_CHECK_EQUAL(f.value_1,v2.as<T>());
    }

BOOST_AUTO_TEST_SUITE_END()


