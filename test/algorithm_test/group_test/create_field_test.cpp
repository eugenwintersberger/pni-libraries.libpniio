//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/create_field.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_rank.hpp>
#include <pni/io/nx/algorithms/get_size.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>

#include "../algorithm_test_fixture.hpp"
#include "../../nexus_lowlevel_test/test_types.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct create_field_test_fixture : algorithm_test_fixture
{
    const static shape_t shape;
    const static shape_t chunk;

    h5::nxdeflate_filter filter;
    create_field_test_fixture():
        algorithm_test_fixture("create_field_test.nx"),
        filter(h5::nxdeflate_filter(2,true))
    {}
};

const shape_t create_field_test_fixture::shape = {2,1024};
const shape_t create_field_test_fixture::chunk = {1,1024};

BOOST_FIXTURE_TEST_SUITE(create_field_test,create_field_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_on_field_object,T,field_test_types)
    {
        //test on compile time function templates
        BOOST_CHECK_THROW(create_field<T>(o_field,"g1"),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_field,"g1",shape),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_field,"g2",shape,filter),type_error);

        //test on runtime function
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK_THROW(create_field(o_field,tid,"g1"),type_error);
        BOOST_CHECK_THROW(create_field(o_field,tid,"g1",shape),type_error);
        BOOST_CHECK_THROW(create_field(o_field,tid,"g2",shape,filter),type_error);
        BOOST_CHECK_THROW(create_field(o_field,tid,"g2",shape,chunk),type_error);
        BOOST_CHECK_THROW(create_field(o_field,tid,"g2",shape,chunk,filter),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_on_attribute_object,T,field_test_types)
    {
        //test on compile time function templates
        BOOST_CHECK_THROW(create_field<T>(o_attribute,"g1"),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_attribute,"g1",shape),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_attribute,"g2",shape,filter),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_attribute,"g2",shape,chunk),type_error);
        BOOST_CHECK_THROW(create_field<T>(o_attribute,"g2",shape,chunk,filter),type_error);

        //test on runtime function
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK_THROW(create_field(o_attribute,tid,"g1"),type_error);
        BOOST_CHECK_THROW(create_field(o_attribute,tid,"g1",shape),type_error);
        BOOST_CHECK_THROW(create_field(o_attribute,tid,"g2",shape,filter),type_error);
        BOOST_CHECK_THROW(create_field(o_attribute,tid,"g2",shape,chunk),type_error);
        BOOST_CHECK_THROW(create_field(o_attribute,tid,"g2",shape,chunk,filter),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_simple,T,field_test_types)
    {
        auto f= create_field<T>(o_group,"f1");
        type_id_t tid = type_id_map<T>::type_id;

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),1);
        BOOST_CHECK_EQUAL(get_size(f),1);
        BOOST_CHECK_EQUAL(get_name(f),"f1");
        BOOST_CHECK_EQUAL(get_type(f),tid);

        f= create_field(o_group,tid,"f2");
        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),1);
        BOOST_CHECK_EQUAL(get_size(f),1);
        BOOST_CHECK_EQUAL(get_name(f),"f2");
        BOOST_CHECK_EQUAL(get_type(f),tid);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_shape,T,field_test_types)
    {
        auto f= create_field<T>(o_group,"f1",shape);
        type_id_t tid = type_id_map<T>::type_id; 

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f1");
        BOOST_CHECK_EQUAL(get_type(f),tid);

        f= create_field(o_group,tid,"f2",shape);

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f2");
        BOOST_CHECK_EQUAL(get_type(f),tid);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_shape_filter,T,field_test_types)
    {
        auto f= create_field<T>(o_group,"f1",shape,filter);
        type_id_t tid = type_id_map<T>::type_id; 

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f1");
        BOOST_CHECK_EQUAL(get_type(f),tid);

        f= create_field(o_group,tid,"f2",shape,filter);
        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f2");
        BOOST_CHECK_EQUAL(get_type(f),tid);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_shape_chunk,T,field_test_types)
    {
        auto f = create_field<T>(o_group,"f1",shape,chunk);
        type_id_t tid = type_id_map<T>::type_id; 

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f1");
        BOOST_CHECK_EQUAL(get_type(f),tid);

        f= create_field(o_group,tid,"f2",shape,chunk);
        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f2");
        BOOST_CHECK_EQUAL(get_type(f),tid);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_shape_chunk_filter,T,field_test_types)
    {
        auto f= create_field<T>(o_group,"f1",shape,chunk,filter);
        type_id_t tid = type_id_map<T>::type_id; 

        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f1");
        BOOST_CHECK_EQUAL(get_type(f),tid);

        f= create_field(o_group,tid,"f2",shape,chunk,filter);
        BOOST_CHECK(is_valid(f));
        BOOST_CHECK_EQUAL(get_rank(f),2);
        BOOST_CHECK_EQUAL(get_size(f),2048);
        BOOST_CHECK_EQUAL(get_name(f),"f2");
        BOOST_CHECK_EQUAL(get_type(f),tid);
    }

BOOST_AUTO_TEST_SUITE_END()


