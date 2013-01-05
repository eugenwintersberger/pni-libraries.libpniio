/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"
#include "NXFileTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFileTest);

//------------------------------------------------------------------------------
void NXFileTest::setUp() { }

//------------------------------------------------------------------------------
void NXFileTest::tearDown() { }

//------------------------------------------------------------------------------
void NXFileTest::test_creation()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	NXFile f;

	//initially create the file
	CPPUNIT_ASSERT(!f.is_valid());
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
	CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(!f.is_readonly());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());

	//recreating the file should cause an error
	CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",false)
            ,pni::io::nx::NXFileError); //here we except an error

	//everything should work fine
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT_THROW(f =
            NXFile::create_file("NXFileTest.h5",true,0),pni::io::nx::NXFileError);
    f.flush();
    //should produce no exception as HDF5 allows multiple files to be open
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::open_file("NXFileTest.h5",true));
    CPPUNIT_ASSERT_NO_THROW(f = NXFile::open_file("NXFileTest.h5",true));
    //try now with readonly flag set
    CPPUNIT_ASSERT_NO_THROW(f = NXFile::open_file("NXFileTest.h5",false));

    //try now multiple calls to create
    //if overwrite is not set an exception should be thrown
	CPPUNIT_ASSERT_THROW(f = NXFile::create_file("NXFileTest.h5",false,0),
            pni::io::nx::NXFileError);
    CPPUNIT_ASSERT_THROW(f = NXFile::create_file("NXFileTest.h5",true,0),
            pni::io::nx::NXFileError);

	f.close();

    //check copy ans move constructor
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT(f.is_valid());
    NXFile f2(f);
    CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(f2.is_valid());

    //check move construction
    NXFile f3 = std::move(f2);
    CPPUNIT_ASSERT(f3.is_valid());
    CPPUNIT_ASSERT(!f2.is_valid());
    CPPUNIT_ASSERT(f.is_valid());

}

//------------------------------------------------------------------------------
void NXFileTest::test_open()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	NXFile f;

    CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT_NO_THROW(f.close());

	CPPUNIT_ASSERT_NO_THROW(f = NXFile::open_file("NXFileTest.h5",true));
    CPPUNIT_ASSERT(f.is_readonly());
	//here we should get exceptions because the file is already open
	CPPUNIT_ASSERT_NO_THROW(NXFile::open_file("NXFileTest.h5",true));

    //here we should  get an exception - the file is already open
	CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",true,0),
            pni::io::nx::NXFileError);

	CPPUNIT_ASSERT_NO_THROW(f.close());

	//try to open a file which does not exist
	CPPUNIT_ASSERT_THROW(NXFile::open_file("blabla.h5",true),pni::io::nx::NXFileError);

}

//-----------------------------------------------------------------------------
void NXFileTest::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    NXFile f;

    CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT(f.path()=="NXFileTest.h5");
    CPPUNIT_ASSERT(f.name()=="NXFileTest.h5");
    CPPUNIT_ASSERT(f.base()=="");

}


//-----------------------------------------------------------------------------
void NXFileTest::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    NXFile f = NXFile::create_file("NXFileTest.h5",true,0);
    f.create_group("dir1");
    f.create_group("dir2");
    f.create_group("dir3");

#ifdef NOFOREACH
    for(auto iter = f.begin(); iter!=f.end();iter++){
        auto &g = *iter;
#else
    for(auto &g: f){
#endif
        std::cout<<g.path()<<std::endl;
    }

    f.close();

}
