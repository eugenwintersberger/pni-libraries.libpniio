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
//  Created on: Jun 28, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "get_object_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_object_test);

//-----------------------------------------------------------------------------
void get_object_test::setUp()
{
    file = h5::nxfile::create_file("get_object_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    h5::nxgroup tg = group.create_group("instrument","NXinstrument");
    tg.create_group("detector","NXdetector");
    tg.create_field<uint32>("data",shape_t{0,1024,1024});
    tg.create_group("source","NXsource");
    field = root.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void get_object_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_object_test::test_absolute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject root_group = root;
    nxpath p = nxpath::from_string("/group/instrument/detector");

    auto o= get_object(root_group,p);
    CPPUNIT_ASSERT(is_valid(get_object(root_group,p)));
    CPPUNIT_ASSERT(is_group(get_object(root_group,p)));
    CPPUNIT_ASSERT(get_name(get_object(root_group,p))=="detector");


    CPPUNIT_ASSERT(is_valid(get_object(root_group,p)));
    CPPUNIT_ASSERT(is_group(get_object(root_group,p)));
    CPPUNIT_ASSERT(get_name(get_object(root_group,p))=="detector");

    p = nxpath::from_string("/:NXentry/instrument/:NXdetector");
    CPPUNIT_ASSERT(is_valid(get_object(root_group,p)));
    CPPUNIT_ASSERT(is_group(get_object(root_group,p)));
    CPPUNIT_ASSERT(get_name(get_object(root_group,p))=="detector");

    p = nxpath::from_string("/:NXentry/instrument/:NXdetector@NX_class");
    CPPUNIT_ASSERT(get_name(get_object(root_group,p))=="NX_class");
    p = nxpath::from_string("/@NX_class");
    CPPUNIT_ASSERT(get_name(get_object(root_group,p))=="NX_class");
}

//-----------------------------------------------------------------------------
void get_object_test::test_relative()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject root_group = root;
    nxpath p = nxpath::from_string("../instrument/detector");
    CPPUNIT_ASSERT(!is_absolute(p));

    h5::nxobject ig = get_object(root_group,nxpath::from_string("group/instrument"));
    CPPUNIT_ASSERT(get_name(ig) == "instrument");
    h5::nxobject d  = get_object(ig,p);
    CPPUNIT_ASSERT(get_name(d) == "detector");

}

//----------------------------------------------------------------------------
void get_object_test::test_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath p = nxpath::from_string(":NXinstrument/:NXdetector/data");
    CPPUNIT_ASSERT_THROW(get_object(group,p),key_error);

    p = nxpath::from_string(":NXinstrument@hello");
    CPPUNIT_ASSERT_THROW(get_object(group,p),key_error);
}

