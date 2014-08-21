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
//  Created on: Aug 21, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>
#include <pni/io/exceptions.hpp>

#include "get_filename_test.hpp"

using pni::io::invalid_object_error;
using pni::io::io_error;

CPPUNIT_TEST_SUITE_REGISTRATION(get_filename_test);

//-----------------------------------------------------------------------------
void get_filename_test::setUp()
{
    file = h5::nxfile::create_file(filename,true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
    attribute = group.attributes["NX_class"];
}

//-----------------------------------------------------------------------------
void get_filename_test::tearDown() 
{ 
    attribute.close();
    field.close();
    group.close();
    root.close();
    file.close();
}


//----------------------------------------------------------------------------
void get_filename_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_filename(root)  == filename);
    CPPUNIT_ASSERT(get_filename(group) == filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxgroup()),invalid_object_error);
}

//----------------------------------------------------------------------------
void get_filename_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_filename(field)== filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxfield()),invalid_object_error);
}

//----------------------------------------------------------------------------
void get_filename_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_filename(attribute) == filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxattribute()),invalid_object_error);
}

//-----------------------------------------------------------------------------
void get_filename_test::test_nxobject_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = group;
    CPPUNIT_ASSERT(get_filename(object) == filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxobject(h5::nxgroup())),
                         invalid_object_error);
}

//-----------------------------------------------------------------------------
void get_filename_test::test_nxobject_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = field;
    CPPUNIT_ASSERT(get_filename(object)==filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxobject(h5::nxfield())),
                         invalid_object_error);
}

//-----------------------------------------------------------------------------
void get_filename_test::test_nxobject_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject object = attribute;
    CPPUNIT_ASSERT(get_filename(object) == filename);
    CPPUNIT_ASSERT_THROW(get_filename(h5::nxobject(h5::nxattribute())),
                         invalid_object_error);
   
}


