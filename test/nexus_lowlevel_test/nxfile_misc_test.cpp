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

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include "nxfile_misc_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxfile_misc_test);

//------------------------------------------------------------------------------
void nxfile_misc_test::setUp() { }

//------------------------------------------------------------------------------
void nxfile_misc_test::tearDown() { }

//------------------------------------------------------------------------------
void nxfile_misc_test::test_is_valid()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxfile f;
    CPPUNIT_ASSERT(!f.is_valid());

    f = h5::nxfile::create_file(filename,true);
    CPPUNIT_ASSERT(f.is_valid());
    
}

//------------------------------------------------------------------------------
void nxfile_misc_test::test_readonly()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfile::create_file(filename,true);
    h5::nxfile f = h5::nxfile::open_file(filename);
    CPPUNIT_ASSERT(f.is_readonly());

    f.close();
    f = h5::nxfile::open_file(filename,false);
    CPPUNIT_ASSERT(!f.is_readonly());
}

//----------------------------------------------------------------------------
void nxfile_misc_test::test_root()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfile f = h5::nxfile::create_file(filename,true);
    h5::nxgroup r = f.root();
    CPPUNIT_ASSERT(r.name() == "/");
}

//----------------------------------------------------------------------------
void nxfile_misc_test::test_close()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    h5::nxfile f = h5::nxfile::create_file(filename,true);
    CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());
}

