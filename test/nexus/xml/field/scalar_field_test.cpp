//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jan 15, 2016
//      Author: Eugen Wintersberger
//

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "field_utils.hpp"
#include "field_test_fixture.hpp"
#include "test_types.hpp"
#include "scalar_ref_data.hpp"
#include "../../check_equal.hpp"

#include <pni/nx/xml/node.hpp>
#include <pni/nx/algorithms/write.hpp>

using namespace pni;
using namespace pni::nx; 

struct scalar_field_fixture : field_test_fixture
{
    scalar_field_fixture():
        field_test_fixture("scalar_test_")
    {}

};

BOOST_FIXTURE_TEST_SUITE(scalar_field_test,scalar_field_fixture)


    BOOST_AUTO_TEST_CASE_TEMPLATE(test_inquery,T,scalar_test_types)
    {
        set_parent<T>();
        BOOST_CHECK_NO_THROW(root_node = xml::create_from_file(xml_file_name<T>()));
        BOOST_CHECK_NO_THROW(child_node = xml::get_child_by_name(root_node.get_child("group"),"data"));

        BOOST_CHECK(xml_test::field_test::size(child_node) == 1);
        BOOST_CHECK(xml_test::field_test::rank(child_node) == 0);
        BOOST_CHECK(xml_test::field_test::type_id(child_node) == get_type_id<T>());
      
        T data;
        xml_test::field_test::data_from_xml(child_node,data);
        check_equal(data,scalar_ref_data<T>::data);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_object,T,scalar_test_types)
    {
        set_parent<T>();
        BOOST_CHECK_NO_THROW(root_node = xml::create_from_file(xml_file_name<T>()));
        BOOST_CHECK_NO_THROW(child_node = xml::get_child_by_name(root_node.get_child("group"),"data"));

        //attach the attribute to the group
        h5::nxfield field = xml_test::field_test::object_from_xml(nx_parent,child_node);

        BOOST_CHECK(field.size() == 1);
        BOOST_CHECK(field.rank() == 1);
        BOOST_CHECK(field.type_id() == get_type_id<T>());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_object,T,scalar_test_types)
    {
        set_parent<T>();
        h5::nxobject field = get_child(nx_parent,"data");
        write(field,scalar_ref_data<T>::data);

        xml::node field_node = xml_test::field_test::object_to_xml(field);
        xml_test::field_test::data_to_xml(scalar_ref_data<T>::data,field_node);

        BOOST_CHECK(xml_test::field_test::size(field_node) == 1);
        BOOST_CHECK(xml_test::field_test::rank(field_node) == 0);
        BOOST_CHECK(xml_test::field_test::type_id(field_node) == get_type_id<T>());
    }

BOOST_AUTO_TEST_SUITE_END()
