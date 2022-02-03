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
//  Created on: Nov 07, 2013
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
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>
#include <list>
#include <boost/current_function.hpp>
#include <pni/types.hpp>
#include "test_trait.hpp"

using namespace pni;

typedef boost::mpl::list<std::vector<uint8>,
                         std::vector<int8>,
                         std::vector<uint16>,
                         std::vector<int16>,
                         std::vector<uint32>,
                         std::vector<int32>,
                         std::vector<uint64>,
                         std::vector<int64>,
                         std::vector<float32>,
                         std::vector<float64>,
                         std::vector<float128>,
                         std::vector<complex32>,
                         std::vector<complex64>,
                         std::vector<complex128>
                         > vector_test_types;

typedef boost::mpl::list< std::list<uint8>,
                         std::list<int8>,
                         std::list<uint16>,
                         std::list<int16>,
                         std::list<uint32>,
                         std::list<int32>,
                         std::list<uint64>,
                         std::list<int64>,
                         std::list<float32>,
                         std::list<float64>,
                         std::list<float128>,
                         std::list<complex32>,
                         std::list<complex64>,
                         std::list<complex128>
                        > list_test_types;

typedef boost::mpl::joint_view<vector_test_types,list_test_types> test_types;


BOOST_AUTO_TEST_SUITE(container_utils_std_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_size,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::generator_type generator_type;

        //without initializiation value
        auto c1 = utils_type::create(10);
        BOOST_CHECK_EQUAL(c1.size(),10u);

        //with initializiation value
        auto init_value = generator_type()();
        auto c2 = utils_type::create(100,init_value);
        for(auto c: c2) BOOST_CHECK_EQUAL(c,init_value);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_range,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;
        typedef typename trait_type::generator_type generator_type; 
    
        generator_type generator;
        vector_type v(100);
        std::generate(v.begin(),v.end(),generator);
        auto c = utils_type::create(v.begin(),v.end());
        BOOST_CHECK_EQUAL(c.size(),v.size());
        
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_container,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;
        typedef typename trait_type::generator_type generator_type;

        generator_type generator;
        vector_type v(100);
        std::generate(v.begin(),v.end(),generator);

        auto c = utils_type::create(v);
        BOOST_CHECK_EQUAL(c.size(),v.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_init_list,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;

        auto v = vector_type{1,2,3,4};
        auto c = utils_type::create({1,2,3,4});
        BOOST_CHECK_EQUAL(c.size(),v.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }

BOOST_AUTO_TEST_SUITE_END()

