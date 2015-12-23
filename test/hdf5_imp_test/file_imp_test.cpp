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
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>

using namespace pni::core;
using namespace pni::io::nx;

BOOST_AUTO_TEST_SUITE(file_imp_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_creation)
    {
        using pni::io::object_error;


        //should raise an exception because the file is not an HDF5 file
        BOOST_CHECK_THROW(h5::file_imp::open("hdf5_imp_test",false),file_error);
        BOOST_CHECK_THROW(h5::file_imp::open("hdf5_imp_test",true),file_error);
        //should throw an exception because the file does not exist.
        BOOST_CHECK_THROW(h5::file_imp::open("blablabla.h5",false),object_error);
        BOOST_CHECK_THROW(h5::file_imp::open("blablabla.h5",true),object_error);

        //create a file
        h5::file_imp file(h5::file_imp::create("file_imp_test.h5",true,0));
        BOOST_CHECK(file.is_valid());
        BOOST_CHECK_NO_THROW(file.close());
        BOOST_CHECK(!file.is_valid());

        //open the file in read/write mode
        file = h5::file_imp::open("file_imp_test.h5",false);
        BOOST_CHECK(file.is_valid());
        BOOST_CHECK(!file.is_readonly());
        BOOST_CHECK_NO_THROW(file.close());

        //open in read only mode
        file = h5::file_imp::open("file_imp_test.h5");
        BOOST_CHECK(file.is_valid());
        BOOST_CHECK(file.is_readonly());

        //use the move constructor
        h5::file_imp file2 = std::move(file);
        BOOST_CHECK(file2.is_valid());
        BOOST_CHECK(!file.is_valid());
        BOOST_CHECK_NO_THROW(file2.close());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        //can only test move assignment - copy assignment is not supported
        //for file
        h5::file_imp file1;
        BOOST_CHECK_NO_THROW(file1 = h5::file_imp::create("file_imp_test.h5",true,0));
        BOOST_CHECK(file1.is_valid());
        h5::file_imp file2;
        BOOST_CHECK(!file2.is_valid());

        BOOST_CHECK_NO_THROW(file2 = std::move(file1));
        BOOST_CHECK(file2.is_valid());
        BOOST_CHECK(!file1.is_valid());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_root)
    {
        h5::file_imp file = h5::file_imp::create("file_imp_test.h5",true);
        h5::group_imp root = file.root();
        BOOST_CHECK_EQUAL(root.name(), "/");
    }

BOOST_AUTO_TEST_SUITE_END()
