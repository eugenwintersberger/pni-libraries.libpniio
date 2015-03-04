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
#include "nxgroup_misc_test.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

using pni::io::invalid_object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(nxgroup_misc_test);

//------------------------------------------------------------------------------
void nxgroup_misc_test::setUp()
{
	_fname = "nxgroup_misc_test.nxs";
    _f = h5::nxfile::create_file(_fname,true);
    _root = _f.root();
    _child = _root.create_group("entry","NXentry");
    _child2 = _child.create_group("instrument","NXinstrument");
}

//------------------------------------------------------------------------------
void nxgroup_misc_test::tearDown()
{
    _child.close();
    _child2.close();
    _root.close();
	_f.close();
}

//------------------------------------------------------------------------------
void nxgroup_misc_test::test_size()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(_root.size()==1);
    CPPUNIT_ASSERT(_child.size()==1);
    CPPUNIT_ASSERT(_child2.size()==0);
}

//------------------------------------------------------------------------------
void nxgroup_misc_test::test_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(_root.name()=="/");
    CPPUNIT_ASSERT(_child.name()=="entry");
}

//------------------------------------------------------------------------------
void nxgroup_misc_test::test_filename()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(_root.filename() == _filename);
    CPPUNIT_ASSERT(_child.filename() == _filename);
}

//------------------------------------------------------------------------------
void nxgroup_misc_test::test_parent()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(h5::nxgroup(_root.parent()).name()=="/");
    CPPUNIT_ASSERT(h5::nxgroup(_child.parent()).name()=="/");
    CPPUNIT_ASSERT(h5::nxgroup(_child2.parent()).name()=="entry");
}
