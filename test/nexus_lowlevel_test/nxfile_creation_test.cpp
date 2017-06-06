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

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/exceptions.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

using namespace pni::core;
using namespace pni::io::nx;

namespace fs = boost::filesystem;

struct nxfile_creation_test_fixture
{
    h5::nxfile f;

    nxfile_creation_test_fixture():
        f()
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxfile_creation_test,nxfile_creation_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_simple)
    {
        BOOST_CHECK(!f.is_valid());

        string fname = "nxfile_creation_test_test_simple.nxs";
        fs::remove(fname);
        //initially create the file
        BOOST_CHECK_NO_THROW(f = h5::nxfile::create_file(fname));
        BOOST_CHECK(f.is_valid());
        BOOST_CHECK(!f.is_readonly());
        BOOST_CHECK_NO_THROW(f.close());
        BOOST_CHECK(!f.is_valid());

        //recreating the file should cause an error as the file already exists
        BOOST_CHECK_THROW(h5::nxfile::create_file(fname,false),
                          pni::io::object_error); //here we except an error
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_with_overwrite)
    {
        string fname = "nxfile_creation_test_test_with_overwrite.nxs";
        //initially create the file
        fs::remove(fname);
        BOOST_CHECK_NO_THROW(f = h5::nxfile::create_file(fname));
        BOOST_CHECK(f.is_valid());
        BOOST_CHECK(!f.is_readonly());
        BOOST_CHECK_NO_THROW(f.close());
        BOOST_CHECK(!f.is_valid());
        
        BOOST_CHECK_NO_THROW(f = h5::nxfile::create_file(fname,true));
        //should throw because the file is already open - cannot create a new one
        BOOST_CHECK_THROW(h5::nxfile::create_file(fname,true),
                          pni::io::object_error);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_with_split)
    {

        string fname = "nxfile_create_test_test_with_split.%05i.nxs";
        for(size_t i=0;i<10;i++)
        {
            boost::format fmt(fname.c_str());
            fmt%i;
            fs::remove(fmt.str());
        }

        BOOST_CHECK_NO_THROW(f= h5::nxfile::create_files(fname,2));
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

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_with_overwrite_with_split)
    {
        string fname = "nxfile_create_test_test_with_overwrite_with_split.%05i.nxs";

        for(size_t i=0;i<10;i++)
        {
            boost::format fmt(fname.c_str());
            fmt%i;
            fs::remove(fmt.str());
        }

        //wrap this stuff into a block so that all destructors are called at the 
        //end before we try to recreate the file
        {
            BOOST_CHECK_NO_THROW(f= h5::nxfile::create_files(fname,2));
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

        BOOST_CHECK_NO_THROW(f= h5::nxfile::create_files(fname,2,true));
    }

BOOST_AUTO_TEST_SUITE_END()
