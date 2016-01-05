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

#include <boost/test/unit_test.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;

struct nxfile_open_single_file_test_fixture
{
    string filename;

    nxfile_open_single_file_test_fixture():
        filename("nxfile_open_test.nxs")
    {
        h5::nxfile::create_file(filename,true); 
    }
};

BOOST_FIXTURE_TEST_SUITE(nxfile_open_single_file_test,
                         nxfile_open_single_file_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rw)
    {
        h5::nxfile f;
        BOOST_CHECK_NO_THROW(f = h5::nxfile::open_file(filename,false));
        BOOST_CHECK_NO_THROW(f.root().create_group("hello"));

        //
        //This should throw - however, according to the HDF5 manual the library
        //manages this situation in some cases, in particular on UNIX file systems
        //
        BOOST_CHECK_NO_THROW(h5::nxfile::open_file(filename));
        BOOST_CHECK_NO_THROW(h5::nxfile::open_file(filename,false));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_ro)
    {
        h5::nxfile f;
        BOOST_CHECK_NO_THROW(f=h5::nxfile::open_file(filename));

        h5::nxfile f2;
        BOOST_CHECK_NO_THROW(f2=h5::nxfile::open_file(filename));

        //should throw as the files are opened in read only mode
        BOOST_CHECK_THROW(f.root().create_group("test"),object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_error)
    {
        BOOST_CHECK_THROW(h5::nxfile::open_file("test.nxs"),object_error);
    }

BOOST_AUTO_TEST_SUITE_END()

