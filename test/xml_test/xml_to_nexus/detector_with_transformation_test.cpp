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
#include <boost/test/floating_point_comparison.hpp>

#include "utils.hpp"
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/xml_to_nexus.hpp>


using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(detector_with_transformation_test)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test)
    {
        typedef static_array<float64,3> vector_type;
        h5::nxfile file = h5::nxfile::create_file("detector_with_transformation.nxs",true);
        h5::nxobject root_group = file.root();
        
        xml::node root_node = xml::create_from_file("detector_with_transformation.xml");
        
        xml::xml_to_nexus(root_node,root_group,
                        [](const h5::nxobject &o) { return get_size(o) <= 3; });

        string base = ":NXentry/:NXinstrument/:NXdetector/:NXtransformations";
        auto depends_on = get_object(root_group,base+"/gamma@depends_on");
        auto type = get_object(root_group,base+"/gamma@transformation_type");
        auto vector = get_object(root_group,base+"/gamma@vector");
        BOOST_CHECK_EQUAL(get_data<string>(depends_on),"delta");
        BOOST_CHECK_EQUAL(get_data<string>(type),"rotation");
        auto v = get_data<vector_type>(vector);
        shape_t ref{1,0,0};
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),ref.begin(),ref.end());


    }

BOOST_AUTO_TEST_SUITE_END()

