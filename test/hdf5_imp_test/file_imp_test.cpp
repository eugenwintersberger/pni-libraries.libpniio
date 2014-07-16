//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#include <boost/current_function.hpp>
#include <pni/io/exceptions.hpp>
#include "file_imp_test.hpp"
#include <pni/io/nx/h5/group_imp.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(file_imp_test);


//----------------------------------------------------------------------------
void file_imp_test::setUp() { }

//----------------------------------------------------------------------------
void file_imp_test::tearDown() { }

//-----------------------------------------------------------------------------
void file_imp_test::test_creation()
{
    using pni::io::object_error;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;


    //should raise an exception because the file is not an HDF5 file
    CPPUNIT_ASSERT_THROW(file_imp::open("hdf5_imp_test",false),type_error);
    CPPUNIT_ASSERT_THROW(file_imp::open("hdf5_imp_test",true),type_error);
    //should throw an exception because the file does not exist.
    CPPUNIT_ASSERT_THROW(file_imp::open("blablabla.h5",false),object_error);
    CPPUNIT_ASSERT_THROW(file_imp::open("blablabla.h5",true),object_error);

    //create a file
    file_imp file(file_imp::create("file_imp_test.h5",true,0));
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT_NO_THROW(file.close());
    CPPUNIT_ASSERT(!file.is_valid());

    //open the file in read/write mode
    file = file_imp::open("file_imp_test.h5",false);
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT(!file.is_readonly());
    CPPUNIT_ASSERT_NO_THROW(file.close());

    //open in read only mode
    file = file_imp::open("file_imp_test.h5");
    CPPUNIT_ASSERT(file.is_valid());
    CPPUNIT_ASSERT(file.is_readonly());

    //use the move constructor
    file_imp file2 = std::move(file);
    CPPUNIT_ASSERT(file2.is_valid());
    CPPUNIT_ASSERT(!file.is_valid());
    CPPUNIT_ASSERT_NO_THROW(file2.close());

}

//-----------------------------------------------------------------------------
void file_imp_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //can only test move assignment - copy assignment is not supported
    //for file
    file_imp file1;
    CPPUNIT_ASSERT_NO_THROW(file1 = file_imp::create("file_imp_test.h5",true,0));
    CPPUNIT_ASSERT(file1.is_valid());
    file_imp file2;
    CPPUNIT_ASSERT(!file2.is_valid());

    CPPUNIT_ASSERT_NO_THROW(file2 = std::move(file1));
    CPPUNIT_ASSERT(file2.is_valid());
    CPPUNIT_ASSERT(!file1.is_valid());

}

//----------------------------------------------------------------------------
void file_imp_test::test_root()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    file_imp file = file_imp::create("file_imp_test.h5",true);
    group_imp root = file.root();
    CPPUNIT_ASSERT(root.name() == "/");
}
