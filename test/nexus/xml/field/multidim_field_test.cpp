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

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "field_test_fixture.hpp"
#include "test_types.hpp"
#include "field_utils.hpp"
#include "multidim_ref_data.hpp"
#include "../../check_equal.hpp"


using namespace pni;
using namespace pni::nexus;

struct MultidimFieldFixture : FieldTestFixture
{
    MultidimFieldFixture():
        FieldTestFixture("multidim_test_")
    { }
};

BOOST_FIXTURE_TEST_SUITE(multidim_field_test,MultidimFieldFixture)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_inquery,T,mdim_test_types)
    {
        typedef std::vector<T> array_type;
        typedef mdim_ref_data<T> ref_data;
        set_parent<T>();
        BOOST_CHECK_NO_THROW(root_node  = xml::create_from_file(xml_file_name<T>()));
        BOOST_CHECK_NO_THROW(child_node = xml::get_child_by_name(root_node.get_child("group"),"data"));
        
        BOOST_CHECK(xml_test::field_test::size(child_node) == 3);
        BOOST_CHECK(xml_test::field_test::rank(child_node) == 1);
        BOOST_CHECK(xml_test::field_test::type_id(child_node) == get_type_id<T>());
       
        array_type data;
        xml_test::field_test::data_from_xml(child_node,data);

        auto r_iter = ref_data::data.begin();
        auto d_iter = data.begin();
        for(;d_iter != data.end(); ++d_iter, ++r_iter)
            check_equal(*d_iter,*r_iter);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_object,T,mdim_test_types)
    {
        set_parent<T>();
        root_node = xml::create_from_file(xml_file_name<T>());
        child_node = xml::get_child_by_name(root_node.get_child("group"),"data");

        //attach the field to the group
        h5::nxfield field = xml_test::field_test::object_from_xml(nx_parent,child_node);

        BOOST_CHECK(field.size() == 3);
        BOOST_CHECK(field.rank() == 1);
        BOOST_CHECK(field.type_id() == get_type_id<T>());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_compression_object,T,mdim_test_types)
    {
        set_parent<T>();
        root_node = xml::create_from_file(xml_file_name<T>());
        child_node = xml::get_child_by_name(root_node.get_child("group"),"data_comp");

        //attach the field to the group
        h5::nxfield field = xml_test::field_test::object_from_xml(nx_parent,child_node);

        BOOST_CHECK(field.size() == 2048*512);
        BOOST_CHECK(field.rank() == 3);
        BOOST_CHECK(field.type_id() == get_type_id<T>());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_chunked_field,T,mdim_test_types)
    {
        set_parent<T>();
        root_node = xml::create_from_file(xml_file_name<T>());
        child_node = xml::get_child_by_name(root_node.get_child("group"),"data_chunk");

        //attach the field to the group
        h5::nxfield field = xml_test::field_test::object_from_xml(nx_parent,child_node);

        BOOST_CHECK(field.size() == 2048);
        BOOST_CHECK(field.rank() == 2);
        BOOST_CHECK(field.type_id() == get_type_id<T>());
        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_object,T,mdim_test_types)
    {
        set_parent<T>();
        typedef mdim_ref_data<T> ref_data;
        h5::nxobject field = get_child(nx_parent,"data");
        BOOST_CHECK_NO_THROW(write(field,ref_data::data));

        root_node.add_child("group",xml::group::object_to_xml(h5::nxobject(root)));
        xml::node field_node;
        BOOST_CHECK_NO_THROW(field_node = xml_test::field_test::object_to_xml(field));
        xml_test::field_test::data_to_xml(ref_data::data,field_node);
        child_node = root_node.add_child("group.field",field_node);

        BOOST_CHECK(xml_test::field_test::size(child_node) == 3);
        BOOST_CHECK(xml_test::field_test::rank(child_node) == 1);
        BOOST_CHECK(xml_test::field_test::type_id(child_node) == get_type_id<T>());

    }

BOOST_AUTO_TEST_SUITE_END()
