//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Apr 24, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/nexus_to_xml.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "../xml_test_common.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using namespace boost::property_tree;

BOOST_AUTO_TEST_SUITE(simple_structure_test)

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test)
    {
        h5::nxfile file = h5::nxfile::open_file("simple_structure.nxs");
        auto root_group = file.root();
        
        xml::node root_node;
        auto p = get_object(root_group,":NXentry");
        BOOST_CHECK_NO_THROW(xml::nexus_to_xml(p,root_node,
                        [](const h5::nxobject &o) { return get_size(o) == 1;
                        }));
                       
        xml::node refnode = xml::create_from_file("simple_structure.xml");

        BOOST_CHECK(compare_trees(root_node,refnode));
    }

BOOST_AUTO_TEST_SUITE_END()
