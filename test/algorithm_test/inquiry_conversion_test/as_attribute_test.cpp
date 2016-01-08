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
#include <pni/io/nx/algorithms/as_attribute.hpp>

#include "inquiry_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct as_attribute_test_fixture : inquiry_test_fixture
{
    as_attribute_test_fixture():
        inquiry_test_fixture("as_attribute_test.nx")
    {}
};


BOOST_FIXTURE_TEST_SUITE(as_attribute_test,as_attribute_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        BOOST_CHECK_THROW(as_attribute(group),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_THROW(as_attribute(field),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        //this shoud work as we are trying to retrieve a real attribute
        h5::nxattribute a;
        BOOST_CHECK_NO_THROW(a = as_attribute(attribute));
        BOOST_CHECK(a.is_valid());
        BOOST_CHECK_EQUAL(a.name(),"NX_class");
    }

BOOST_AUTO_TEST_SUITE_END()
