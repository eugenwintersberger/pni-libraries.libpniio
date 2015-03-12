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

#include<cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include "nxlink_internal_test.hpp"
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/algorithms.hpp>



CPPUNIT_TEST_SUITE_REGISTRATION(nxlink_internal_test);

//------------------------------------------------------------------------------
void nxlink_internal_test::setUp()
{
    target_file = h5::nxfile::create_file("nxlink_internal_test.nxs",true);
    h5::nxgroup root_group = target_file.root();
    location = root_group.create_group("links");

    root_group.create_group("entry","NXentry");
    target_group = root_group.create_group("/entry/detector","NXdetector");
    target_field = root_group.create_field<uint16>("/entry/detector/data");
    target_field.attributes.create<string>("units").write("au");
}

//------------------------------------------------------------------------------
void nxlink_internal_test::tearDown()
{
    target_field.close();
    target_group.close();
    root_group.close();
    location.close();
	target_file.close();
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_is_hard_link()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_hard_link(h5::nxgroup(target_file.root()),"entry"));
    CPPUNIT_ASSERT(is_hard_link(target_group,"data"));
}

//------------------------------------------------------------------------------
void nxlink_internal_test::test_field_by_instance()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link(target_field,location,"link_field"));
    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
    CPPUNIT_ASSERT(is_soft_link(location,"link_field"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_field_by_string_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link("/entry/detector/data",location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
    CPPUNIT_ASSERT(is_soft_link(location,"link_field"));

}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_field_by_string_relative()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link("../entry/detector/data",location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
    CPPUNIT_ASSERT(is_soft_link(location,"link_field"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_field_by_path_relative()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath target = nxpath::from_string("../entry:NXentry/detector:NXdetector/data");
    CPPUNIT_ASSERT_NO_THROW(link(target,location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
    CPPUNIT_ASSERT(is_soft_link(location,"link_field"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_field_by_path_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath target = nxpath::from_string("/entry:NXentry/detector:NXdetector/data");
    CPPUNIT_ASSERT_NO_THROW(link(target,location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
    CPPUNIT_ASSERT(is_soft_link(location,"link_field"));
}

//------------------------------------------------------------------------------
void nxlink_internal_test::test_group_by_instance()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_NO_THROW(link(target_group,location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
    CPPUNIT_ASSERT(is_soft_link(location,"link_group"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_group_by_string_relative()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link("../entry/detector",location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
    CPPUNIT_ASSERT(is_soft_link(location,"link_group"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_group_by_string_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT_NO_THROW(link("/entry/detector",location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
    CPPUNIT_ASSERT(is_soft_link(location,"link_group"));
}
//----------------------------------------------------------------------------
void nxlink_internal_test::test_group_by_path_relative()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("../entry:NXentry/detector:NXdetector");
    CPPUNIT_ASSERT_NO_THROW(link(p,location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
    CPPUNIT_ASSERT(is_soft_link(location,"link_group"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_group_by_path_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string("/entry:NXentry/detector:NXdetector");
    CPPUNIT_ASSERT_NO_THROW(link(p,location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
    CPPUNIT_ASSERT(is_soft_link(location,"link_group"));
}

//----------------------------------------------------------------------------
void nxlink_internal_test::test_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(link("/:NXentry/detector/data",location,"link"),
                         value_error);
    CPPUNIT_ASSERT_THROW(link(nxpath::from_string("/:NXentry/detector/data"),
                         location,"link"),value_error);

    CPPUNIT_ASSERT_THROW(link("/entry/../detector/data",location,"link"),
                         value_error);
}
