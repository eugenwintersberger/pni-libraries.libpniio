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
//  Created on: Jul 31, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include <pni/io/nx/algorithms/get_attribute.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <pni/io/exceptions.hpp>

#include <pni/io/nx/algorithms.hpp>

#include "get_attributes_test.hpp"

using pni::io::object_error;
using pni::io::invalid_object_error;


CPPUNIT_TEST_SUITE_REGISTRATION(get_attributes_test);

//-----------------------------------------------------------------------------
void get_attributes_test::setUp()
{
    file = h5::nxfile::create_file("get_attributes_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = root.create_field<uint32>("data");
    field.attributes.create<string>("units").write("mm");
}

//-----------------------------------------------------------------------------
void get_attributes_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_attributes_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = group;
    auto a = get_attributes<container_type>(object);
    CPPUNIT_ASSERT(a.size()==1);
    CPPUNIT_ASSERT(get_name(a.front())=="NX_class");

    a = get_attributes<container_type>(file.root());
    CPPUNIT_ASSERT(a.size()==6);
}

//-----------------------------------------------------------------------------
void get_attributes_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_type object = field;
    
    auto a = get_attributes<container_type>(object);
    CPPUNIT_ASSERT(a.size()==1);
    CPPUNIT_ASSERT(get_name(a.front())=="units");
}

//-----------------------------------------------------------------------------
void get_attributes_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    auto a = object_type(group.attributes["NX_class"]);
    CPPUNIT_ASSERT_THROW(get_attributes<container_type>(a),type_error);
}


