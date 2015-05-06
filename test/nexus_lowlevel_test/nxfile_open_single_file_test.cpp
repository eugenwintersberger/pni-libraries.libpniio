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

#include "nxfile_open_single_file_test.hpp"
#include <pni/io/exceptions.hpp>

using pni::io::object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(nxfile_open_single_file_test);

//------------------------------------------------------------------------------
void nxfile_open_single_file_test::setUp() 
{ 
    h5::nxfile::create_file(filename,true);
}

//------------------------------------------------------------------------------
void nxfile_open_single_file_test::tearDown() { }

//------------------------------------------------------------------------------
void nxfile_open_single_file_test::test_rw()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfile f;
    CPPUNIT_ASSERT_NO_THROW(f = h5::nxfile::open_file(filename,false));

    CPPUNIT_ASSERT_NO_THROW(f.root().create_group("hello"));

    //
    //This should throw - however, according to the HDF5 manual the library
    //manages this situation in some cases, in particular on UNIX file systems
    //
    CPPUNIT_ASSERT_NO_THROW(h5::nxfile::open_file(filename));
    CPPUNIT_ASSERT_NO_THROW(h5::nxfile::open_file(filename,false));
}

//------------------------------------------------------------------------------
void nxfile_open_single_file_test::test_ro()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    h5::nxfile f;
    CPPUNIT_ASSERT_NO_THROW(f=h5::nxfile::open_file(filename));

    h5::nxfile f2;
    CPPUNIT_ASSERT_NO_THROW(f2=h5::nxfile::open_file(filename));

    //should throw as the files are opened in read only mode
    CPPUNIT_ASSERT_THROW(f.root().create_group("test"),object_error);
}

//----------------------------------------------------------------------------
void nxfile_open_single_file_test::test_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(h5::nxfile::open_file("test.nxs"),object_error);
}

