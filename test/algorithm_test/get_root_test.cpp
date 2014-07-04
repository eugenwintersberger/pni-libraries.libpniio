//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

#include "get_root_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_root_test);

//-----------------------------------------------------------------------------
void get_root_test::setUp()
{
    file = h5::nxfile::create_file("get_root_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = group.create_field<uint32>("data");

}

//-----------------------------------------------------------------------------
void get_root_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_root_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxgroup g = as_group(get_child(group,"instrument",""));
    CPPUNIT_ASSERT(get_name(get_root(group))=="/");

    CPPUNIT_ASSERT(get_name(get_root(root))=="/");

    CPPUNIT_ASSERT(get_name(get_root(h5::nxobject(group)))=="/");
    CPPUNIT_ASSERT(get_name(get_root(h5::nxobject(root)))=="/");

}

//-----------------------------------------------------------------------------
void get_root_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_name(get_root(field)) == "/");
    CPPUNIT_ASSERT(get_name(get_root(h5::nxobject(field))) == "/");

}

//-----------------------------------------------------------------------------
void get_root_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    h5::nxattribute a = group.attr("NX_class");
    
    CPPUNIT_ASSERT(get_name(get_root(a))=="/");
    CPPUNIT_ASSERT(get_name(get_root(h5::nxobject(a)))=="/");
}

