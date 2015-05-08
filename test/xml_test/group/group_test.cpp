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
//  Created on: Nov 26, 2014
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/is_valid.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/get_class.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "group_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(group_test);

void group_test::setUp()
{
    file = h5::nxfile::create_file("xml_gruop_test.nxs",true);
    root_group = file.root();
}

//----------------------------------------------------------------------------
void group_test::tearDown()
{
    close(root_group);
    file.close();
}

//----------------------------------------------------------------------------
void group_test::set_xml(const string &fname)
{
    root = xml::create_from_file(fname);
    child = root.get_child("group");
}

//----------------------------------------------------------------------------
void group_test::test_read_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_xml("group1.xml");

    h5::nxobject g = xml::group::object_from_xml(root_group,child);
    CPPUNIT_ASSERT(is_valid(g));
    CPPUNIT_ASSERT(get_name(g) == "hello");
    CPPUNIT_ASSERT(get_class(g) == "NXentry");
    
}

//----------------------------------------------------------------------------
void group_test::test_read_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_xml("group2.xml");

    h5::nxobject g = xml::group::object_from_xml(root_group,child);
    CPPUNIT_ASSERT(is_valid(g));
    CPPUNIT_ASSERT(get_name(g)=="hello");
}

//----------------------------------------------------------------------------
void group_test::test_read_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    set_xml("group3.xml");

    h5::nxobject g;
    CPPUNIT_ASSERT_THROW(g = xml::group::object_from_xml(root_group,child),
                         pni::core::value_error);
}

//----------------------------------------------------------------------------
void group_test::test_write_1()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxobject g = create_group(root_group,"hello");

    xml::node root;
    xml::node gnode = xml::group::object_to_xml(g);
    root.add_child("group",gnode);
    write_xml("test.xml",root);

    xml::node readback = xml::create_from_file("test.xml");
    CPPUNIT_ASSERT(readback == root);
}
