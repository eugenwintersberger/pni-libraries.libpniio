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

#include<cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include "nxlink_external_test.hpp"
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/algorithms.hpp>



CPPUNIT_TEST_SUITE_REGISTRATION(nxlink_external_test);

//------------------------------------------------------------------------------
void nxlink_external_test::setUp()
{
    link_file = h5::nxfile::create_file(link_file_name,true);
    location  = h5::nxgroup(link_file.root()).create_group("links");

    //create structure in the target file
    target_file = h5::nxfile::create_file(target_file_name,true);
    root_group = target_file.root();
    root_group.create_group("entry","NXentry");
    root_group.create_group("/entry/detector","NXdetector");
    h5::nxfield field = root_group.create_field<uint16>("/entry/detector/data");
    field.attributes.create<string>("units").write("au");
    field.close();
    root_group.close();
    target_file.close();
}

//------------------------------------------------------------------------------
void nxlink_external_test::tearDown()
{
    location.close();
	link_file.close();
}

//----------------------------------------------------------------------------
void nxlink_external_test::test_field_by_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link(target_file_name+"://entry/detector/data",
                            location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
}

//----------------------------------------------------------------------------
void nxlink_external_test::test_field_by_path()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath target = nxpath::from_string(target_file_name+
                     "://entry:NXentry/detector:NXdetector/data");
    CPPUNIT_ASSERT_NO_THROW(link(target,location,"link_field"));

    h5::nxfield field = location["link_field"];
    CPPUNIT_ASSERT(get_unit(field)=="au");
}

//----------------------------------------------------------------------------
void nxlink_external_test::test_group_by_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(link(target_file_name+"://entry/detector",
                                 location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
}

//----------------------------------------------------------------------------
void nxlink_external_test::test_group_by_path()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath p = nxpath::from_string(target_file_name+
               "://entry:NXentry/detector:NXdetector");
    CPPUNIT_ASSERT_NO_THROW(link(p,location,"link_group"));
    h5::nxgroup g = location["link_group"];
    CPPUNIT_ASSERT(get_class(g)=="NXdetector");
}

//----------------------------------------------------------------------------
void nxlink_external_test::test_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(link(target_file_name+"://:NXentry/detector/data",location,"link"),
                         value_error);
    CPPUNIT_ASSERT_THROW(link(nxpath::from_string(target_file_name+"://:NXentry/detector/data"),
                         location,"link"),value_error);

    CPPUNIT_ASSERT_THROW(link(target_file_name+"://entry/../detector/data",location,"link"),
                         value_error);
    CPPUNIT_ASSERT_THROW(link(target_file_name+"://../entry/../detector/data",location,"link"),
                         value_error);
}
