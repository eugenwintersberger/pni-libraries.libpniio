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
//  Created on: Nov 2, 2015
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
#include <boost/test/parameterized_test.hpp>
#include <boost/mpl/list.hpp>
#include <vector>
#include <list>
#include <pni/arrays/index_map/index_maps.hpp>
#include <pni/arrays/array_selection.hpp>
#include "common.hpp"

using namespace pni;
using namespace boost::unit_test;

namespace fixed_dim_cindex_map_test{
   
    typedef fixed_dim_cindex_map<1> map_type_1d;
    typedef fixed_dim_cindex_map<2> map_type_2d;
    typedef fixed_dim_cindex_map<3> map_type_3d;

    //------------------------------------------------------------------------
    void test_offset()
    {
        auto map1 = map_utils<map_type_1d>::create({20});
        BOOST_CHECK_EQUAL(map1.offset(vector_index_type{10}),10u);

        auto map2 = map_utils<map_type_2d>::create({1024,100});
        BOOST_CHECK_EQUAL(map2.offset(vector_index_type{1000,55}),100055u);

        auto map3 = map_utils<map_type_3d>::create({3,4,5});
        BOOST_CHECK_EQUAL(map3.offset(vector_index_type{2,1,2}),47u);
    }
    
    //------------------------------------------------------------------------
    void test_selection_offset()
    {
        array_selection s = array_selection::create(slice_vector{slice(5,7)});
        auto map1 = map_utils<map_type_1d>::create({10});
        BOOST_CHECK_EQUAL(map1.offset(s,vector_index_type{1}),6u);
        
        s = array_selection::create(slice_vector{slice(3,8),slice(7,10)});
        auto map2 = map_utils<map_type_2d>::create({10,20});
        BOOST_CHECK_EQUAL(map2.offset(s,vector_index_type{2,1}),5u*20u+8u);
    }

    //------------------------------------------------------------------------
    void test_index()
    {
        vector_index_type rindex={10};
        auto map1 = map_utils<map_type_1d>::create({20});
        auto index = map1.index<vector_index_type>(10);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(), 
                                      rindex.begin(),rindex.end()); 

        rindex = vector_index_type{1000,55};
        auto map2 = map_utils<map_type_2d>::create({1024,100});
        index = map2.index<vector_index_type>(100055);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      rindex.begin(),rindex.end());

        rindex = vector_index_type{2,1,2};
        auto map3 = map_utils<map_type_3d>::create({3,4,5});
        index = map3.index<vector_index_type>(47);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      rindex.begin(),rindex.end());
    }

    //------------------------------------------------------------------------
    void test_inquery()
    {

        shape_t s{20};
        auto map1 = map_utils<map_type_1d>::create(s);
        BOOST_CHECK_EQUAL(map1.max_elements(),20u);
        BOOST_CHECK_EQUAL(map1.rank(),s.size());
        BOOST_CHECK_EQUAL(map1.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map1.begin(),map1.end(),
                                      s.begin(),s.end());

        s = shape_t{3,4,5};
        auto map2 = map_utils<map_type_3d>::create(s);
        BOOST_CHECK_EQUAL(map2.max_elements(),60u);
        BOOST_CHECK_EQUAL(map2.rank(),s.size());
        BOOST_CHECK_EQUAL(map2.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map2.begin(),map2.end(),
                                      s.begin(),s.end());
        
        s = shape_t{1024,1000};
        auto map3 = map_utils<map_type_2d>::create(s);
        BOOST_CHECK_EQUAL(map3.max_elements(),1024u*1000u);
        BOOST_CHECK_EQUAL(map3.rank(),s.size());
        BOOST_CHECK_EQUAL(map3.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map3.begin(),map3.end(),
                                      s.begin(),s.end());

    }
}

//============================================================================
int fixed_dim_cindex_map_test_init()
{
    using namespace fixed_dim_cindex_map_test;
    
    test_suite *ts = BOOST_TEST_SUITE("fixed_dim_cindex_map_test");

    ts->add(BOOST_TEST_CASE(&test_offset));
    ts->add(BOOST_TEST_CASE(&test_index));
    ts->add(BOOST_TEST_CASE(&test_inquery));
    ts->add(BOOST_TEST_CASE(&test_selection_offset));

    
    framework::master_test_suite().add(ts);
    return 0;                            
}

