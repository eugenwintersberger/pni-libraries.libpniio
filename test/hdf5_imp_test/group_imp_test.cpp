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
#include <vector>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include "h5_imp_test_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct group_imp_test_fixture
{
    h5::file_imp file;
    h5::group_imp root_group;

    group_imp_test_fixture():
        file(h5::file_imp::create("group_imp_test.h5",true,0)),
        root_group(file.root())
    {}

    ~group_imp_test_fixture()
    {
        file.close();
        root_group.close();
    }

};

BOOST_FIXTURE_TEST_SUITE(group_imp_test,group_imp_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_creation)
    {
        h5::group_imp g; //default constructor
        BOOST_CHECK(!g.is_valid());

        //create directly using the constructor
        h5::group_imp g1(root_group,"group1");
        BOOST_CHECK(g1.is_valid());
        BOOST_CHECK_EQUAL(g1.name(),"group1");
        BOOST_CHECK_EQUAL(g1.filename(),"group_imp_test.h5");

        //using the copy constructor
        h5::group_imp g2 = g1;
        BOOST_CHECK(g1.is_valid());
        BOOST_CHECK(g2.is_valid());

        //using the move constructor
        h5::group_imp g3 = std::move(g2);
        BOOST_CHECK(g3.is_valid());
        BOOST_CHECK(!g2.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        h5::group_imp g(root_group,"group1");
        h5::group_imp g1,g2;
        
        //test copy assignment
        BOOST_CHECK_NO_THROW(g1 = g);
        BOOST_CHECK(g1.is_valid());
        BOOST_CHECK(g.is_valid());

        //test move assignment
        BOOST_CHECK_NO_THROW(g2 = std::move(g));
        BOOST_CHECK(g2.is_valid());
        BOOST_CHECK(!g.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_open_by_name)
    {
        h5::group_imp g(root_group,"test");
        h5::group_imp det;

        BOOST_CHECK_NO_THROW(det = h5::group_imp(root_group.at("test")));
        BOOST_CHECK(det.is_valid());
        BOOST_CHECK_EQUAL(det.name(),"test");

        BOOST_CHECK_THROW(root_group.at("bla"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_open_by_index)
    {
        h5::group_imp g(root_group,"test");

        h5::group_imp det;
        BOOST_CHECK_EQUAL(root_group.size(),1);
        //det = h5::group_imp(root_group.at(0));
        BOOST_CHECK_NO_THROW(det = h5::group_imp(root_group.at(0)));
        BOOST_CHECK_EQUAL(det.name(),"test");

        BOOST_CHECK_THROW(root_group.at(10),index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_parent)
    {
        h5::group_imp g1(root_group,"group1");
        h5::group_imp parent;

        BOOST_CHECK_NO_THROW(parent = h5::group_imp(g1.parent()));
        BOOST_CHECK_EQUAL(parent.name(), "/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_scalar_attribute)
    {
        using pni::io::object_error;
        h5::group_imp g(root_group,"test");

        h5::attribute_imp a = g.attr("hello",type_id_t::FLOAT32);
        BOOST_CHECK(g.has_attr("hello"));
        BOOST_CHECK_EQUAL(g.nattr(),1);

        BOOST_CHECK_THROW(g.attr("hello",type_id_t::FLOAT32),object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_mdim_attribute)
    {
        using pni::io::object_error;
        h5::group_imp g(root_group,"test");

        h5::attribute_imp a = g.attr("hello",type_id_t::STRING,
                                 h5::type_imp::index_vector_type{2,40});
        BOOST_CHECK(g.has_attr("hello"));
        BOOST_CHECK_EQUAL(g.nattr(),1);

        BOOST_CHECK_THROW(g.attr("hello",type_id_t::FLOAT32,
                          h5::type_imp::index_vector_type{3,40}),
                          object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_attribute_by_name)
    {
        h5::group_imp g(root_group,"test");

        g.attr("hello world",type_id_t::STRING);
        h5::attribute_imp a = g.attr("hello world");
        BOOST_CHECK_EQUAL(a.name(),"hello world");
        BOOST_CHECK_EQUAL(a.type_id(),type_id_t::STRING);
        BOOST_CHECK_EQUAL(a.rank(),1);
        BOOST_CHECK_EQUAL(a.size(),1);

        BOOST_CHECK_THROW(g.attr("bla"),key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_attribute_by_index)
    {
        h5::group_imp g(root_group,"test");

        g.attr("hello world",type_id_t::STRING);
        h5::attribute_imp a = g.attr(0);
        BOOST_CHECK_EQUAL(a.name(),"hello world");
        BOOST_CHECK_EQUAL(a.type_id(),type_id_t::STRING);
        BOOST_CHECK_EQUAL(a.rank(),1);
        BOOST_CHECK_EQUAL(a.size(),1);

        BOOST_CHECK_THROW(g.attr(10),index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delete_attribute)
    {
        h5::group_imp g(root_group,"test");

        g.attr("bla",type_id_t::STRING);
        BOOST_CHECK(g.has_attr("bla"));

        g.del_attr("bla");
        BOOST_CHECK(!g.has_attr("bla"));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_remove)
    {
        using pni::io::invalid_object_error;

        h5::group_imp g(root_group,"test");
        BOOST_CHECK(root_group.has_child("test"));
        root_group.remove("test");
        BOOST_CHECK(!root_group.has_child("test"));

        BOOST_CHECK_THROW(root_group.remove("bla"),key_error);
        BOOST_CHECK_THROW(h5::group_imp().remove("bla"),invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()
