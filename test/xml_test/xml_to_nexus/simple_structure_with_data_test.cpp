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
//  Created on: Apr 23, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/xml_to_nexus.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/core/types.hpp>
#include "utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(simple_structure_with_data_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        h5::nxfile file = h5::nxfile::create_file("simple_structure_with_data.nxs",true);
        h5::nxgroup root_group = file.root();

        xml::node root_node = xml::create_from_file("simple_structure_with_data.xml");
        
        BOOST_CHECK_NO_THROW(xml::xml_to_nexus(root_node,root_group,
                        [](const h5::nxobject &o) { return get_size(o) == 1; })
                        );

        auto o = get_object(root_group,":NXentry/title");
        BOOST_CHECK_EQUAL(get_data<string>(o),"alignment scan");
        o = get_object(root_group,":NXentry/experiment_identifier");
        BOOST_CHECK_EQUAL(get_data<string>(o),"SI12453");
        o = get_object(root_group,":NXentry/experiment_description");
        BOOST_CHECK_EQUAL(get_data<string>(o),"Beamtime at PETRA III in March");

        o = get_object(root_group,":NXentry/:NXinstrument/:NXsource/name");
        BOOST_CHECK_EQUAL(get_data<string>(o),"PETRAIII");
        o = get_object(root_group,":NXentry/:NXinstrument/:NXsource/type");
        BOOST_CHECK_EQUAL(get_data<string>(o),"Synchrotron X-ray Source");
        o = get_object(root_group,":NXentry/:NXinstrument/:NXsource/distance");
        BOOST_CHECK_CLOSE(get_data<float64>(o),float64(40),1.e-16);
        o = get_object(root_group,":NXentry/:NXinstrument/:NXsource/sigma_x");
        BOOST_CHECK_CLOSE(get_data<float64>(o),float64(0.5),1.e-16);
        o = get_object(root_group,":NXentry/:NXinstrument/:NXsource/sigma_y");
        BOOST_CHECK_CLOSE(get_data<float64>(o),float64(0.4),1.e-16);

    }

BOOST_AUTO_TEST_SUITE_END()
