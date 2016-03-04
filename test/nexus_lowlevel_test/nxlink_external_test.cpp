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
//  Created on: Mar 12, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/algorithms.hpp>
#include "../base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

const string target_file_struct = 
"<group name=\"entry\" type=\"NXentry\">"
"  <group name=\"instrument\" type=\"NXinstrument\">"
"     <group name=\"detector\" type=\"NXdetector\">"
"         <field name=\"data\" type=\"uint16\" units=\"au\"/>"
"     </group>"
"  </group>"
"</group>";

const string link_file_struct =
"<group name=\"entry\" type=\"NXentry\">"
"<group name=\"data\" type=\"NXdata\"/>"
"</group>";


struct nxlink_external_test_fixture : base_fixture
{
    static const string link_file_name;
    static const string target_file_name;

    h5::nxgroup location;

    nxlink_external_test_fixture():
        base_fixture(link_file_name)
    {
        xml::node n = xml::create_from_string(link_file_struct);
        xml::xml_to_nexus(n,root);
        location = get_object(root,"/:NXentry/:NXdata");

        n = xml::create_from_string(target_file_struct);
        h5::nxfile target= h5::nxfile::create_file(target_file_name,true);
        h5::nxgroup r = target.root();
        xml::xml_to_nexus(n,r);
    }

    ~nxlink_external_test_fixture()
    {
        location.close();
    }
};

const string nxlink_external_test_fixture::link_file_name = 
"nxlink_external_test.link.nxs";
const string nxlink_external_test_fixture::target_file_name = 
"nxlink_external_test.target.nxs";


BOOST_FIXTURE_TEST_SUITE(nxlink_external_test,nxlink_external_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_string)
    {
        BOOST_CHECK_NO_THROW(link(target_file_name+"://entry/instrument/detector/data",
                                location,"link_field"));

        h5::nxfield field = get_object(location,"link_field");
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_external_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),
                          nxlink_status::VALID);
        nxpath t;
        BOOST_CHECK_NO_THROW(t = link_target(location,"link_field"));
        BOOST_CHECK_EQUAL(nxpath::to_string(t),
                          target_file_name+"://entry/instrument/detector/data");
        BOOST_CHECK_NO_THROW(t = link_target(location,0));
        BOOST_CHECK_EQUAL(nxpath::to_string(t),
                          target_file_name+"://entry/instrument/detector/data");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_field_by_path)
    {
        nxpath target = nxpath::from_string(target_file_name+
                         "://entry:NXentry/instrument/detector:NXdetector/data");
        BOOST_CHECK_NO_THROW(link(target,location,"link_field"));

        h5::nxfield field = location["link_field"];
        BOOST_CHECK_EQUAL(get_unit(field),"au");
        BOOST_CHECK(is_external_link(location,"link_field"));
        BOOST_CHECK_EQUAL(link_status(location,"link_field"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_string)
    {
        BOOST_CHECK_NO_THROW(link(target_file_name+"://entry/instrument/detector",
                                     location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_external_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group_by_path)
    {
        nxpath p = nxpath::from_string(target_file_name+
                   "://entry:NXentry/instrument/detector:NXdetector");
        BOOST_CHECK_NO_THROW(link(p,location,"link_group"));
        h5::nxgroup g = location["link_group"];
        BOOST_CHECK_EQUAL(get_class(g),"NXdetector");
        BOOST_CHECK(is_external_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::VALID); 
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_error)
    {
        BOOST_CHECK_THROW(link(target_file_name+"://:NXentry/instrument/detector/data",location,"link"),
                             value_error);
        BOOST_CHECK_THROW(link(nxpath::from_string(target_file_name+"://:NXentry/instrument/detector/data"),
                             location,"link"),value_error);

        BOOST_CHECK_THROW(link(target_file_name+"://entry/../instrument/detector/data",location,"link"),
                             value_error);
        BOOST_CHECK_THROW(link(target_file_name+"://../entry/../detector/data",location,"link"),
                             value_error);
    }

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_links)
    {
        nxpath p = nxpath::from_string("blabla.nxs"
                "://entry:NXentry/instrument/detector:NXdetector");
        BOOST_CHECK_NO_THROW(link(p,location,"link_group"));
        BOOST_CHECK(is_external_link(location,"link_group"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group"),
                          nxlink_status::INVALID); 


        p = nxpath::from_string(target_file_name+
                   "://entry:NXentry/data:NXdata");
        BOOST_CHECK_NO_THROW(link(p,location,"link_group2"));
        BOOST_CHECK(is_external_link(location,"link_group2"));
        BOOST_CHECK_EQUAL(link_status(location,"link_group2"),
                          nxlink_status::INVALID); 
        
    }

BOOST_AUTO_TEST_SUITE_END()
