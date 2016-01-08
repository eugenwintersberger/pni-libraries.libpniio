//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aug 21, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/algorithms/get_filename.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;
using pni::io::io_error;

struct get_filename_test_fixture : algorithm_test_fixture
{
    static const string filename;
    get_filename_test_fixture():
        algorithm_test_fixture("get_filename_test.nx")
    {}
};

const string get_filename_test_fixture::filename = "get_filename_test.nx";

BOOST_FIXTURE_TEST_SUITE(get_filename_test,get_filename_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_EQUAL(get_filename(root)  , filename);
        BOOST_CHECK_EQUAL(get_filename(group) , filename);
        BOOST_CHECK_THROW(get_filename(h5::nxgroup()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_EQUAL(get_filename(field), filename);
        BOOST_CHECK_THROW(get_filename(h5::nxfield()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_EQUAL(get_filename(attribute) , filename);
        BOOST_CHECK_THROW(get_filename(h5::nxattribute()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_group)
    {
        BOOST_CHECK_EQUAL(get_filename(o_group),filename);
        BOOST_CHECK_THROW(get_filename(h5::nxobject(h5::nxgroup())),
                             invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_field)
    {
        BOOST_CHECK_EQUAL(get_filename(o_field),filename);
        BOOST_CHECK_THROW(get_filename(h5::nxobject(h5::nxfield())),
                             invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nxobject_attribute)
    {
        BOOST_CHECK_EQUAL(get_filename(o_attribute) , filename);
        BOOST_CHECK_THROW(get_filename(h5::nxobject(h5::nxattribute())),
                             invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()


