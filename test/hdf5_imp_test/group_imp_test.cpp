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
#include <vector>
#include <pni/core/arrays.hpp>
#include <pni/io/exceptions.hpp>
#include "group_imp_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(group_imp_test);

using pni::io::object_error;
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
void group_imp_test::setUp()
{
    file = file_imp::create("group_imp_test.h5",true,0);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void group_imp_test::tearDown()
{
    file.close();
    root_group.close();
}

//-----------------------------------------------------------------------------
void group_imp_test::test_creation()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    group_imp g; //default constructor
    CPPUNIT_ASSERT(!g.is_valid());

    //create directly using the constructor
    group_imp g1(root_group,"group1");
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g1.name()=="group1");
    CPPUNIT_ASSERT(g1.filename() == "group_imp_test.h5");

    //using the copy constructor
    group_imp g2 = g1;
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());

    //using the move constructor
    group_imp g3 = std::move(g2);
    CPPUNIT_ASSERT(g3.is_valid());
    CPPUNIT_ASSERT(!g2.is_valid());
}

//-----------------------------------------------------------------------------
void group_imp_test::test_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    group_imp g(root_group,"group1");
    group_imp g1,g2;
    
    //test copy assignment
    CPPUNIT_ASSERT_NO_THROW(g1 = g);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g.is_valid());

    //test move assignment
    CPPUNIT_ASSERT_NO_THROW(g2 = std::move(g));
    CPPUNIT_ASSERT(g2.is_valid());
    CPPUNIT_ASSERT(!g.is_valid());
}

//------------------------------------------------------------------------------
void group_imp_test::test_open_by_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    group_imp g(root_group,"test");

    group_imp det;

    CPPUNIT_ASSERT_NO_THROW(det = group_imp(root_group.at("test")));
    CPPUNIT_ASSERT(det.is_valid());
    CPPUNIT_ASSERT(det.name() == "test");

    CPPUNIT_ASSERT_THROW(root_group.at("bla"),key_error);
}

//----------------------------------------------------------------------------
void group_imp_test::test_open_by_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");

    group_imp det;
    CPPUNIT_ASSERT(root_group.size()==1);
    det = group_imp(root_group.at(0));
    CPPUNIT_ASSERT_NO_THROW(det = group_imp(root_group.at(0)));
    CPPUNIT_ASSERT(det.name() == "test");

    CPPUNIT_ASSERT_THROW(root_group.at(10),index_error);
}

//-----------------------------------------------------------------------------
void group_imp_test::test_parent()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    group_imp g1(root_group,"group1");
    group_imp parent;

    CPPUNIT_ASSERT_NO_THROW(parent = group_imp(g1.parent()));
    CPPUNIT_ASSERT(parent.name() == "/");
}

//----------------------------------------------------------------------------
void group_imp_test::test_create_scalar_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");

    attribute_imp a = g.attr("hello",type_id_t::FLOAT32);
    CPPUNIT_ASSERT(g.has_attr("hello"));
    CPPUNIT_ASSERT(g.nattr() == 1);

    CPPUNIT_ASSERT_THROW(g.attr("hello",type_id_t::FLOAT32),object_error);
}

//----------------------------------------------------------------------------
void group_imp_test::test_create_mdim_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    group_imp g(root_group,"test");

    attribute_imp a = g.attr("hello",type_id_t::STRING,
                             type_imp::index_vector_type{2,40});
    CPPUNIT_ASSERT(g.has_attr("hello"));
    CPPUNIT_ASSERT(g.nattr() == 1);

    CPPUNIT_ASSERT_THROW(g.attr("hello",type_id_t::FLOAT32,
                                type_imp::index_vector_type{3,40}),
                         object_error);
}

//----------------------------------------------------------------------------
void group_imp_test::test_get_attribute_by_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");

    g.attr("hello world",type_id_t::STRING);
    attribute_imp a = g.attr("hello world");
    CPPUNIT_ASSERT(a.name() == "hello world");
    CPPUNIT_ASSERT(a.type_id() == type_id_t::STRING);
    CPPUNIT_ASSERT(a.rank() == 1);
    CPPUNIT_ASSERT(a.size() == 1);

    CPPUNIT_ASSERT_THROW(g.attr("bla"),key_error);
}

//----------------------------------------------------------------------------
void group_imp_test::test_get_attribute_by_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");

    g.attr("hello world",type_id_t::STRING);
    attribute_imp a = g.attr(0);
    CPPUNIT_ASSERT(a.name() == "hello world");
    CPPUNIT_ASSERT(a.type_id() == type_id_t::STRING);
    CPPUNIT_ASSERT(a.rank() == 1);
    CPPUNIT_ASSERT(a.size() == 1);

    CPPUNIT_ASSERT_THROW(g.attr(10),index_error);
}

//----------------------------------------------------------------------------
void group_imp_test::test_delete_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");

    g.attr("bla",type_id_t::STRING);
    CPPUNIT_ASSERT(g.has_attr("bla"));

    g.del_attr("bla");
    CPPUNIT_ASSERT(!g.has_attr("bla"));
}

//----------------------------------------------------------------------------
void group_imp_test::test_remove()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    group_imp g(root_group,"test");
    CPPUNIT_ASSERT(root_group.has_child("test"));
    root_group.remove("test");
    CPPUNIT_ASSERT(!root_group.has_child("test"));

    CPPUNIT_ASSERT_THROW(root_group.remove("bla"),key_error);
    CPPUNIT_ASSERT_THROW(group_imp().remove("bla"),invalid_object_error);
}
