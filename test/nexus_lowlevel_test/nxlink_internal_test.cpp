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
//  Created on: Mar 11, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxlink.hpp>
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
"</group>"
"<group name=\"links\"/>" ;


struct nxlink_internal_test_fixture : base_fixture
{
    h5::nxgroup location;
    nxlink_internal_test_fixture():
        base_fixture("nxlink_internal_test.nxs")
    {
        xml::node n = xml::create_from_string(file_structure);
        xml::xml_to_nexus(n,root); 
        location = get_object(root,"/links");
    }

};


BOOST_FIXTURE_TEST_SUITE(nxlink_internal_test,nxlink_internal_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_is_hard_link)
    {
        BOOST_CHECK(is_hard_link(root,"entry"));
        h5::nxgroup g = get_object(root,"/entry/instrument/detector");
        BOOST_CHECK(is_hard_link(g,"data"));
        BOOST_CHECK_EQUAL(link_status(g,"data"),nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_instance)
    {
        h5::nxfield target= get_object(root,"/entry/instrument/detector/data");

        BOOST_CHECK_NO_THROW(link(target,location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_soft_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),nxlink_status::VALID);
        nxpath t;
        BOOST_CHECK_NO_THROW(t = link_target(location,"link_field"));
        BOOST_CHECK_EQUAL(nxpath::to_string(t),
                          "nxlink_internal_test.nxs://entry/instrument/detector/data");
        BOOST_CHECK_NO_THROW(t = link_target(location,0));
        BOOST_CHECK_EQUAL(nxpath::to_string(t),
                          "nxlink_internal_test.nxs://entry/instrument/detector/data");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_string_absolute)
    {
        BOOST_CHECK_NO_THROW(link("/entry/instrument/detector/data",
                                  location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_soft_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),nxlink_status::VALID);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_string_relative)
    {
        BOOST_CHECK_NO_THROW(link("../entry/instrument/detector/data",
                                  location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_soft_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_path_relative)
    {
        nxpath target = nxpath::from_string("../entry/instrument/detector/data");
        BOOST_CHECK_NO_THROW(link(target,location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_soft_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_path_absolute)
    {
        nxpath target = nxpath::from_string("/entry/instrument/detector/data");
        BOOST_CHECK_NO_THROW(link(target,location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_soft_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),
                          nxlink_status::VALID);
    }
    
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_instance)
    {
        h5::nxgroup target = get_object(root,"/:NXentry/:NXinstrument/:NXdetector");
        BOOST_CHECK_NO_THROW(link(target,location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_soft_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_string_relative)
    {
        BOOST_CHECK_NO_THROW(link("../entry/instrument/detector",location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_soft_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_string_absolute)
    {
        BOOST_CHECK_NO_THROW(link("/entry/instrument/detector",location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_soft_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_path_relative)
    {
        nxpath p = nxpath::from_string("../entry/instrument/detector:NXdetector");
        BOOST_CHECK_NO_THROW(link(p,location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_soft_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_path_absolute)
    {
        nxpath p = nxpath::from_string("/entry/instrument/detector:NXdetector");
        BOOST_CHECK_NO_THROW(link(p,location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_soft_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_error)
    {
        BOOST_CHECK_THROW(link("/:NXentry/instrument/detector/data",location,"link"),
                             value_error);
        BOOST_CHECK_THROW(link(nxpath::from_string("/:NXentry/instrument/detector/data"),
                             location,"link"),value_error);

        BOOST_CHECK_THROW(link("/entry/../detector/data",location,"link"),
                             value_error);
    }

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_links)
    {
        auto target = nxpath::from_string("/entry/data/data");
        BOOST_CHECK_NO_THROW(link(target,location,"nxdata_link"));
        BOOST_CHECK_EQUAL(link_status(location,"nxdata_link"),
                          nxlink_status::INVALID);
    }

BOOST_AUTO_TEST_SUITE_END()
