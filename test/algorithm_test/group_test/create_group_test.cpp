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
// ==========================================================================
//
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/create_group.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct create_group_test_fixture : algorithm_test_fixture
{
    create_group_test_fixture():
        algorithm_test_fixture("create_group_test.nx")
    {}
};

BOOST_FIXTURE_TEST_SUITE(create_group_test,create_group_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_name_only)
    {
        h5::nxobject ng;
        BOOST_CHECK_NO_THROW(ng = create_group(o_group,"scan_1"));
        BOOST_CHECK(is_valid(ng));
        BOOST_CHECK(is_group(ng));
        BOOST_CHECK_EQUAL(get_name(ng),"scan_1");
        BOOST_CHECK_EQUAL(get_class(ng),"");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_name_and_class)
    {
        h5::nxobject ng;
        BOOST_CHECK_NO_THROW(ng = create_group(o_group,"scan_1:NXentry"));
        BOOST_CHECK(is_valid(ng));
        BOOST_CHECK(is_group(ng));
        BOOST_CHECK_EQUAL(get_name(ng),"scan_1");
        BOOST_CHECK_EQUAL(get_class(ng),"NXentry");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_from_path)
    {
        h5::nxobject ng;
        BOOST_CHECK_NO_THROW(ng = create_group(o_group,
                                nxpath::from_string("scan_2:NXentry")));
        BOOST_CHECK(is_valid(ng));
        BOOST_CHECK(is_group(ng));
        BOOST_CHECK_EQUAL(get_name(ng), "scan_2");
        BOOST_CHECK(pni::io::nx::is_class(ng,"NXentry"));

        BOOST_CHECK_NO_THROW(ng = create_group(ng, 
                             nxpath::from_string("../scan_3:NXentry")));
        BOOST_CHECK(is_valid(ng));
        BOOST_CHECK(is_group(ng));
        BOOST_CHECK(pni::io::nx::is_class(ng,"NXentry"));
        BOOST_CHECK_EQUAL(get_name(ng),"scan_3");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_errors)
    {
        BOOST_CHECK_THROW(create_group(o_group,":NXentry"),value_error);
        BOOST_CHECK_THROW(create_group(o_group,":NXentry/collection:NXcollection"),
                             key_error);


    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_THROW(create_group(o_field,"g1:NXlog"),type_error);
        BOOST_CHECK_THROW(create_group(o_field,"g2:NXlog"),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(create_group(o_attribute,"g1:NXlog"),type_error);
        BOOST_CHECK_THROW(create_group(o_attribute,"g2:NXlog"),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()

