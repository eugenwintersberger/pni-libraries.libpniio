/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *************************************************************************
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <pni/core/arrays.hpp>
#include <boost/current_function.hpp>
#include "H5FileTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5FileTest);


void H5FileTest::setUp(){
}

void H5FileTest::tearDown(){
}


//-----------------------------------------------------------------------------
void H5FileTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5File file;

    //should raise an exception because the file is not an HDF5 file
    CPPUNIT_ASSERT_THROW(H5File::open_file("H5FileTest.cpp",false),pni::io::nx::nxfile_error);
    CPPUNIT_ASSERT_THROW(H5File::open_file("H5FileTest.cpp",true),pni::io::nx::nxfile_error);
    //should throw an exception because the file does not exist.
    CPPUNIT_ASSERT_THROW(H5File::open_file("blablabla.h5",false),pni::io::nx::nxfile_error);
    CPPUNIT_ASSERT_THROW(H5File::open_file("blablabla.h5",true),pni::io::nx::nxfile_error);

    //create a file
    CPPUNIT_ASSERT_NO_THROW(file = H5File::create_file("H5FileTest.h5",true,0));
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT_NO_THROW(file.close());
    CPPUNIT_ASSERT(!file.is_valid());

    //open the file in read/write mode
    file = H5File::open_file("H5FileTest.h5",false);
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT(!file.is_readonly());
    file.close();
    //open in read only mode
    file = H5File::open_file("H5FileTest.h5");
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT(file.is_readonly());

    //use the move constructor
    H5File file2 = std::move(file);
    CPPUNIT_ASSERT(file2.is_valid());
    CPPUNIT_ASSERT(!file.is_valid());
    CPPUNIT_ASSERT_NO_THROW(file2.close());

}

//-----------------------------------------------------------------------------
void H5FileTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //can only test move assignment - copy assignment is not supported
    //for file
    H5File file1;
    CPPUNIT_ASSERT_NO_THROW(file1 = H5File::create_file("H5FileTest.h5",true,0));
    CPPUNIT_ASSERT(file1.is_valid());
    CPPUNIT_ASSERT(file1.path()=="H5FileTest.h5");
    CPPUNIT_ASSERT(file1.name()=="H5FileTest.h5");
    CPPUNIT_ASSERT(file1.base()=="");
    H5File file2;
    CPPUNIT_ASSERT(!file2.is_valid());

    CPPUNIT_ASSERT_NO_THROW(file2 = std::move(file1));
    CPPUNIT_ASSERT(file2.is_valid());
    CPPUNIT_ASSERT(!file1.is_valid());

}

//-----------------------------------------------------------------------------
void H5FileTest::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5File file = H5File::create_file("../H5FileTest.h5",true,0);

    CPPUNIT_ASSERT(file.path()=="../H5FileTest.h5");
    CPPUNIT_ASSERT(file.name()=="H5FileTest.h5");
    CPPUNIT_ASSERT(file.base()=="../");
}

