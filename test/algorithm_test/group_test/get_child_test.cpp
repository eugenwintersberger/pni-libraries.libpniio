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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/get_child.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

struct get_child_test_fixture : algorithm_test_fixture
{
    get_child_test_fixture():
        algorithm_test_fixture("get_child_test.nx")
    {
        h5::nxgroup group = root.create_group("scan_1","NXentry");
        group.create_group("beamline","NXinstrument");
        group.create_field<string>("date");
        group.create_field<string>("experiment_id");
        group.create_group("data","NXdata");
        group.create_group("control","NXmonitor");
    }
};

BOOST_FIXTURE_TEST_SUITE(get_child_test,get_child_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_index)
    {
        h5::nxgroup parent = get_object(root,":NXentry");
        h5::nxobject child;
        BOOST_CHECK_NO_THROW(child=get_child(parent,0));
        BOOST_CHECK_EQUAL(get_name(child),"beamline");

        BOOST_CHECK_NO_THROW(child=get_child(parent,1));
        BOOST_CHECK_EQUAL(get_name(child),"control");
        
        BOOST_CHECK_THROW(get_child(parent,100),index_error);
        BOOST_CHECK_THROW(get_child(h5::nxgroup(),1),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_object_by_index)
    {
        auto parent = get_object(root,":NXentry");
        h5::nxobject child;
        BOOST_CHECK_NO_THROW(child=get_child(parent,0));
        BOOST_CHECK_EQUAL(get_name(child),"beamline");

        BOOST_CHECK_NO_THROW(child=get_child(parent,1));
        BOOST_CHECK_EQUAL(get_name(child),"control");
        
        BOOST_CHECK_THROW(get_child(parent,100),index_error);
        BOOST_CHECK_THROW(get_child(h5::nxgroup(),1),invalid_object_error);
    }


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_name)
    {
        auto parent = get_object(root,":NXentry");
        auto child  = get_child(parent,"control","");
        BOOST_CHECK_EQUAL(get_name(child),"control");
        BOOST_CHECK(is_class(child,"NXmonitor"));

        BOOST_CHECK_THROW(get_child(parent,"bla",""), key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_class)
    {
        auto parent = get_object(root,":NXentry");
        auto child  = get_child(parent,"","NXinstrument");
        BOOST_CHECK_EQUAL(get_name(child),"beamline");
        BOOST_CHECK(is_class(child,"NXinstrument"));

        BOOST_CHECK_THROW(get_child(parent,"","NXfoo"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_name_class)
    {
        auto child = get_child(root,"scan_1","NXentry");
        BOOST_CHECK_EQUAL(get_name(child),"scan_1");
        BOOST_CHECK(is_class(child,"NXentry"));

        BOOST_CHECK_THROW(get_child(root,"scan_1","NXfoo"),key_error);
        BOOST_CHECK_THROW(get_child(root,"foo","NXentry"),key_error);
        BOOST_CHECK_THROW(get_child(root,"foo","NXfoo"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_name)
    {
        auto parent = get_object(root,":NXentry");
        auto child  = get_child(parent,"date","");
        BOOST_CHECK(is_field(child));
        BOOST_CHECK_EQUAL(get_name(child),"date");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_object)
    {
        h5::nxobject parent = root;
        BOOST_CHECK(is_valid(get_child(parent,"scan_1","")));
        BOOST_CHECK(is_valid(get_child(parent,"","NXentry")));
        BOOST_CHECK(is_valid(get_child(parent,"scan_1","NXentry")));
        BOOST_CHECK_THROW(get_child(parent,"log",""),key_error);
        BOOST_CHECK_THROW(get_child(parent,"","NXlog"),key_error);
        BOOST_CHECK_THROW(get_child(parent,"log","NXlog"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_object)
    {
        BOOST_CHECK_THROW(get_child(o_field,"",""),type_error); 
        BOOST_CHECK_THROW(get_child(o_field,1),type_error);
    }

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute_object)
    {
        BOOST_CHECK_THROW(get_child(o_attribute,"",""),type_error);
        BOOST_CHECK_THROW(get_child(o_attribute,1),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

