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
#include "nxgroup_access_test.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

using pni::io::invalid_object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(nxgroup_access_test);

//------------------------------------------------------------------------------
void nxgroup_access_test::setUp()
{
	_fname = "nxgroup_access_test.nxs";
    _f = h5::nxfile::create_file(_fname,true);
    _root = _f.root();
    _child = _root.create_group("entry","NXentry");
}

//------------------------------------------------------------------------------
void nxgroup_access_test::tearDown()
{
    _child.close();
    _root.close();
	_f.close();
}

//------------------------------------------------------------------------------
void nxgroup_access_test::test_operator_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(_root.size()==1);

    h5::nxgroup g = _root[0];
    CPPUNIT_ASSERT(g.name()=="entry");
    
    CPPUNIT_ASSERT_THROW(_root[1],index_error);
}

//------------------------------------------------------------------------------
void nxgroup_access_test::test_operator_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(_root.size()==1);

    h5::nxgroup g = _root["entry"];
    CPPUNIT_ASSERT(g.name()=="entry");
    
    CPPUNIT_ASSERT_THROW(_root["nothing"],key_error);
}

//------------------------------------------------------------------------------
void nxgroup_access_test::test_at_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g = _root.at(0);
    CPPUNIT_ASSERT(g.name()=="entry");
    
    CPPUNIT_ASSERT_THROW(_root.at(1),index_error);
}

//------------------------------------------------------------------------------
void nxgroup_access_test::test_at_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g = _root.at("entry");
    CPPUNIT_ASSERT(g.name()=="entry");
    
    CPPUNIT_ASSERT_THROW(_root.at("nothing"),key_error);
}
