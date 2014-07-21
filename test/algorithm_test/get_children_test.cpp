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
//  Created on: Jul 4, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_children_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_children_test);

//-----------------------------------------------------------------------------
void get_children_test::setUp()
{
    file = h5::nxfile::create_file("get_children_test.nx",true,0);
    root = file.root();
    group = root.create_group("scan_1","NXentry");
    group.create_group("beamline","NXinstrument");
    group.create_field<string>("date");
    group.create_field<string>("experiment_id");
    group.create_group("data","NXdata");
    group.create_group("control","NXmonitor");
    field = root.create_field<uint32>("data");
    attribute = group.attributes["NX_class"];
}

//-----------------------------------------------------------------------------
void get_children_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//----------------------------------------------------------------------------
void get_children_test::test_from_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    container_type c;
    CPPUNIT_ASSERT_NO_THROW(get_children(group,c));

    CPPUNIT_ASSERT(c.size() == 5);
    for(auto child: c)
        CPPUNIT_ASSERT((get_name(child) == "beamline") || 
                       (get_name(child) == "date")     ||
                       (get_name(child) == "experiment_id") || 
                       (get_name(child) == "data") ||
                       (get_name(child) == "control"));

}

//----------------------------------------------------------------------------
void get_children_test::test_from_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    container_type c;
    h5::nxobject g = group;

    CPPUNIT_ASSERT_NO_THROW(get_children(g,c));
    
    CPPUNIT_ASSERT(c.size() == 5);
    for(auto child: c)
        CPPUNIT_ASSERT((get_name(child) == "beamline") || 
                       (get_name(child) == "date")     ||
                       (get_name(child) == "experiment_id") || 
                       (get_name(child) == "data") ||
                       (get_name(child) == "control"));

    g = h5::nxobject(field);
    CPPUNIT_ASSERT_THROW(get_children(g,c),type_error);
    g = h5::nxobject(attribute);
    CPPUNIT_ASSERT_THROW(get_children(g,c),type_error);
}

