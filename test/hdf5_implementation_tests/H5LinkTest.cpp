/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Feb 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/nxpath_utils.hpp>
#include <pni/io/nx/nxlink_type.hpp>
#include <boost/current_function.hpp>
#include "H5LinkTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5LinkTest);

//-----------------------------------------------------------------------------
void H5LinkTest::setUp(){
    _file1 = H5File::create_file("H5LinkTest1.h5",true,0);
    _file2 = H5File::create_file("H5LinkTest2.h5",true,0);
}

//------------------------------------------------------------------------------
void H5LinkTest::tearDown(){
    _file1.close();
    _file2.close();
}

void H5LinkTest::test_internal()
{
    using pni::io::nx::nxpath;
    using pni::io::nx::path_from_string;
    using pni::io::nx::nxlink_type;

    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group root_group(_file1.open("/"));
    H5Group g("/test/data",_file1);
    //the original group should be a hard link
    CPPUNIT_ASSERT(g.link_type() == nxlink_type::HARD);

    //straight forward - the link name is just a single name
    nxpath target = path_from_string(g.path());
    CPPUNIT_ASSERT_NO_THROW(h5link::create_internal_link(target,root_group,"link_1"));
    CPPUNIT_ASSERT(root_group.exists("link_1"));
    H5Group lg = root_group.open("link_1");
    //this should be now a soft link
    CPPUNIT_ASSERT(lg.link_type()==nxlink_type::SOFT);

    //check for exceptions
    target = path_from_string("test.nx:///test/data");
    CPPUNIT_ASSERT_THROW(h5link::create_internal_link(target,root_group,"link_2"),
                         pni::io::nx::nxlink_error);

    target = path_from_string("/:NXentry/data");
    CPPUNIT_ASSERT_THROW(h5link::create_internal_link(target,root_group,"link_3"),
                         pni::core::value_error);
}

//------------------------------------------------------------------------------
void H5LinkTest::test_external()
{
    using pni::io::nx::nxpath;
    using pni::io::nx::path_from_string;
    using pni::io::nx::nxlink_type;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group g("/test/data",_file1);
    CPPUNIT_ASSERT(g.link_type() == nxlink_type::HARD);

    H5Group root_group(_file2.open("/"));
    //create a link to the group data in the first file
    nxpath target = path_from_string("H5LinkTest1.h5:///test/data");
    CPPUNIT_ASSERT_NO_THROW(h5link::create_external_link(target,root_group,"external"));
    H5Group gext = root_group["external"];
    CPPUNIT_ASSERT(gext.link_type() == nxlink_type::EXTERNAL);
    CPPUNIT_ASSERT(root_group.exists("external"));

    //echeck exceptions
    target = path_from_string("/test/data");
    CPPUNIT_ASSERT_THROW(h5link::create_external_link(target,root_group,"ext2"),
            pni::io::nx::nxlink_error);


    target = path_from_string("H5LinkTest1.h5:///:NXentry/data");
    CPPUNIT_ASSERT_THROW(h5link::create_external_link(target,root_group,"external"),
            pni::core::value_error);
}


