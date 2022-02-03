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
//  Created on: Nov 13, 2013
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
#include <boost/test/parameterized_test.hpp>
#include <vector>
#include <list>
#include <array>
#include <pni/types.hpp>
#include <pni/arrays/index_map/c_index_map_imp.hpp>
#include <pni/arrays/array_selection.hpp>

using namespace pni;
using namespace boost::unit_test;

namespace cindex_implementation_test
{

    typedef c_index_map_imp map_type; 
    typedef array_selection sel_type;
    typedef std::vector<slice> slice_vector;
    typedef std::vector<size_t> index_type;

    typedef struct{
        index_type shape;
        index_type index;
        size_t expected_offset; 
    } offset_test_arg;

    typedef std::vector<offset_test_arg> offset_test_args;

    typedef struct{
        slice_vector sel;
        index_type shape;
        index_type sel_index;
        size_t expected_offset;
    } sel_offset_test_arg;

    typedef std::vector<sel_offset_test_arg> sel_offset_test_args;

    //------------------------------------------------------------------------
    void test_index(const offset_test_arg &arg)
    {
        shape_t index(arg.shape.size());
        map_type::index(arg.shape,index,arg.expected_offset);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      arg.index.begin(),arg.index.end());
    }

    //------------------------------------------------------------------------
    void test_offset(const offset_test_arg &arg)
    {
        BOOST_CHECK_EQUAL(map_type::offset(arg.shape,arg.index),
                          arg.expected_offset);
    }

    //------------------------------------------------------------------------
    void test_selection_offset(const sel_offset_test_arg &arg)
    {
        array_selection s = array_selection::create(arg.sel);
        BOOST_CHECK_EQUAL(map_type::offset(s,arg.shape,arg.sel_index),
                          arg.expected_offset);
    }

}


//============================================================================
int cindex_implementation_test_init()
{
    namespace test_ns = cindex_implementation_test;  

    test_suite *ts = BOOST_TEST_SUITE("cindex_implementation_test");
    test_ns::offset_test_args offset_args = {{{100},{5},5},
                                             {{100,23},{5,10},10+5*23}};

    ts->add(BOOST_PARAM_TEST_CASE(&test_ns::test_index,
                                  offset_args.begin(),
                                  offset_args.end()));

    ts->add(BOOST_PARAM_TEST_CASE(&test_ns::test_offset,
                                  offset_args.begin(),
                                  offset_args.end()));

    test_ns::sel_offset_test_args soffset_args = {
    {{slice(5,7)},{10},{1},6},
    {{slice(3,8),slice(7,10)},{10,20},{2,1},5*20+8}
    };

    ts->add(BOOST_PARAM_TEST_CASE(&test_ns::test_selection_offset,
                                  soffset_args.begin(),
                                  soffset_args.end()));

    framework::master_test_suite().add(ts);

    return 0;
}

