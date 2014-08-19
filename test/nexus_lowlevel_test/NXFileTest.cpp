//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
#include "NXFileTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFileTest);

//------------------------------------------------------------------------------
void NXFileTest::setUp() { }

//------------------------------------------------------------------------------
void NXFileTest::tearDown() { }

//------------------------------------------------------------------------------
void NXFileTest::test_creation()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxfile f;

	//initially create the file
	CPPUNIT_ASSERT(!f.is_valid());
	CPPUNIT_ASSERT_NO_THROW(f = nxfile::create_file("NXFileTest.h5",true,0));
	CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(!f.is_readonly());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());

	//recreating the file should cause an error
	CPPUNIT_ASSERT_THROW(nxfile::create_file("NXFileTest.h5",false)
            ,pni::io::object_error); //here we except an error

	//everything should work fine
	CPPUNIT_ASSERT_NO_THROW(f = nxfile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT_THROW(f =
            nxfile::create_file("NXFileTest.h5",true,0),pni::io::object_error);
    f.flush();
    //should produce no exception as HDF5 allows multiple files to be open
	CPPUNIT_ASSERT_NO_THROW(f = nxfile::open_file("NXFileTest.h5",true));
    CPPUNIT_ASSERT_NO_THROW(f = nxfile::open_file("NXFileTest.h5",true));
    //try now with readonly flag set
    CPPUNIT_ASSERT_NO_THROW(f = nxfile::open_file("NXFileTest.h5",false));

    //try now multiple calls to create
    //if overwrite is not set an exception should be thrown
	CPPUNIT_ASSERT_THROW(f = nxfile::create_file("NXFileTest.h5",false,0),
            pni::io::object_error);
    CPPUNIT_ASSERT_THROW(f = nxfile::create_file("NXFileTest.h5",true,0),
            pni::io::object_error);

	f.close();

    //check copy ans move constructor
	CPPUNIT_ASSERT_NO_THROW(f = nxfile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT(f.is_valid());
    nxfile f2(f);
    CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(f2.is_valid());

    //check move construction
    nxfile f3 = std::move(f2);
    CPPUNIT_ASSERT(f3.is_valid());
    CPPUNIT_ASSERT(!f2.is_valid());
    CPPUNIT_ASSERT(f.is_valid());

}

//------------------------------------------------------------------------------
void NXFileTest::test_open()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxfile f;

    CPPUNIT_ASSERT_NO_THROW(f = nxfile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT_NO_THROW(f.close());

	CPPUNIT_ASSERT_NO_THROW(f = nxfile::open_file("NXFileTest.h5",true));
    CPPUNIT_ASSERT(f.is_readonly());
	//here we should get exceptions because the file is already open
	CPPUNIT_ASSERT_NO_THROW(nxfile::open_file("NXFileTest.h5",true));

    //here we should  get an exception - the file is already open
	CPPUNIT_ASSERT_THROW(nxfile::create_file("NXFileTest.h5",true,0),
            pni::io::object_error);

	CPPUNIT_ASSERT_NO_THROW(f.close());

	//try to open a file which does not exist
	CPPUNIT_ASSERT_THROW(nxfile::open_file("blabla.h5",true),pni::io::object_error);

}

