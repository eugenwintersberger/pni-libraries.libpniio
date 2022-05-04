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
//  Created on: May 14, 2012
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
#include <pni/arrays.hpp>
#include "../data_generator.hpp"
#include "array_types.hpp"
#include <boost/mpl/joint_view.hpp>
#include <iostream>
#include "../compiler_version.hpp"

using namespace pni;

#define NX 100
#define NY 125

typedef  boost::mpl::joint_view<all_dynamic_arrays,
#if GCC_VERSION > 40800
                                boost::mpl::joint_view<
                                all_fixed_dim_arrays<2>,
                                all_static_arrays<NX,NY>
                                >
#else 
                                all_fixed_dim_arrays<2>
#endif
                                > all_array_types;

template<typename TestArrayT> struct array_view_test_fixture
{
    typedef TestArrayT                            array_type;
    typedef array_view<TestArrayT>                view_type;
    typedef typename TestArrayT::value_type       value_type;
    typedef random_generator<value_type>  generator_type;
    typedef std::vector<slice>            slice_vector;
    typedef typename array_type::map_type map_type;
    typedef array_selection               selection_type;

    generator_type generator;
    shape_t shape;
    array_type a;

    array_view_test_fixture():
        generator(),
        shape({NX,NY}),
        a(array_type::create(shape))
    {
        std::generate(a.begin(),a.end(),generator); 
    }
};

#define SETUP_VIEW_FIXTURE()\
        typedef array_view_test_fixture<TestArrayT> fixture_type;  \
        fixture_type fixture 

BOOST_AUTO_TEST_SUITE(array_view_test)

    template<typename ViewT>
    void check_view(const ViewT &view,const shape_t &ref)
    {
        size_t ref_size = std::accumulate(ref.begin(),ref.end(),1,
                std::multiplies<size_t>());
        size_t ref_rank = ref.size();

        BOOST_CHECK_EQUAL(view.rank(),ref_rank);
        BOOST_CHECK_EQUAL(view.size(),ref_size);

        auto shape = view.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      ref.begin(),ref.end());

    }
        
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;

        slice_vector slices{slice(0,3),slice(3,7)};
        view_type v1(fixture.a,array_selection::create(slices));
        check_view(v1,shape_t{3,4});
    
        slices = slice_vector{slice(1),slice(3,7)};
        view_type v2(fixture.a,array_selection::create(slices));
        check_view(v2,shape_t{4});
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction_from_array,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;

        slice_vector selection{slice(0,3),slice(3,7)};
        shape_t view_shape{3,4};

        view_type v = fixture.a(selection);
        check_view(v,view_shape);
        
        //check construction from a const array
        const TestArrayT &carray = fixture.a;
        auto v2 = carray(selection);
        check_view(v2,view_shape);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction_from_array_variadic,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();

        auto view = fixture.a(slice(0,3),slice(3,7));
        shape_t view_shape{3,4};
        check_view(view,view_shape);

        const TestArrayT &carray = fixture.a;
        auto view2 = carray(slice(0,3),slice(3,7));
        check_view(view2,view_shape);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;

        //create a selection
        auto s = array_selection::create(slice_vector{slice(0,1),slice(2,7)});
        view_type view(fixture.a,s);
        check_view(view,shape_t{5});

        for(size_t index=0;index<view.size();++index) 
            BOOST_CHECK_EQUAL(view[index],fixture.a(0,2+index));

        //-----------------check for front-----------------------------------------
        typename TestArrayT::value_type v = fixture.a(0,2);
        BOOST_CHECK_EQUAL(view.front(),v);

        //-----------------check for back------------------------------------------
        view.back() = v;
        BOOST_CHECK_EQUAL(view.back(),v);

        //finally we have to check for const references
        const view_type &cview = view;
        for(size_t index=0;index<cview.size();++index) 
            BOOST_CHECK_EQUAL(cview[index],fixture.a(0,2+index));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_pointer,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();

        //create a selection
        auto view1 = fixture.a(slice(0,50,2),slice(1,100,3));

        //should not work
        BOOST_CHECK_THROW(view1.data(),shape_mismatch_error);

        auto view2 = fixture.a(slice(0,5),slice(0,NY));
        auto ptr  = view2.data();
        auto iter = view2.begin();
        
        for(size_t i=0;i<5*NY;++i) BOOST_CHECK_EQUAL(*ptr++,*iter++);

        const decltype(view2) &cview2 = view2;
        auto cptr  = cview2.data();
        auto citer = cview2.begin();

        for(size_t i=0;i<5*NY;++i) BOOST_CHECK_EQUAL(*cptr++,*citer++);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_iterator_access,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::value_type value_type;        
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;

        //create the view
        auto s = array_selection::create(slice_vector{slice(10,35,2),slice(100,125,3)});
        view_type v(fixture.a,s);
        check_view(v,shape_t{13,9});

        //create data for the selection
        std::vector<typename TestArrayT::value_type> data(v.size());
        std::generate(data.begin(),data.end(),fixture.generator);

        //---------------------check write access----------------------------------
        auto diter = data.begin();
        std::copy(data.begin(),data.end(),v.begin());

        //----------------------check read access----------------------------------
        diter = data.begin();
        for(auto iter = v.begin();iter!=v.end();++iter,++diter)
            BOOST_CHECK_EQUAL(*iter,*diter);

        //-----now we need to check if the data arrived at the original array------
        array_selection  selection(shape_t{13,9},shape_t{10,100},shape_t{2,3});
        index_iterator<shape_t,dynamic_cindex_map> index_iter(shape_t{13,9},0);
        value_type v1,v2;
        size_t i = 0;
        for(auto iter = data.begin();iter!=data.end();++iter)
        {
            auto oindex = *index_iter++;
            auto index  = selection.template index<shape_t>(oindex);
            v1 = *iter;
            v2 = fixture.a(index);
            //compare(v1,v2);
            BOOST_CHECK_EQUAL(v1,v2);
            i++;
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::value_type value_type;
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;

        //select roi
        auto s = array_selection::create(slice_vector{slice(1,10),slice(0,100)});
        view_type roi(fixture.a,s);
   
        //allocate new array for a roi - we have to use a DArray here as for a
        //static array we would have to know the shape of the array

        dynamic_array<value_type> roia(roi);
        auto roi_s = roi.template shape<shape_t>();
        auto roia_s = roia.template shape<shape_t>();
        BOOST_CHECK_EQUAL(roi.rank(),roia.rank());
        BOOST_CHECK_EQUAL(roia_s.size(),roi_s.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(roia_s.begin(),roia_s.end(),
                                      roi_s.begin(),roi_s.end());

        //write new data to the array
        std::generate(roia.begin(),roia.end(),fixture.generator);
        std::copy(roia.begin(),roia.end(),roi.begin());
        auto roi_iter = roi.begin();
        auto roia_iter = roia.begin();
        while( roia_iter != roia.end())
            BOOST_CHECK_EQUAL(*roi_iter++,*roia_iter++);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multiindex_access,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        typedef typename TestArrayT::value_type value_type;
        typedef typename TestArrayT::view_type view_type;
        typedef std::vector<slice> slice_vector;
     
        slice_vector slices{slice(10,40),slice(0,100)};
        view_type view(fixture.a,array_selection::create(slices));
        check_view(view,shape_t{30,100});
        auto s = view.template shape<shape_t>();

        std::vector<value_type> data(view.size());
        std::generate(data.begin(),data.end(),fixture.generator);

        //-----------------writing data----------------------------
        auto diter = data.begin();
        for(size_t i=0;i<s[0];++i)
            for(size_t j=0;j<s[1];++j)
            {
                value_type v = *diter++;
                view(i,j) = v;
            }

        //----------------reading data-----------------------------
        diter = data.begin();
        for(size_t i=0;i<s[0];++i)
            for(size_t j=0;j<s[1];++j)
                BOOST_CHECK_EQUAL(view(i,j),*diter++);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_comparison,TestArrayT,all_array_types)
    {
        SETUP_VIEW_FIXTURE();
        auto a1 = fixture.a(0,slice(0,NY));
        auto a2 = fixture.a(1,slice(0,NY));

        BOOST_CHECK(a1==a1);
        BOOST_CHECK(a2==a2);
        BOOST_CHECK(a1!=a2);
    }

BOOST_AUTO_TEST_SUITE_END()

