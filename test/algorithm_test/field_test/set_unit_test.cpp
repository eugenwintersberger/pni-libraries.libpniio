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

#include <pni/io/nx/algorithms/set_unit.hpp>
#include <pni/io/nx/algorithms/get_unit.hpp>
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "set_unit_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(set_unit_test);
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
void set_unit_test::setUp()
{
    file = h5::nxfile::create_file("is_valid.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    field = root.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void set_unit_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void set_unit_test::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    h5::nxobject object = group;
    CPPUNIT_ASSERT_THROW(set_unit(object,"m"),type_error);
}

//-----------------------------------------------------------------------------
void set_unit_test::test_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = field;
    CPPUNIT_ASSERT_NO_THROW(set_unit(object,"m"));
#ifdef CLANG_CXX
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-comparison"
#endif
    CPPUNIT_ASSERT_NO_THROW(get_unit(object)=="m");
#ifdef CLANG_CXX
#pragma GCC diagnostic pop
#endif

    CPPUNIT_ASSERT_NO_THROW(set_unit(field,"mm"));
#ifdef CLANG_CXX
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-comparison"
#endif
    CPPUNIT_ASSERT_NO_THROW(get_unit(field)=="mm");
#ifdef CLANG_CXX
#pragma GCC diagnostic pop
#endif

    CPPUNIT_ASSERT_THROW(set_unit(h5::nxfield(),"mm"),invalid_object_error);
    CPPUNIT_ASSERT_THROW(set_unit(h5::nxobject(h5::nxfield()),"mm"),
                         invalid_object_error);
}

//-----------------------------------------------------------------------------
void set_unit_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = group.attributes["NX_class"];
    CPPUNIT_ASSERT_THROW(set_unit(object,"m"),type_error);
   
}

