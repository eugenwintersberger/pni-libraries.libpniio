//
// Declaration of Nexus object template.
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
//  Created on: Aug 4, 2011
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

#include "nxgroup_creation_test.hpp"

using pni::io::invalid_object_error;
using pni::io::object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(nxgroup_creation_test);

//------------------------------------------------------------------------------
void nxgroup_creation_test::setUp()
{
	_fname = "nxgroup_creation_test.nxs";
    _f = h5::nxfile::create_file(_fname,true);
    _root = _f.root();
}

//------------------------------------------------------------------------------
void nxgroup_creation_test::tearDown()
{
    _root.close();
	_f.close();
}

//------------------------------------------------------------------------------
void nxgroup_creation_test::test_simple()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxgroup g;

    CPPUNIT_ASSERT_NO_THROW( g = _root.create_group("test"));
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.name() == "test");

    //throw an exception if the group already exists
    CPPUNIT_ASSERT_THROW(_root.create_group("test"),object_error);

    CPPUNIT_ASSERT_THROW(_root.create_group("test2/data"),object_error);

}

//------------------------------------------------------------------------------
void nxgroup_creation_test::test_with_class()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g;
    CPPUNIT_ASSERT_NO_THROW( g = _root.create_group("test","NXentry"));
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.name()=="test");
    CPPUNIT_ASSERT(get_class(g)=="NXentry");
   
    CPPUNIT_ASSERT_THROW(_root.create_group("test","NXinstrument"),object_error);
    CPPUNIT_ASSERT_THROW(_root.create_group("test2/data","NXdata"),object_error);
}

//------------------------------------------------------------------------------
void nxgroup_creation_test::test_copy_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g;
    g = _root.create_group("test");
    h5::nxgroup g2 = g;
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());

}

//------------------------------------------------------------------------------
void nxgroup_creation_test::test_move_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g;
    g = _root.create_group("test");
    h5::nxgroup g2 = std::move(g);
    CPPUNIT_ASSERT(!g.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());
}


