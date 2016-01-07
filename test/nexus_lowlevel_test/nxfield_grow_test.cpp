//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "test_types.hpp"
#include "nxfield_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxfield_grow_test_fixture : nxfield_test_fixture
{
    nxfield_grow_test_fixture():
        nxfield_test_fixture("nxfield_grow_test.nxs")
    {}
};


BOOST_FIXTURE_TEST_SUITE(nxfield_grow_test,nxfield_grow_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_grow_1d,T,field_test_types)
    {
        h5::nxfield field = create_field<T>("test",shape_t{0});
        BOOST_CHECK(field.is_valid());
        BOOST_CHECK_EQUAL(field.size(),0);
        BOOST_CHECK_EQUAL(field.rank(),1);

        BOOST_CHECK_NO_THROW(field.grow(0,1));
        BOOST_CHECK_EQUAL(field.size(),1);

        BOOST_CHECK_NO_THROW(field.grow(0,10));
        BOOST_CHECK_EQUAL(field.size(),11);
       
        BOOST_CHECK_THROW(field.grow(1,3),index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_grow_2d,T,field_test_types)
    {
        h5::nxfield f = create_field<T>("test",shape_t{3,4});
        BOOST_CHECK_EQUAL(f.rank(),2);
        BOOST_CHECK_EQUAL(f.size(),12);

        BOOST_CHECK_NO_THROW(f.grow(0,2));
        BOOST_CHECK_EQUAL(f.size(),20);

        BOOST_CHECK_NO_THROW(f.grow(1,4));
        BOOST_CHECK_EQUAL(f.size(),40);
    }

BOOST_AUTO_TEST_SUITE_END()


