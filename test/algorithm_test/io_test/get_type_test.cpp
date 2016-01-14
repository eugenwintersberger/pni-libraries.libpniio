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
#include <pni/io/nx/algorithms/get_type.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_traits.hpp>

#include "io_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

struct get_type_test_fixture : io_test_fixture
{
    get_type_test_fixture():
        io_test_fixture("get_type_test.nx")
    {}
};


BOOST_FIXTURE_TEST_SUITE(get_type_test,get_type_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_THROW(get_type(o_group),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {

        BOOST_CHECK_EQUAL(get_type(o_mdim_field),type_id_t::FLOAT64);
        BOOST_CHECK_EQUAL(get_type(mdim_field),type_id_t::FLOAT64);
        
        BOOST_CHECK_EQUAL(get_type(o_scalar_field),type_id_t::FLOAT32);
        BOOST_CHECK_EQUAL(get_type(scalar_field),type_id_t::FLOAT32);

        BOOST_CHECK_THROW(get_type(h5::nxfield()),invalid_object_error);
        BOOST_CHECK_THROW(get_type(h5::nxobject(h5::nxfield())),
                                   invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_EQUAL(get_type(o_mdim_attribute),type_id_t::UINT16);
        BOOST_CHECK_EQUAL(get_type(mdim_attribute),type_id_t::UINT16);
        
        BOOST_CHECK_EQUAL(get_type(o_scalar_attribute),type_id_t::STRING);
        BOOST_CHECK_EQUAL(get_type(scalar_attribute),type_id_t::STRING);

        BOOST_CHECK_THROW(get_type(h5::nxattribute()),invalid_object_error);
        BOOST_CHECK_THROW(get_type(h5::nxobject(h5::nxattribute())),
                             invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()
