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
//  Created on: Oct 19, 2013
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
#include <boost/test/parameterized_test.hpp>
#include <boost/mpl/list.hpp>
#include <vector>
#include <list>
#include <pni/arrays/index_map/index_maps.hpp>
#include <pni/arrays/array_selection.hpp>
#include "common.hpp"

using namespace pni;
using namespace boost::unit_test;

namespace dynamic_cindex_map_test{
   
    typedef dynamic_cindex_map map_type;
    typedef offset_arg<map_type,vector_index_type> offset_arg_type;
    typedef selection_offset_arg<map_type,vector_index_type> 
            selection_offset_arg_type; 
    typedef std::vector<offset_arg_type> offset_args_type;
    typedef std::vector<selection_offset_arg_type> selection_offset_args_type;

    //------------------------------------------------------------------------
    void test_offset(const offset_arg_type &arg)
    {
        BOOST_CHECK_EQUAL(arg.map.offset(arg.index),arg.expected_offset);
    }
    
    //------------------------------------------------------------------------
    void test_selection_offset(const selection_offset_arg_type &arg)
    {
        array_selection s = array_selection::create(arg.slices);
        BOOST_CHECK_EQUAL(arg.map.offset(s,arg.sel_index),arg.expected_offset);
    }

    //------------------------------------------------------------------------
    void test_index(const offset_arg_type &arg)
    {
        auto index = arg.map.index<vector_index_type>(arg.expected_offset);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      arg.index.begin(),arg.index.end()); 
    }

    //------------------------------------------------------------------------
    void test_inquery()
    {
        shape_t s{20};
        auto map = map_utils<map_type>::create(s);
        BOOST_CHECK_EQUAL(map.max_elements(),20u);
        BOOST_CHECK_EQUAL(map.rank(),s.size());
        BOOST_CHECK_EQUAL(map.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map.begin(),map.end(),s.begin(),
                                      s.end());

        s = shape_t{3,4,5};
        map = map_utils<map_type>::create(s);
        BOOST_CHECK_EQUAL(map.max_elements(),60u);
        BOOST_CHECK_EQUAL(map.rank(),s.size());
        BOOST_CHECK_EQUAL(map.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map.begin(),map.end(),s.begin(),
                                      s.end());
        
        s = shape_t{1024,1000};
        map = map_utils<map_type>::create(s);
        BOOST_CHECK_EQUAL(map.max_elements(),1024u*1000u);
        BOOST_CHECK_EQUAL(map.rank(),s.size());
        BOOST_CHECK_EQUAL(map.size(),s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(map.begin(),map.end(),s.begin(),
                                      s.end());

    }
}

//============================================================================
int dynamic_cindex_map_test_init()
{
    using namespace dynamic_cindex_map_test;
    typedef map_utils<dynamic_cindex_map> utils_type;
    
    test_suite *ts = BOOST_TEST_SUITE("dynamic_cindex_map_test");
    offset_args_type offset_args = {
    {utils_type::create({3,4,5}),{2,1,2},47},
    {utils_type::create({20}),{10},10},
    {utils_type::create({1024,100}),{1000,55},100055}
    };

    ts->add(BOOST_PARAM_TEST_CASE(&test_offset,
                                  offset_args.begin(),
                                  offset_args.end()));

    ts->add(BOOST_PARAM_TEST_CASE(&test_index,
                                  offset_args.begin(),
                                  offset_args.end()));

    ts->add(BOOST_TEST_CASE(test_inquery));

    selection_offset_args_type soffset_args = {
        {{slice(5,7)},utils_type::create({10}),{1},6},
        {{slice(3,8),slice(7,10)},utils_type::create({10,20}),
          {2,1},5*20+8}
    };

    ts->add(BOOST_PARAM_TEST_CASE(&test_selection_offset,
                                  soffset_args.begin(),
                                  soffset_args.end()));

    
    framework::master_test_suite().add(ts);
    return 0;                            
}

