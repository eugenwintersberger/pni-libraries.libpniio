//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/nxlink_type.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>


#include <pni/io/nx/h5/h5link.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>

using namespace pni::core;
using namespace pni::io::nx;

struct h5link_test_fixture
{
    h5::file_imp file1;
    h5::file_imp file2;

    h5link_test_fixture():
        file1(h5::file_imp::create("h5link_test1.h5",true,0)),
        file2(h5::file_imp::create("h5link_test2.h5",true,0))
    {}

    ~h5link_test_fixture()
    {
        file1.close();
        file2.close();
    }
};

BOOST_FIXTURE_TEST_SUITE(h5link_test,h5link_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_internal)
    {
        h5::group_imp root_group(file1.root());
        h5::group_imp g(root_group,"test");
        //the original group should be a hard link
        BOOST_CHECK(h5::h5link::link_type(root_group,"test") == nxlink_type::HARD);

        //straight forward - the link name is just a single name
        nxpath target = nxpath::from_string("/test");
        BOOST_CHECK_NO_THROW(h5::h5link::create_internal_link(target,root_group,"link_1"));
        BOOST_CHECK(root_group.has_child("link_1"));
        h5::group_imp lg(root_group.at("link_1"));
        //this should be now a soft link
        BOOST_CHECK(h5::h5link::link_type(root_group,"link_1")==nxlink_type::SOFT);

        //check for exceptions
        target = nxpath::from_string("test.nx://test/data");
        BOOST_CHECK_THROW(h5::h5link::create_internal_link(target,root_group,"link_2"),
                          value_error);

        target = nxpath::from_string("/:NXentry/data");
        BOOST_CHECK_THROW(h5::h5link::create_internal_link(target,root_group,"link_3"),
                          value_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_external)
    {
        h5::group_imp root_group(file1.root());
        h5::group_imp g(root_group,"test");
        BOOST_CHECK(h5::h5link::link_type(root_group,"test") == nxlink_type::HARD);

        root_group = h5::group_imp(file2.root());
        nxpath target = nxpath::from_string("h5link_test1.h5://test");
        //create a link to the group data in the first file
        BOOST_CHECK_NO_THROW(h5::h5link::create_external_link(target,root_group,"external"));
        BOOST_CHECK(h5::h5link::link_type(root_group,"external") 
                == nxlink_type::EXTERNAL);
        BOOST_CHECK(root_group.has_child("external"));

        //echeck exceptions
        target = nxpath::from_string("/test/data");
        BOOST_CHECK_THROW(h5::h5link::create_external_link(target,root_group,"ext2"),
                          value_error);


        target = nxpath::from_string("h5link_test1.h5://:NXentry/data");
        BOOST_CHECK_THROW(h5::h5link::create_external_link(target,root_group,"external"),
                          value_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_link_type)
    {
        h5::group_imp root_group = file1.root();
        
        //exception if child does not exist
        BOOST_CHECK_THROW(h5::h5link::link_type(root_group,"test"),key_error);
        
    }

BOOST_AUTO_TEST_SUITE_END()
