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
#include <pni/io/nx/algorithms/get_path.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct get_path_test_fixture : algorithm_test_fixture
{
    get_path_test_fixture():
        algorithm_test_fixture("get_path_test.nx")
    {
        root.create_group("entry","NXentry").
             create_group("instrument","NXinstrument").
             create_group("detector","NXdetector");

        h5::nxgroup g = get_object(root,":NXentry/:NXinstrument/:NXdetector");
        g.create_field<uint32>("data",shape_t{0,1024,512});
    }
};

BOOST_FIXTURE_TEST_SUITE(get_path_test,get_path_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        h5::nxgroup g = get_object(root,":NXentry/:NXinstrument");
        BOOST_CHECK_EQUAL(get_path(g),"/entry:NXentry/instrument:NXinstrument");
        BOOST_CHECK_EQUAL(get_path(root), "/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        h5::nxfield f = get_object(root,"/entry/instrument/detector/data");
        BOOST_CHECK_EQUAL(get_path(f), "/entry:NXentry/instrument:"
                                       "NXinstrument/detector:NXdetector/"
                                       "data");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        h5::nxattribute a = get_object(root,"/@NX_class");
        BOOST_CHECK_EQUAL(get_path(a),"/@NX_class");

        a = get_object(root,"/entry@NX_class");
        BOOST_CHECK_EQUAL(get_path(a),"/entry:NXentry@NX_class");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        auto g = get_object(root,":NXentry/:NXinstrument");
        BOOST_CHECK_EQUAL(get_path(g),"/entry:NXentry/instrument:NXinstrument");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        h5::nxobject f = get_object(root,":NXentry/:NXinstrument/:NXdetector"
                                         "/data");
        BOOST_CHECK_EQUAL(get_path(f),"/entry:NXentry/instrument:NXinstrument"
                                      "/detector:NXdetector/data");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        auto a = get_object(root,"/@NX_class");
        BOOST_CHECK_EQUAL(get_path(a),"/@NX_class");

        a = get_object(root,"/entry@NX_class");
        BOOST_CHECK_EQUAL(get_path(a),"/entry:NXentry@NX_class");
       
    }


BOOST_AUTO_TEST_SUITE_END()

