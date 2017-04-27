//
// (c) Copyright 2016 Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// 
// ===========================================================================

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/link.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/nx/xml.hpp>

#include "../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

static const string file_structure = 
"<group name=\"entry\" type=\"NXentry\">"
"  <group name=\"instrument\" type=\"NXinstrument\"/>"
"  <link name=\"instrument_link\" target=\"/entry/instrument\"/>"
"  <link name=\"external\" target=\"test.nxs://scan_2\"/>"
"</group>";


struct link_test_fixture : base_fixture
{
    h5::nxgroup location;
    link_test_fixture():
        base_fixture("link_test.nxs")
    {
        xml::node n = xml::create_from_string(file_structure);
        xml::xml_to_nexus(n,root); 
        location = get_object(root,"entry");
    }

};


BOOST_FIXTURE_TEST_SUITE(link_test,link_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_hard)
    {
        h5::nxlink l(location,"instrument"); 
        BOOST_CHECK_EQUAL(l.name(),"instrument");
        BOOST_CHECK_EQUAL(l.status(),nxlink_status::VALID);
        BOOST_CHECK_EQUAL(l.type(),nxlink_type::HARD);
        BOOST_CHECK(l.is_valid());
        BOOST_CHECK_EQUAL(l.filename(),"link_test.nxs");
        BOOST_CHECK_EQUAL(l.target_path(),
                          nxpath::from_string("link_test.nxs://entry/instrument"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_soft)
    {
        h5::nxlink l(location,"instrument_link"); 
        BOOST_CHECK_EQUAL(l.name(),"instrument_link");
        BOOST_CHECK_EQUAL(l.status(),nxlink_status::VALID);
        BOOST_CHECK_EQUAL(l.type(),nxlink_type::SOFT);
        BOOST_CHECK(l.is_valid());
        BOOST_CHECK_EQUAL(l.filename(),"link_test.nxs");
        BOOST_CHECK_EQUAL(l.target_path(),
                          nxpath::from_string("link_test.nxs://entry/instrument"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_external)
    {
        h5::nxlink l(location,"external"); 
        BOOST_CHECK_EQUAL(l.name(),"external");
        BOOST_CHECK_EQUAL(l.status(),nxlink_status::INVALID);
        BOOST_CHECK_EQUAL(l.type(),nxlink_type::EXTERNAL);
        BOOST_CHECK(!l.is_valid());
        BOOST_CHECK_EQUAL(l.filename(),"link_test.nxs");
        BOOST_CHECK_EQUAL(l.target_path(),
                          nxpath::from_string("test.nxs://scan_2"));
    }

BOOST_AUTO_TEST_SUITE_END()

