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

#include <vector>
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../uniform_distribution.hpp"
#include "nxattribute_test_fixture.hpp"
#include "test_types.hpp"


using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_view_io_test_fixture : nxattribute_test_fixture
{
    static const shape_t array_shape;

    nxattribute_view_io_test_fixture():
        nxattribute_test_fixture("nxattribute_view_io_test.nxs")
    {}
};

const shape_t nxattribute_view_io_test_fixture::array_shape = shape_t{10,20};

BOOST_FIXTURE_TEST_SUITE(nxattribute_view_io_test,nxattribute_view_io_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_rvalue_cont_view,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto data = create_random_array<T>(array_shape);

        //write data
        BOOST_CHECK_NO_THROW(attr.write(data(0,slice(0,12))));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(data(1,slice(0,12))));

        auto write_view = data(0,slice(0,12));
        auto read_view  = data(1,slice(0,12));

        BOOST_CHECK_EQUAL_COLLECTIONS(read_view.begin(),read_view.end(),
                                      write_view.begin(),write_view.end());
    }

    //----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_rvalue_discont_view,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto data = create_random_array<T>(array_shape);

        //write data
        BOOST_CHECK_NO_THROW(attr.write(data(slice(0,3),slice(0,4))));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(data(slice(3,6),slice(0,4))));

        auto write_view = data(slice(0,3),slice(0,4));
        auto read_view  = data(slice(3,6),slice(0,4));

        for(size_t i=0;i<default_shape[0];++i)
        {
            for(size_t j=0;j<default_shape[1];++j)
            {
                BOOST_CHECK_EQUAL(read_view(i,j),write_view(i,j));
            }
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_lvalue_discont_view,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto data = create_random_array<T>(array_shape);

        auto write = data(slice(0,3),slice(0,4));
        auto read  = data(slice(3,6),slice(0,4));

        //write data
        BOOST_CHECK_NO_THROW(attr.write(write));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(read));

        for(size_t i=0;i<default_shape[0];++i)
        {
            for(size_t j=0;j<default_shape[1];++j)
            {
                BOOST_CHECK_EQUAL(read(i,j),write(i,j));
            }
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_lvalue_cont_view,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto data = create_random_array<T>(array_shape);

        auto write = data(0,slice(0,12));
        auto read  = data(1,slice(0,12));

        //write data
        BOOST_CHECK_NO_THROW(attr.write(write));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(read));

        BOOST_CHECK_EQUAL_COLLECTIONS(read.begin(),read.end(),
                                      write.begin(),write.end());
    }


BOOST_AUTO_TEST_SUITE_END()

