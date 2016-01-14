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
//  Created on: Jul 5, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/algorithms/create_attribute.hpp>
#include <pni/io/nx/algorithms/is_attribute.hpp>
#include <pni/io/nx/algorithms/get_rank.hpp>
#include <pni/io/nx/algorithms/get_size.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>

#include "../algorithm_test_fixture.hpp"
#include "../../nexus_lowlevel_test/test_types.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;
using pni::io::object_error;

struct create_attribute_test_fixture : algorithm_test_fixture
{
    static const shape_t shape;
    create_attribute_test_fixture():
        algorithm_test_fixture("create_attribute_test.nx")
    {}
};

const shape_t create_attribute_test_fixture::shape = {4,3};

BOOST_FIXTURE_TEST_SUITE(create_attribute_test,create_attribute_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_group_scalar,T,attribute_test_types)
    {
        h5::nxobject a;
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK_NO_THROW(a=create_attribute<T>(o_group,"test1"));
        BOOST_CHECK(is_valid(a));
        BOOST_CHECK(is_attribute(a));
        BOOST_CHECK_EQUAL(get_name(a),"test1");
        BOOST_CHECK_EQUAL(get_rank(a),0);
        BOOST_CHECK_EQUAL(get_type(a),tid);
        BOOST_CHECK_EQUAL(get_size(a),1);
        auto s = get_shape<shape_t>(a);
        BOOST_CHECK_EQUAL(s.size(),0);

        //by default overwrite is false - this should throw
        BOOST_CHECK_THROW(create_attribute<T>(o_group,"test1"),object_error);
        //if we wet overwrite to true - we can create a new attribute
        BOOST_CHECK_NO_THROW(a=create_attribute<T>(o_group,"test1",true));
        BOOST_CHECK_EQUAL(get_type(a),tid);

        BOOST_CHECK_NO_THROW(a = create_attribute(o_group,type_id_t::INT16,"test1",true));
        BOOST_CHECK_EQUAL(get_type(a),type_id_t::INT16);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_group_multidim,T,attribute_test_types)
    {
        h5::nxobject a;
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK(is_valid(a=create_attribute<T>(o_group,"test2",shape)));
        BOOST_CHECK(is_attribute(a));
        BOOST_CHECK_EQUAL(get_name(a),"test2");
        BOOST_CHECK_EQUAL(get_rank(a),2);
        BOOST_CHECK_EQUAL(get_type(a),tid);
        auto s = get_shape<shape_t>(a);
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),
                                      shape.begin(),shape.end());
        
        //by default overwrite is false - this should throw
        BOOST_CHECK_THROW(create_attribute<T>(o_group,"test2",shape),object_error);
        //if we wet overwrite to true - we can create a new attribute
        BOOST_CHECK_NO_THROW(a = create_attribute<T>(o_group,"test2",shape,true));
        BOOST_CHECK_EQUAL(get_type(a),tid);
        BOOST_CHECK_NO_THROW(a = create_attribute(o_group,type_id_t::INT16,"test2",true));
        BOOST_CHECK_EQUAL(get_type(a),type_id_t::INT16);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_scalar,T,attribute_test_types)
    {
        h5::nxobject a;
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK_NO_THROW(a=create_attribute<T>(o_field,"test1"));
        BOOST_CHECK(is_valid(a));
        BOOST_CHECK(is_attribute(a));
        BOOST_CHECK_EQUAL(get_name(a),"test1");
        BOOST_CHECK_EQUAL(get_rank(a),0);
        BOOST_CHECK_EQUAL(get_type(a),tid);
        BOOST_CHECK_EQUAL(get_size(a),1);
        auto s = get_shape<shape_t>(a);
        BOOST_CHECK_EQUAL(s.size(),0);

        //by default overwrite is false - this should throw
        BOOST_CHECK_THROW(create_attribute<T>(o_field,"test1"),object_error);
        //if we wet overwrite to true - we can create a new attribute
        BOOST_CHECK_NO_THROW(a = create_attribute<T>(o_field,"test1",true));
        BOOST_CHECK_EQUAL(get_type(a),tid);

        BOOST_CHECK_NO_THROW(a = create_attribute(o_field,type_id_t::INT16,"test1",true));
        BOOST_CHECK_EQUAL(get_type(a),type_id_t::INT16);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_multidim,T,attribute_test_types)
    {
        h5::nxobject a;
        type_id_t tid=type_id_map<T>::type_id;
        BOOST_CHECK(is_valid(a=create_attribute<T>(o_field,"test2",shape)));
        BOOST_CHECK(is_attribute(a));
        BOOST_CHECK_EQUAL(get_name(a),"test2");
        BOOST_CHECK_EQUAL(get_rank(a),2);
        BOOST_CHECK_EQUAL(get_type(a),tid);
        auto s = get_shape<shape_t>(a);
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),
                                      shape.begin(),shape.end());
        
        //by default overwrite is false - this should throw
        BOOST_CHECK_THROW(create_attribute<T>(o_field,"test2",shape),object_error);
        //if we wet overwrite to true - we can create a new attribute
        BOOST_CHECK_NO_THROW(a = create_attribute<T>(o_field,"test2",shape,true));
        BOOST_CHECK_EQUAL(get_type(a),tid);
        BOOST_CHECK_NO_THROW(a = create_attribute(o_field,type_id_t::INT16,"test2",true));
        BOOST_CHECK_EQUAL(get_type(a),type_id_t::INT16);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_attribute,T,attribute_test_types)
    {
        BOOST_CHECK_THROW(create_attribute<T>(o_attribute,"g1"),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_errors,T,attribute_test_types)
    {
        BOOST_CHECK_THROW(create_attribute<T>(h5::nxobject(),"test"),
                             invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()


