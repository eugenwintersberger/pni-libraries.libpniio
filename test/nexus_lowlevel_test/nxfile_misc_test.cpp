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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

struct nxfile_misc_test_fixture
{
    string filename;
    
    nxfile_misc_test_fixture():
        filename("nxfile_misc_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxfile_misc_test,nxfile_misc_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_is_valid)
    {
        h5::nxfile f;
        BOOST_CHECK(!f.is_valid());

        f = h5::nxfile::create_file(filename,true);
        BOOST_CHECK(f.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_readonly)
    {
        h5::nxfile::create_file(filename,true);
        h5::nxfile f = h5::nxfile::open_file(filename);
        BOOST_CHECK(f.is_readonly());

        f.close();
        f = h5::nxfile::open_file(filename,false);
        BOOST_CHECK(!f.is_readonly());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_root)
    {
        h5::nxfile f = h5::nxfile::create_file(filename,true);
        h5::nxgroup r = f.root();
        BOOST_CHECK(r.name() == "/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_close)
    {
        h5::nxfile f = h5::nxfile::create_file(filename,true);
        BOOST_CHECK(f.is_valid());
        BOOST_CHECK_NO_THROW(f.close());
        BOOST_CHECK(!f.is_valid());
    }

BOOST_AUTO_TEST_SUITE_END()

