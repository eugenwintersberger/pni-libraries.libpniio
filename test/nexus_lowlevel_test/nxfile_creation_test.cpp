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
#include "nxfile_creation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxfile_creation_test);

//------------------------------------------------------------------------------
void nxfile_creation_test::setUp() { }

//------------------------------------------------------------------------------
void nxfile_creation_test::tearDown() { }

//------------------------------------------------------------------------------
void nxfile_creation_test::test_simple()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!f.is_valid());

    string fname = "nxfile_creation_test_test_simple.nxs";
	//initially create the file
	CPPUNIT_ASSERT_NO_THROW(f = h5::nxfile::create_file(fname));
	CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(!f.is_readonly());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());

	//recreating the file should cause an error as the file already exists
	CPPUNIT_ASSERT_THROW(h5::nxfile::create_file(fname,false)
            ,pni::io::object_error); //here we except an error

    //opening the file read only - works  
    //CPPUNIT_ASSERT_THROW(h5::nxfile::open_file(fname),object_error);
}

//------------------------------------------------------------------------------
void nxfile_creation_test::test_with_overwrite()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    string fname = "nxfile_creation_test_test_with_overwrite.nxs";
	//initially create the file
	CPPUNIT_ASSERT_NO_THROW(f = h5::nxfile::create_file(fname));
	CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(!f.is_readonly());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());
	
    CPPUNIT_ASSERT_NO_THROW(f = h5::nxfile::create_file(fname,true));
    //should throw because the file is already open - cannot create a new one
    CPPUNIT_ASSERT_THROW(h5::nxfile::create_file(fname,true),object_error);

}

//----------------------------------------------------------------------------
void nxfile_creation_test::test_with_split()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    string fname = "nxfile_create_test_test_with_split.%05i.nxs";
    CPPUNIT_ASSERT_NO_THROW(f= h5::nxfile::create_files(fname,2));
    h5::nxgroup root = f.root();

    auto data = dynamic_array<float64>::create(shape_t{100000});
    h5::nxfield field = root.create_field<float64>("data",{0,100000});

    for(size_t i=0;i<10;++i)
    {
        std::fill(data.begin(),data.end(),float64(i));
        field.grow(0);
        field(i,slice(0,100000)).write(data);
    }
}

//----------------------------------------------------------------------------
void nxfile_creation_test::test_with_overwrite_with_split()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string fname = "nxfile_create_test_test_with_overwrite_with_split.%05i.nxs";

    //wrap this stuff into a block so that all destructors are called at the 
    //end before we try to recreate the file
    {
        CPPUNIT_ASSERT_NO_THROW(f= h5::nxfile::create_files(fname,2));
        h5::nxgroup root = f.root();

        auto data = dynamic_array<float64>::create(shape_t{100000});
        h5::nxfield field = root.create_field<float64>("data",{0,100000});

        for(size_t i=0;i<10;++i)
        {
            std::fill(data.begin(),data.end(),float64(i));
            field.grow(0);
            field(i,slice(0,100000)).write(data);
        }
    }
    f.close();

    CPPUNIT_ASSERT_NO_THROW(f= h5::nxfile::create_files(fname,2,true));
}

