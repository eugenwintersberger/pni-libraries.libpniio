//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Mar 07, 2016
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/link.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/nx/xml.hpp>

#include "../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

static const string file_structure = 
"<group name=\"entry\" type=\"NXentry\">"
"  <group name=\"instrument\" type=\"NXinstrument\">"
"     <group name=\"detector\" type=\"NXdetector\">"
"         <field name=\"data\" type=\"uint16\" units=\"au\"/>"
"     </group>"
"  </group>"
"  <group name=\"data\" type=\"NXdata\">"
"</group>"
"</group>"
"<group name=\"links\"/>" ;


struct get_links_test_fixture : base_fixture
{
    h5::nxgroup location;
    get_links_test_fixture():
        base_fixture("get_links_test.nxs")
    {
        xml::node n = xml::create_from_string(file_structure);
        xml::xml_to_nexus(n,root); 
        location = get_object(root,"/links");
    }

};


BOOST_FIXTURE_TEST_SUITE(get_links_test,get_links_test_fixture)

    using link_vector = std::vector<h5::nxlink>;
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        location = get_object(root,"/entry");
        auto links = get_links<link_vector>(location);
        BOOST_CHECK_EQUAL(links.size(),2);
        BOOST_CHECK_EQUAL(links[0].name(),"data");
        BOOST_CHECK_EQUAL(links[1].name(),"instrument");
    }

    BOOST_AUTO_TEST_CASE(test_append)
    {
        location = get_object(root,"/entry");
        link_vector links;
        get_links<link_vector>(location,links);
        BOOST_CHECK_EQUAL(links.size(),2);
        BOOST_CHECK_EQUAL(links[0].name(),"data");
        BOOST_CHECK_EQUAL(links[1].name(),"instrument");
    }


BOOST_AUTO_TEST_SUITE_END()
