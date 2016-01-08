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
#include <pni/io/nx/algorithms/get_parent.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/is_group.hpp>
#include <pni/io/nx/algorithms/as_group.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::io::nx;
using namespace pni::core;
using pni::io::invalid_object_error;

struct get_parent_test_suite : algorithm_test_fixture
{
    static const string data_path;
    static const string inst_path;
    static const string attr_path;

    get_parent_test_suite():
        algorithm_test_fixture("get_parent_test.nx")
    {
        root.create_group("entry","NXentry").
             create_group("instrument","NXinstrument").
             create_group("detector","NXdetector");

        h5::nxgroup g = get_object(root,":NXentry/:NXinstrument/:NXdetector");
        g.create_field<int32>("data",shape_t{0,1024,1024});
    }
};

const string get_parent_test_suite::data_path = 
":NXentry/:NXinstrument/:NXdetector/data";

const string get_parent_test_suite::inst_path = 
":NXentry/:NXinstrument";

const string get_parent_test_suite::attr_path = 
":NXentry/:NXinstrument@NX_class";


BOOST_FIXTURE_TEST_SUITE(get_parent_test,get_parent_test_suite)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        h5::nxobject instrument ;
        BOOST_CHECK_THROW(get_parent(instrument),invalid_object_error);

        instrument= get_object(root,inst_path);
        BOOST_CHECK(is_valid(get_parent(instrument)));
        BOOST_CHECK_EQUAL(get_name(get_parent(instrument)),"entry");
        BOOST_CHECK_EQUAL(get_name(get_parent(get_parent(instrument))),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        h5::nxgroup instrument = get_object(root,inst_path);
        BOOST_CHECK(is_valid(get_parent(instrument)));
        BOOST_CHECK_EQUAL(get_name(get_parent(instrument)),"entry");
        BOOST_CHECK_EQUAL(get_name(get_parent(get_parent(instrument))),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        h5::nxobject data = get_object(root,data_path);
        BOOST_CHECK_EQUAL(get_name(get_parent(data)),"detector");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        h5::nxfield data = get_object(root,data_path);
        BOOST_CHECK_EQUAL(get_name(get_parent(data)),"detector");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        h5::nxobject attr = get_object(root,attr_path);

        BOOST_CHECK(is_group(get_parent(attr)));
        BOOST_CHECK(is_valid(get_parent(attr)));
        BOOST_CHECK_EQUAL(get_name(get_parent(attr)),"instrument");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        h5::nxattribute attr = get_object(root,attr_path);
        BOOST_CHECK_EQUAL(get_name(get_parent(attr)), "instrument");
    }

BOOST_AUTO_TEST_SUITE_END()
