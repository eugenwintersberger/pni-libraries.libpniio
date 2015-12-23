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
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <list>
#include <boost/test/unit_test.hpp>
#include <pni/io/exceptions.hpp>

#include <pni/io/nx/h5/h5dataspace.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;


BOOST_AUTO_TEST_SUITE(h5dataspace_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default_construction)
    {
        h5dataspace space;
        BOOST_CHECK_EQUAL(space.rank(),1);
        BOOST_CHECK_EQUAL(space.size(),1);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_object_construction)
    {
        hsize_t dims[3] = {10,20,3};
        h5dataspace space1(object_imp(H5Screate_simple(3,dims,dims)));
        BOOST_CHECK_EQUAL(space1.rank(),3);
        BOOST_CHECK_EQUAL(space1.size(),600);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_move_construction)
    {
        h5dataspace s1{{10,3}};
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s1.size(),30);
        BOOST_CHECK_EQUAL(s1.rank(),2);

        h5dataspace s2(std::move(s1));
        BOOST_CHECK(s2.is_valid());
        BOOST_CHECK(!s1.is_valid());
        BOOST_CHECK_EQUAL(s2.rank(),2);
        BOOST_CHECK_EQUAL(s2.size(),30);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_copy_construction)
    {
        h5dataspace s1{{10,3}};
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s1.size(),30);
        BOOST_CHECK_EQUAL(s1.rank(),2);

        h5dataspace s2(s1);
        BOOST_CHECK(s2.is_valid());
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s2.rank(),2);
        BOOST_CHECK_EQUAL(s2.size(),30);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_move_assignment)
    {
        h5dataspace s1{{10,3}};
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s1.size() , 30);
        BOOST_CHECK_EQUAL(s1.rank() , 2);

        h5dataspace s2;
        s2 = std::move(s1);
        BOOST_CHECK(s2.is_valid());
        BOOST_CHECK(!s1.is_valid());
        BOOST_CHECK_EQUAL(s2.rank() , 2);
        BOOST_CHECK_EQUAL(s2.size() , 30);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_copy_assignment)
    {
        h5dataspace s1{{10,3}};
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s1.size() , 30);
        BOOST_CHECK_EQUAL(s1.rank() , 2);

        h5dataspace s2;
        s2 = s1;
        BOOST_CHECK(s2.is_valid());
        BOOST_CHECK(s1.is_valid());
        BOOST_CHECK_EQUAL(s2.rank() , 2);
        BOOST_CHECK_EQUAL(s2.size() , 30);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_container_construction)
    {
        typedef type_imp::index_vector_type list_type;
        
        list_type cdims={10,4,3};

        h5dataspace s1(cdims);
        BOOST_CHECK_EQUAL(s1.rank(),3);
        BOOST_CHECK_EQUAL(s1.size(),120);

        h5dataspace s2{list_type{100,40,30}};
        BOOST_CHECK_EQUAL(s2.rank(),3);
        BOOST_CHECK_EQUAL(s2.size(),100*40*30);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_current_iterator)
    {
        typedef type_imp::index_vector_type list_type;
        list_type shape{20,40,10};

        h5dataspace space(shape);
        
        auto liter = shape.begin();
        auto siter = space.shape().begin();
        for(;siter!=space.shape().end();++siter,++liter)
            BOOST_CHECK_EQUAL(*siter,*liter);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_grow)
    {
        h5dataspace space{{10,20}};

        BOOST_CHECK_NO_THROW(space.grow(0));
        BOOST_CHECK_EQUAL(space.shape()[0],11);
        BOOST_CHECK_NO_THROW(space.grow(0,4));
        BOOST_CHECK_EQUAL(space.shape()[0],15);
        BOOST_CHECK_NO_THROW(space.grow(1,2));
        BOOST_CHECK_EQUAL(space.shape()[1],22);

        BOOST_CHECK_THROW(space.grow(10),index_error);
    }

BOOST_AUTO_TEST_SUITE_END()
