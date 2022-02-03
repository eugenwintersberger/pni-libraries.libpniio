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
//  Created on: Jul 13, 2012
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
#include <pni/algorithms.hpp>
#include <pni/arrays/array_selection.hpp>
#include <pni/arrays/index_map/index_maps.hpp>

#include <list>
#include <iostream>

using namespace pni;

namespace array_selection_test_types
{
    typedef std::vector<size_t> index_type;
    typedef std::vector<slice>  slice_type;
    typedef dynamic_cindex_map  map_type;
}

namespace std
{
    ostream &operator<<(ostream &stream,
                        const array_selection_test_types::index_type &index)
    {
        stream<<"( ";
        for(auto i: index)
            stream<<i<<" ";

        stream<<")";

        return stream;
    }

    ostream &operator<<(ostream &stream,
                        const array_selection_test_types::slice_type &slices)
    {
        stream<<"( ";
        for(auto s: slices)
            stream<<s<<" ";

        stream<<")";

        return stream;
    }
}

struct array_selection_fixture
{

    array_selection_test_types::map_type m1;
    array_selection_test_types::map_type m2;
    array_selection_test_types::slice_type slices_1;
    array_selection_test_types::slice_type slices_2;
    array_selection sel_1;
    array_selection sel_2;

    array_selection_fixture():
        m1(array_selection_test_types::index_type{10,20}),
        m2(array_selection_test_types::index_type{10,20,5}),
        slices_1({slice(2,10),slice(2)}),
        slices_2({slice(2,10),slice(2),slice(1,5,2)}),
        sel_1(array_selection::create(slices_1)),
        sel_2(array_selection::create(slices_2))
    {}
};


BOOST_FIXTURE_TEST_SUITE(array_selection_test,array_selection_fixture)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_default_construction)
    {
        array_selection sel1;
        auto sel1_shape = sel1.shape<shape_t>();
        BOOST_CHECK_EQUAL(sel1.rank(),0u);
        BOOST_CHECK_EQUAL(sel1.shape<shape_t>(),shape_t());
        BOOST_CHECK_EQUAL(sel1.size(),0u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_standard_construction)
    {
        using namespace array_selection_test_types;

        //testing standard constructor
        index_type s({1,100,100}); 
        index_type o({0,0,0}); 
        index_type str({1,1,1});
        array_selection sel(s,o,str);
        BOOST_CHECK_EQUAL(sel.rank(),2u);
        BOOST_CHECK_EQUAL(sel.size(),100u*100u);

        auto sel_shape = sel.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin()+1,s.end(),
                                      sel_shape.begin(),sel_shape.end());

        //check full parameters
        BOOST_CHECK_EQUAL_COLLECTIONS(sel.full_shape().begin(),
                                      sel.full_shape().end(),
                                      s.begin(),s.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(sel.offset().begin(),
                                      sel.offset().end(),
                                      o.begin(),o.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(sel.stride().begin(),
                                      sel.stride().end(),
                                      str.begin(),str.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_copy_construction)
    {
        using namespace array_selection_test_types;

        //! copy constructor
        array_selection s(sel_1);
        BOOST_CHECK_EQUAL(s.rank(),sel_1.rank());
        BOOST_CHECK_EQUAL(s.size(),sel_1.size());
        auto s_shape = s.shape<index_type>();
        auto r_shape = sel_1.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s_shape.begin(),s_shape.end(),
                                      r_shape.begin(),r_shape.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_move_construction)
    {
        using namespace array_selection_test_types;

        //! move construction
        array_selection s_orig(sel_2);
        array_selection s(std::move(s_orig));
        BOOST_CHECK_EQUAL(s.rank(),sel_2.rank());
        BOOST_CHECK_EQUAL(s.size(),sel_2.size());
        auto s_shape = s.shape<index_type>();
        auto r_shape = sel_2.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s_shape.begin(),s_shape.end(),
                                      r_shape.begin(),r_shape.end());

        BOOST_CHECK_EQUAL(s_orig.size(),0u);
        BOOST_CHECK_EQUAL(s_orig.rank(),0u);
        BOOST_CHECK_EQUAL(s_orig.shape<index_type>(),index_type());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_fixture_objects)
    {
        using namespace array_selection_test_types;

        //testing the default internal objects
        BOOST_CHECK_EQUAL(sel_1.rank(),1u);
        auto sel_1_shape = sel_1.shape<index_type>();
        index_type sel_1_shape_ref = {8};
        BOOST_CHECK_EQUAL_COLLECTIONS(sel_1_shape.begin(),sel_1_shape.end(),
                                      sel_1_shape_ref.begin(),
                                      sel_1_shape_ref.end());

        BOOST_CHECK_EQUAL(sel_2.rank(),2u);
        auto sel_2_shape = sel_2.shape<index_type>();
        index_type sel_2_shape_ref = {8,2};
        BOOST_CHECK_EQUAL_COLLECTIONS(sel_2_shape.begin(),sel_2_shape.end(),
                                      sel_2_shape_ref.begin(),
                                      sel_2_shape_ref.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_create)
    {
        using namespace array_selection_test_types;

        slice_type slices{slice(0,10),slice(1,30,2),slice(2)};
        array_selection s = array_selection::create(slices);

        BOOST_CHECK_EQUAL(s.size(),10u*15u);
        BOOST_CHECK_EQUAL(s.rank(),2u);
        index_type ref_shape{10,15};
        auto ss = s.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(ss.begin(),ss.end(),
                                      ref_shape.begin(),ref_shape.end());

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_copy_assignment)
    {
        using namespace array_selection_test_types;

        array_selection s1;

        s1 = sel_2;
        BOOST_CHECK_EQUAL(s1.rank(),sel_2.rank());
        BOOST_CHECK_EQUAL(s1.size(),sel_2.size());
        auto s1_shape = s1.shape<index_type>();
        auto r_shape  = sel_2.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s1_shape.begin(),s1_shape.end(),
                                      r_shape.begin(),r_shape.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_move_assignment)
    {
        using namespace array_selection_test_types;

        array_selection s_orig(sel_2);
        array_selection s;
        s = std::move(s_orig);
        BOOST_CHECK_EQUAL(s.rank(),sel_2.rank());
        BOOST_CHECK_EQUAL(s.size(),sel_2.size());
        auto s_shape  = s.shape<index_type>();
        auto r_shape  = sel_2.shape<index_type>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s_shape.begin(),s_shape.end(),
                                      r_shape.begin(),r_shape.end());

        BOOST_CHECK_EQUAL(s_orig.size(),0u);
        BOOST_CHECK_EQUAL(s_orig.rank(),0u);
        BOOST_CHECK_EQUAL(s_orig.shape<index_type>(),index_type());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_index)
    {
        using namespace array_selection_test_types;

        array_selection selection(index_type({10,20}),index_type({1,2}),
                            index_type({3,2}));
            
        index_type calculated_index(selection.rank());
        selection.index(index_type({1,3}),calculated_index);
        index_type expected_index{4,8};
        BOOST_CHECK_EQUAL_COLLECTIONS(calculated_index.begin(),
                                      calculated_index.end(),
                                      expected_index.begin(),
                                      expected_index.end());

        selection =  array_selection(index_type({10,1,20}),
                                     index_type({1,1,2}),
                                     index_type({3,1,2}));
        calculated_index = index_type(3);
        selection.index(index_type({1,3}),calculated_index);
        expected_index = index_type{4,1,8};
        BOOST_CHECK_EQUAL_COLLECTIONS(calculated_index.begin(),
                                      calculated_index.end(),
                                      expected_index.begin(),
                                      expected_index.end());
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_offset)
    {
        using namespace array_selection_test_types;

        index_type index={2};

        BOOST_CHECK_EQUAL(offset(m1,sel_1,index),
                          m1.offset(index_type{4,2}));

        index_type index_2 = {2,1};
        BOOST_CHECK_EQUAL(offset(m2,sel_2,index_2),
                          m2.offset(index_type{4,2,1+2}));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_start_offset)
    {
        BOOST_CHECK_EQUAL(start_offset(m1,sel_1),42u);
        BOOST_CHECK_EQUAL(start_offset(m2,sel_2),211u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_end_offset)
    {
        BOOST_CHECK_EQUAL(last_offset(m1,sel_1),182u);
        BOOST_CHECK_EQUAL(last_offset(m2,sel_2),913u);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_is_contiguous)
    {
        using namespace array_selection_test_types;

        BOOST_CHECK(!is_contiguous(m1,sel_1));
        BOOST_CHECK(!is_contiguous(m2,sel_2));

        slice_type cslices{slice(1),slice(10,19)};
        array_selection cs = array_selection::create(cslices);
        BOOST_CHECK(is_contiguous(m1,cs));

    }

BOOST_AUTO_TEST_SUITE_END()


