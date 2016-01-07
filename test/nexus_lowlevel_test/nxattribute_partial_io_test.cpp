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
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "test_types.hpp"
#include "nxattribute_test_fixture.hpp"


using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_partial_io_test_fixture : nxattribute_test_fixture
{
    nxattribute_partial_io_test_fixture():
        nxattribute_test_fixture("nxattribute_partial_io_test.nxs")
    {}
};


BOOST_FIXTURE_TEST_SUITE(nxattribute_partial_io_test,nxattribute_partial_io_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_selection,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto write_buffer = create_random_array<T>(default_shape);
        auto read_buffer  = create_array<T>(default_shape);

        //writing data to disk
        for(size_t i=0;i<default_shape[0];++i)
            for(size_t j=0;j<default_shape[1];++j)
                BOOST_CHECK_NO_THROW(attr(i,j).write(write_buffer(i,j)));

        for(size_t i=0;i<default_shape[0];++i)
            for(size_t j=0;j<default_shape[1];++j)
                BOOST_CHECK_NO_THROW(attr(i,j).read(read_buffer(i,j)));
        
        BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                      read_buffer.begin(),read_buffer.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_strip_selection,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        
        //writing data to disk
        auto read  = create_array<T>(shape_t{4});
        for(size_t i=0;i<default_shape[0];++i)
        {
            auto write = create_random_array<T>(shape_t{4});

            //write data
            BOOST_CHECK_NO_THROW(attr(i,slice(0,4)).write(write));
            //read back data
            BOOST_CHECK_NO_THROW(attr(i,slice(0,4)).read(read));

            BOOST_CHECK_EQUAL_COLLECTIONS(read.begin(),read.end(),
                                          write.begin(),write.end());
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_view_to_selection,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);

        //writing data to disk
        auto write = create_random_array<T>(default_shape);
        auto read  = create_array<T>(default_shape);

        slice s(0,4);
        for(size_t i=0;i<default_shape[0];++i)
        {
            //write data
            BOOST_CHECK_NO_THROW(attr(i,s).write(write(i,s)));
            BOOST_CHECK_NO_THROW(attr(i,s).read(read(i,s)));
        }

        BOOST_CHECK_EQUAL_COLLECTIONS(read.begin(),read.end(),
                                      write.begin(),write.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_and_selection,T,attribute_test_types)
    {
        //create attribute and selection
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto selection = attr(0,slice(0,4));

        BOOST_CHECK_EQUAL(attr.rank(),2);
        BOOST_CHECK_EQUAL(attr.size(),12);

        BOOST_CHECK_EQUAL(selection.rank(),1);
        BOOST_CHECK_EQUAL(selection.size(),4);

        auto write_full = create_random_array<T>(default_shape);
        BOOST_CHECK_NO_THROW(attr.write(write_full));

        auto read_selection = create_array<T>(selection.template shape<shape_t>());
        selection.read(read_selection);

        for(size_t i=0;i<default_shape[0];++i)
            BOOST_CHECK_EQUAL(read_selection(i),write_full(0,i));
    }

BOOST_AUTO_TEST_SUITE_END()

