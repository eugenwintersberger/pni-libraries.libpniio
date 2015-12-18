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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test XML to NeXus conversion

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/xml_to_nexus.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/core/types.hpp>
#include "utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(simple_structure_test)
    

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        h5::nxfile file = h5::nxfile::create_file("simple_structure.nxs",true);
        h5::nxgroup root_group = file.root();

        xml::node root_node = xml::create_from_file("simple_structure.xml");
        
        BOOST_CHECK_NO_THROW(xml::xml_to_nexus(root_node,root_group));

        BOOST_CHECK_EQUAL(get_size(root_group),1);
        auto g = get_object(root_group,":NXentry");
        BOOST_CHECK_EQUAL(get_size(g),6);

        test_field(get_object(g,"title"),"title",type_id_t::STRING);
        test_field(get_object(g,"experiment_identifier"),"experiment_identifier",type_id_t::STRING);
        test_field(get_object(g,"experiment_description"),"experiment_description",type_id_t::STRING);

        test_group(get_object(g,"instrument"),"instrument","NXinstrument");
        test_group(get_object(g,"sample"),"sample","NXsample");
        test_group(get_object(g,"data"),"data","NXdata");

        g = get_object(root_group,":NXentry/:NXinstrument/:NXsource");
        test_group(g,"storage_ring","NXsource");

        test_field(get_object(g,"distance"),"distance",type_id_t::FLOAT64,1,"m");
        test_field(get_object(g,"name"),"name",type_id_t::STRING,1,"");
        test_field(get_object(g,"type"),"type",type_id_t::STRING,1,"");
        test_field(get_object(g,"sigma_x"),"sigma_x",type_id_t::FLOAT64,1,"um");
        test_field(get_object(g,"sigma_y"),"sigma_y",type_id_t::FLOAT64,1,"um");

    }

BOOST_AUTO_TEST_SUITE_END()

