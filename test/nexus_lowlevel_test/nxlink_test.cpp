//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aug 20, 2013
//      Author: Eugen Wintersberger
//

#include<cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include "nxlink_test.hpp"
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/algorithms.hpp>



CPPUNIT_TEST_SUITE_REGISTRATION(nxlink_test);

//------------------------------------------------------------------------------
void nxlink_test::setUp()
{
    target_file = h5::nxfile::create_file("nxlink_target_test.h5",true);
    h5::nxgroup root_group = target_file.root();
    root_group.create_group("entry","NXentry");
    target_group = root_group.create_group("/entry/detector","NXdetector");
    target_field = root_group.create_field<uint16>("/entry/detector/data");

    location = root_group.create_group("links");
    
}

//------------------------------------------------------------------------------
void nxlink_test::test_hard_type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxgroup root_group = target_file.root();
    //test for group
    CPPUNIT_ASSERT(link_type(root_group,"links")==nxlink_type::HARD);
    CPPUNIT_ASSERT(is_hard_link(root_group,"links"));
    CPPUNIT_ASSERT(!is_soft_link(root_group,"links"));
    CPPUNIT_ASSERT(!is_external_link(root_group,"links"));

    h5::nxgroup p = as_group(target_field.parent());
    CPPUNIT_ASSERT(link_type(p,"data")==nxlink_type::HARD);
    CPPUNIT_ASSERT(is_hard_link(p,"data"));
    CPPUNIT_ASSERT(!is_soft_link(p,"data"));
    CPPUNIT_ASSERT(!is_external_link(p,"data"));
}

//------------------------------------------------------------------------------
void nxlink_test::tearDown()
{
    target_field.close();
    target_group.close();
    location.close();
	target_file.close();
}

//------------------------------------------------------------------------------
void nxlink_test::test_field_internal_link()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxgroup root_group = target_file.root();
    nxpath p = nxpath::from_string("/entry/detector/data");
    link(p,location,"detector_data_1");

    link("/entry/detector/data",location,"detector_data_2");
    CPPUNIT_ASSERT(link_type(location,"detector_data_2")==nxlink_type::SOFT);
    CPPUNIT_ASSERT(is_soft_link(location,"detector_data_2"));
    CPPUNIT_ASSERT(!is_hard_link(location,"detector_data_2"));
    CPPUNIT_ASSERT(!is_external_link(location,"detector_data_2"));

    link(target_field,location,"detector_data_3");

    h5::nxfield field_1 = as_field(root_group["links/detector_data_1"]);
    CPPUNIT_ASSERT(field_1.is_valid());
    CPPUNIT_ASSERT(field_1.size() == 1);
    CPPUNIT_ASSERT(field_1.type_id() == type_id_t::UINT16);
    
    h5::nxfield field_2 = as_field(root_group["links/detector_data_2"]);
    CPPUNIT_ASSERT(field_2.is_valid());
    CPPUNIT_ASSERT(field_2.size() == 1);
    CPPUNIT_ASSERT(field_2.type_id() == type_id_t::UINT16);
    
    h5::nxfield field_3 = root_group["links/detector_data_3"];
    CPPUNIT_ASSERT(field_3.is_valid());
    CPPUNIT_ASSERT(field_3.size() == 1);
    CPPUNIT_ASSERT(field_3.type_id() == type_id_t::UINT16);
}

//-----------------------------------------------------------------------------
void nxlink_test::test_field_external_link()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxfile link_file = h5::nxfile::create_file("nxlink_external.h5",true);
    
    h5::nxgroup root_group = link_file.root();

    nxpath p = nxpath::from_string("nxlink_target_test.h5:///entry/detector/data");
    link(p,root_group,"data_1");
    CPPUNIT_ASSERT(link_type(root_group,"data_1")==nxlink_type::EXTERNAL);
    CPPUNIT_ASSERT(!is_soft_link(root_group,"data_1"));
    CPPUNIT_ASSERT(!is_hard_link(root_group,"data_1"));
    CPPUNIT_ASSERT(is_external_link(root_group,"data_1"));

    link("nxlink_taret_test.h5:///entry/detector/data",root_group,"data_2");

    h5::nxfield field_1 = root_group["data_1"];
    CPPUNIT_ASSERT(field_1.is_valid());
    CPPUNIT_ASSERT(field_1.size() == 1);
    CPPUNIT_ASSERT(field_1.type_id() == type_id_t::UINT16);
    
    h5::nxfield field_2 = root_group["data_1"];
    CPPUNIT_ASSERT(field_2.is_valid());
    CPPUNIT_ASSERT(field_2.size() == 1);
    CPPUNIT_ASSERT(field_2.type_id() == type_id_t::UINT16);
}

//-----------------------------------------------------------------------------
void nxlink_test::test_group_internal_link()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup root_group = target_file.root();
    nxpath p = nxpath::from_string("/entry/detector");
    link(p,location,"detector_1");

    link("/entry/detector",location,"detector_2");
    CPPUNIT_ASSERT(link_type(location,"detector_2")==nxlink_type::SOFT);
    CPPUNIT_ASSERT(is_soft_link(location,"detector_2"));
    CPPUNIT_ASSERT(!is_hard_link(location,"detector_2"));
    CPPUNIT_ASSERT(!is_external_link(location,"detector_2"));

    link(target_group,location,"detector_3");
    
    string buffer;
    h5::nxgroup group_1 = root_group["links/detector_1"];
    CPPUNIT_ASSERT(group_1.is_valid());
    group_1.attributes["NX_class"].read(buffer);
    CPPUNIT_ASSERT(buffer == "NXdetector");
    
    h5::nxgroup group_2 = root_group["links/detector_2"];
    CPPUNIT_ASSERT(group_2.is_valid());
    group_2.attributes["NX_class"].read(buffer);
    CPPUNIT_ASSERT(buffer == "NXdetector");
    
    h5::nxgroup group_3 = root_group["links/detector_3"];
    CPPUNIT_ASSERT(group_3.is_valid());
    group_3.attributes["NX_class"].read(buffer);
    CPPUNIT_ASSERT(buffer == "NXdetector");
}

//-----------------------------------------------------------------------------
void nxlink_test::test_group_external_link()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfile link_file = h5::nxfile::create_file("nxlink_external.h5",true);
    
    h5::nxgroup root_group = link_file.root();

    nxpath p = nxpath::from_string("nxlink_target_test.h5:///entry/detector");
    link(p,root_group,"detector_1");
    CPPUNIT_ASSERT(link_type(root_group,"detector_1")==nxlink_type::EXTERNAL);
    CPPUNIT_ASSERT(is_external_link(root_group,"detector_1"));
    CPPUNIT_ASSERT(!is_hard_link(root_group,"detector_1"));
    CPPUNIT_ASSERT(!is_soft_link(root_group,"detector_1"));

    link("nxlink_taret_test.h5:///entry/detector",root_group,"detector_2");

    string buffer;
    h5::nxgroup group_1 = root_group["detector_1"];
    CPPUNIT_ASSERT(group_1.is_valid());
    group_1.attributes["NX_class"].read(buffer);
    CPPUNIT_ASSERT(buffer == "NXdetector");
    
    h5::nxgroup group_2 = root_group["detector_1"];
    CPPUNIT_ASSERT(group_2.is_valid());
    group_2.attributes["NX_class"].read(buffer);
    CPPUNIT_ASSERT(buffer == "NXdetector");
}

