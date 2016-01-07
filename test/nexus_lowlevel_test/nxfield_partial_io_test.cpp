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

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <vector>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../uniform_distribution.hpp"
#include "test_types.hpp"
#include "nxfield_test_fixture.hpp"


using namespace pni::core;
using namespace pni::io::nx;

struct nxfield_partial_io_fixture : nxfield_test_fixture
{
    nxfield_partial_io_fixture():
        nxfield_test_fixture("nxfield_partial_io_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxfield_partial_io_test,nxfield_partial_io_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_selection,T,field_test_types)
    {
        auto field = create_field<T>("data",default_shape);
        auto buffer =  create_random_buffer<T>(default_size);

        //writing data to disk
        size_t index = 0;
        for(size_t i=0;i<default_shape[0];++i)
        {
            for(size_t j=0;j<default_shape[1];++j)
            {
                BOOST_CHECK_NO_THROW(field(i,j).write(buffer[index++]));
            }
        }

        index = 0;
        T read;
        for(size_t i=0;i<default_shape[0];++i)
        {
            for(size_t j=0;j<default_shape[1];++j)
            {
                BOOST_CHECK_NO_THROW(field(i,j).read(read));
                BOOST_CHECK_EQUAL(read,buffer[index++]);
            }
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_strip_selection,T,field_test_types)
    {
        auto field = create_field<T>("data",default_shape);

        //writing data to disk
        shape_t slice_shape{4};
        auto read_buffer  = create_array<T>(slice_shape);

        for(size_t i=0;i<default_shape[0];++i)
        {
            auto write_buffer = create_random_array<T>(slice_shape);

            //write data
            BOOST_CHECK_NO_THROW(field(i,slice(0,4)).write(write_buffer));
            //read back data
            BOOST_CHECK_NO_THROW(field(i,slice(0,4)).read(read_buffer));

            BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                          read_buffer.begin(),read_buffer.end());
        }

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_view_to_selection,T,field_test_types)
    {
        auto field = create_field<T>("data",default_shape);
        //writing data to disk
        auto write = create_random_array<T>(default_shape);
        auto read  = create_array<T>(default_shape);

        slice s(0,4);
        for(size_t i=0;i<default_shape[0];++i)
        {
            //write data
            field(i,s).write(write(i,s));
            //read data
            field(i,s).read(read(i,s));
        }
       
        BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                      read.begin(),read.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_and_selection,T,field_test_types)
    {
        auto field = create_field<T>("data",default_shape);
        //create the selection
        auto selection = field(0,slice(0,4));

        BOOST_CHECK_EQUAL(field.rank() , 2);
        BOOST_CHECK_EQUAL(field.size() , 12);

        BOOST_CHECK_EQUAL(selection.rank() , 1);
        BOOST_CHECK_EQUAL(selection.size() , 4);

        auto write_full = create_random_array<T>(default_shape);
        field.write(write_full);

        auto read_selection = create_array<T>(selection.template shape<shape_t>());
        selection.read(read_selection);

        for(size_t i=0;i<default_shape[0];++i)
            BOOST_CHECK_EQUAL(read_selection(i),write_full(0,i));
    }


BOOST_AUTO_TEST_SUITE_END()

