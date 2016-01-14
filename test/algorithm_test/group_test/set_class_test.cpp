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
//  Created on: May 29, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/set_class.hpp>
#include <pni/io/nx/algorithms/is_group.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include "../algorithm_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::invalid_object_error;

struct set_class_test_fixture : algorithm_test_fixture
{
    set_class_test_fixture():
        algorithm_test_fixture("set_class_test.nx")
    {
        group = group.create_group("entry");
        o_group = group;
    }
};


BOOST_FIXTURE_TEST_SUITE(set_class_test,set_class_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        string buffer;

        //test on the plain nxgroup object
        BOOST_CHECK_NO_THROW(set_class(group,"NXentry"));
        group.attributes["NX_class"].read(buffer);
        BOOST_CHECK_EQUAL(buffer,"NXentry");
       
        //test on the object
        BOOST_CHECK_NO_THROW(set_class(o_group,"NXlog"));
        group.attributes["NX_class"].read(buffer);
        BOOST_CHECK_EQUAL(buffer,"NXlog");

        //test some exceptions
        BOOST_CHECK_THROW(set_class(h5::nxgroup(),"NXdetector"),
                             invalid_object_error);
        BOOST_CHECK_THROW(set_class(h5::nxobject(h5::nxgroup()),"NXinstrument"),
                             invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field)
    {
        BOOST_CHECK_THROW(set_class(o_field,"NXentry"),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        BOOST_CHECK_THROW(set_class(o_attribute,"NXentry"),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()
