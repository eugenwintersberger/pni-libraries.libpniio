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

#include "get_parent_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_parent_test);

//-----------------------------------------------------------------------------
void get_parent_test::setUp()
{
    file = h5::nxfile::create_file("get_parent_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void get_parent_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_parent_test::test_nxobject_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = group["instrument"];
    CPPUNIT_ASSERT(is_valid(get_parent(object)));
    CPPUNIT_ASSERT(get_name(get_parent(object)) == "group");
    CPPUNIT_ASSERT(get_name(get_parent(h5::nxobject(group))) == "/");
    
    CPPUNIT_ASSERT(get_name(get_parent(get_parent(h5::nxobject(group))))=="/");
}

//-----------------------------------------------------------------------------
void get_parent_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup object = group["instrument"];
    CPPUNIT_ASSERT(is_valid(get_parent(object)));
    CPPUNIT_ASSERT(get_name(get_parent(object)) == "group");
    CPPUNIT_ASSERT(get_name(get_parent(group)) == "/");
    
    CPPUNIT_ASSERT(get_name(get_parent(get_parent(group)))=="/");
}

//-----------------------------------------------------------------------------
void get_parent_test::test_nxobject_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = field;

    CPPUNIT_ASSERT(get_name(get_parent(object)) == "/");

}

//----------------------------------------------------------------------------
void get_parent_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_name(get_parent(field))=="/");
}

//-----------------------------------------------------------------------------
void get_parent_test::test_nxobject_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject a(group.attr("NX_class"));

    auto p = get_parent(a);
    CPPUNIT_ASSERT(is_group(p));
    CPPUNIT_ASSERT(is_valid(p));
    CPPUNIT_ASSERT(get_name(p)=="group");
}

//----------------------------------------------------------------------------
void get_parent_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxattribute a = group.attr("NX_class");

    h5::nxgroup p = get_parent(a);

    CPPUNIT_ASSERT(p.name() == "group");

    p = get_parent(root);
    CPPUNIT_ASSERT(p.name() == "/");
}
