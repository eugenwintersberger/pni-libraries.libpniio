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
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/nexus_to_xml.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/get_child.hpp>
#include <fstream>
#include "../xml_test_common.hpp"

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(detector_with_transformation_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test)
    {
        h5::nxfile file = h5::nxfile::open_file("detector_with_transformation.nxs");
        auto root_group = file.root();
        
        xml::node root_node;
        auto p = get_object(root_group,":NXentry");
        xml::nexus_to_xml(p,root_node,
                     [](const h5::nxobject &o) { return get_size(o) <= 3; });
                     
        xml::node refnode = xml::create_from_file("detector_with_transformation.xml");
        BOOST_CHECK(compare_trees(root_node,refnode)); 
    }

BOOST_AUTO_TEST_SUITE_END()
