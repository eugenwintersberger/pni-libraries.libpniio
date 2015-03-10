//
// Declaration of Nexus object template.
//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

//testing class for ArrayShape objects

#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class nxattribute_access_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxattribute_access_test);
	CPPUNIT_TEST(test_by_index<h5::nxgroup>);
	CPPUNIT_TEST(test_by_index<h5::nxfield>);
	CPPUNIT_TEST(test_by_name<h5::nxgroup>);
	CPPUNIT_TEST(test_by_name<h5::nxfield>);
    CPPUNIT_TEST(test_by_begin_end<h5::nxgroup>);
    CPPUNIT_TEST(test_by_begin_end<h5::nxfield>);
    CPPUNIT_TEST(test_by_foreach<h5::nxgroup>);
    CPPUNIT_TEST(test_by_foreach<h5::nxfield>);
	CPPUNIT_TEST_SUITE_END();
    h5::nxfile f;
    h5::nxgroup group;
    h5::nxfield field;
    static const string filename;
    static const shape_t shape;
    static const size_t size = 12;
    static const std::vector<string> attr_names;

    template<typename ST> 
    static bool check_shape(const ST &a,const ST &b)
    {
        return std::equal(a.begin(),a.end(),b.begin()); 
    }

    void get_parent(h5::nxgroup &g) { g = group; }

    void get_parent(h5::nxfield &f) { f = field; }
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    template<typename P> void test_by_index();
    template<typename P> void test_by_name();
    template<typename P> void test_by_begin_end();
    template<typename P> void test_by_foreach();

};

const string nxattribute_access_test::filename="nxattribute_access_test.nxs";
const shape_t nxattribute_access_test::shape = shape_t{3,4};
const std::vector<string> nxattribute_access_test::attr_names{"attr1","temperature","matrix"};

//----------------------------------------------------------------------------
template<typename P>
void nxattribute_access_test::test_by_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    P parent; 
    get_parent(parent);
    
    CPPUNIT_ASSERT(parent.attributes.size()==3);
    CPPUNIT_ASSERT(parent.attributes[0].name() == "attr1");
    CPPUNIT_ASSERT(parent.attributes[1].name() == "temperature");
    CPPUNIT_ASSERT(parent.attributes[2].name() == "matrix");

    //try to create a new attribute of same name should throw
    CPPUNIT_ASSERT_THROW(parent.attributes[3],index_error);
}

//----------------------------------------------------------------------------
template<typename P>
void nxattribute_access_test::test_by_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    P parent; 
    get_parent(parent);
    CPPUNIT_ASSERT(parent.attributes["attr1"].size() == 1);
    CPPUNIT_ASSERT(parent.attributes["temperature"].size() ==1);
    CPPUNIT_ASSERT(parent.attributes["matrix"].size() == 12);

    CPPUNIT_ASSERT_THROW(parent.attributes["bla"],key_error);
}

//----------------------------------------------------------------------------
template<typename P>
void nxattribute_access_test::test_by_begin_end()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    P parent;
    get_parent(parent);

    auto start_iter = parent.attributes.begin();
    auto end_iter   = parent.attributes.end();

    CPPUNIT_ASSERT(std::distance(start_iter,end_iter)==3);
    
    auto name_iter = attr_names.begin();
    for(;start_iter != end_iter; ++start_iter,++name_iter)
        CPPUNIT_ASSERT((*start_iter).name() == *name_iter);
}

//----------------------------------------------------------------------------
template<typename P>
void nxattribute_access_test::test_by_foreach()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    P parent;
    get_parent(parent);
    
    auto name_iter = attr_names.begin();
    for(auto attr: parent.attributes)
        CPPUNIT_ASSERT(attr.name() == *name_iter++);

}

