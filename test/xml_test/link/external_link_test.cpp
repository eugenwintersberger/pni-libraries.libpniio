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
//  Created on: Apr 22, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml/link.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>

using namespace pni::core;
using namespace pni::io::nx;

struct external_link_fixture
{
    static const string xml_file_name;
    static const string nxs_data_file_name;
    static const string nxs_link_file_name;
    
    h5::nxfile nxs_file;        
    xml::node root_node;
    xml::node link_node;

    static void create_external_data();

    external_link_fixture():
        nxs_file(),
        root_node(xml::create_from_file(xml_file_name)),
        link_node(root_node.get_child("link"))
    {
        create_external_data();
        //generate the basic NeXus file structure
        nxs_file = h5::nxfile::create_file(nxs_link_file_name,true);
    }

    ~external_link_fixture()
    {
        nxs_file.close();
    }

};

void external_link_fixture::create_external_data()
{
    //generate the basic NeXus file structure
    h5::nxfile  file = h5::nxfile::create_file(nxs_data_file_name,true);
    h5::nxgroup root_group = file.root();
    
    h5::nxgroup g = root_group.create_group("data","NXdata");
    g.create_field<uint16>("data",shape_t{1,1024,2048});
}

const string external_link_fixture::xml_file_name = "external_link_test.xml";
const string external_link_fixture::nxs_data_file_name = "external_link_data.nxs";
const string external_link_fixture::nxs_link_file_name = "external_link_link.nxs";

BOOST_FIXTURE_TEST_SUITE(external_link_test,external_link_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_link)
    {
        BOOST_CHECK(xml::has_attribute(link_node,"name"));
        BOOST_CHECK(xml::has_attribute(link_node,"target"));
        
        h5::nxobject root = nxs_file.root();
        BOOST_CHECK_NO_THROW(xml::link::object_from_xml(root,link_node));
        
        h5::nxfield ldata;    
        ldata = get_object(root,"linked_data");
        BOOST_CHECK_EQUAL(ldata.size(),1024*2048);
        BOOST_CHECK_EQUAL(ldata.type_id(),type_id_t::UINT16);
        BOOST_CHECK_EQUAL(ldata.rank(),3);
    }

BOOST_AUTO_TEST_SUITE_END()
