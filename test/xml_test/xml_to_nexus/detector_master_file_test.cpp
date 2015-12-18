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
#include <pni/core/types.hpp>
#include <pni/io/nx/xml/xml_to_nexus.hpp>

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(detector_master_file_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_data_file)
    {
        h5::nxfile file = h5::nxfile::create_file("detector_data_file.nxs",true);
        auto root_group = file.root();
        
        xml::node root_node = xml::create_from_file("detector_data_file.xml");
        
        xml::xml_to_nexus(root_node,root_group,
                        [](const h5::nxobject &o) { return get_size(o) <= 3; });
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_master_file)
    {
        h5::nxfile file = h5::nxfile::create_file("detector_master_file.nxs",true);
        auto root_group = file.root();
        
        xml::node root_node = xml::create_from_file("detector_master_file.xml");
        
        xml::xml_to_nexus(root_node,root_group,
                        [](const h5::nxobject &o) { return get_size(o) <= 3; });
    }

BOOST_AUTO_TEST_SUITE_END()

