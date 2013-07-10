/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * NXGroupTest.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#include <boost/current_function.hpp>
#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION(NXGroupTest);

//------------------------------------------------------------------------------
void NXGroupTest::setUp()
{
	_fname = "test.group.h5";
    _f = nxfile::create_file("NXGroupTest.h5",true,0);
    CPPUNIT_ASSERT(_f.object_type() == pni::io::nx::nxobject_type::NXGROUP);
}

//------------------------------------------------------------------------------
void NXGroupTest::tearDown()
{
	_f.close();
}

//------------------------------------------------------------------------------
void NXGroupTest::test_linking()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxgroup g = _f.create_group("/scan_1/detector/data");
    CPPUNIT_ASSERT_NO_THROW(g.link("/collection/detector/data"));
    CPPUNIT_ASSERT(_f.exists("/collection/detector/data"));

    nxgroup ref = g.open("/scan_1");
    CPPUNIT_ASSERT_NO_THROW(g.link(ref,"a_link"));
    CPPUNIT_ASSERT(_f.exists("/scan_1/a_link"));

    nxfile file = nxfile::create_file("NXGroupTest2.h5",true,0);
    file.create_group("/test/data");
    CPPUNIT_ASSERT_NO_THROW(g.link("NXGroupTest2.h5:/test/data","/external/data"));
    CPPUNIT_ASSERT(_f.exists("/external/data"));
}

//------------------------------------------------------------------------------
void NXGroupTest::test_creation()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g;
    CPPUNIT_ASSERT(!g.is_valid());

	g = _f.create_group("/hello/world");
    CPPUNIT_ASSERT(g.is_valid());
	g.close();
    CPPUNIT_ASSERT(!g.is_valid());
	g = _f.create_group("/directory_1");
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.path() == "/directory_1");
    CPPUNIT_ASSERT(g.name() == "directory_1");
    CPPUNIT_ASSERT(g.base() == "/");


	//test copy constructor
	nxgroup g1(g);
	CPPUNIT_ASSERT(g1.is_valid());
	CPPUNIT_ASSERT(g.is_valid());
	CPPUNIT_ASSERT(g1.name() == g.name());

	//test move constructor
	nxgroup g2 = std::move(g1);
	CPPUNIT_ASSERT(!g1.is_valid());
	CPPUNIT_ASSERT(g2.is_valid());
}

//------------------------------------------------------------------------------
void NXGroupTest::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxgroup g = _f.create_group("detector/modules");
    nxgroup p = g.parent();
    CPPUNIT_ASSERT(p.name() == "detector");
    CPPUNIT_ASSERT(p.parent().name() == "/");
}

//------------------------------------------------------------------------------
void NXGroupTest::test_open()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g1,g2;

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.create_group("/directory1/data"));

	CPPUNIT_ASSERT_NO_THROW(g2 = _f.open("/directory1"));
	nxgroup g = g2.open("data");
	nxgroup g3;
	g3 = g2.open("data");

	nxgroup g4 = _f.open("/directory1/data");

	CPPUNIT_ASSERT_THROW(_f.open("directory2"),pni::io::nx::nxgroup_error);
	CPPUNIT_ASSERT_NO_THROW(_f.open("directory1/data"));

	g1.close();
	g2.close();

}

//------------------------------------------------------------------------------
void NXGroupTest::test_internal_links()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
}

//------------------------------------------------------------------------------
void NXGroupTest::test_existance()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g1,g2;
	nxfield f;

	g1 = _f.create_group("/scan_1/instrument");
	g1 = _f.create_group("/scan_2/instrument/detector");

	g1 = _f.open("scan_1");
	CPPUNIT_ASSERT(g1.exists("instrument"));
	CPPUNIT_ASSERT(g1.exists("/scan_2"));
	CPPUNIT_ASSERT(!g1.exists("/instrument"));
	g2 = _f.open("scan_2");
	CPPUNIT_ASSERT(g2.exists("instrument/detector/"));
	CPPUNIT_ASSERT(!g2.exists("/instrument/detector/data"));

	CPPUNIT_ASSERT(_f.exists("scan_1"));
	CPPUNIT_ASSERT(_f.exists("/scan_1/instrument"));
	CPPUNIT_ASSERT(_f.exists("scan_2/instrument/detector"));
}

//------------------------------------------------------------------------------
void NXGroupTest::test_remove()
{
	nxgroup g1;
	nxfield f;
}

//------------------------------------------------------------------------------
void NXGroupTest::test_assignment()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g1,g2;

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.create_group("test1"));
	CPPUNIT_ASSERT_NO_THROW(g2 = g1);
	CPPUNIT_ASSERT(g1.is_valid());
	CPPUNIT_ASSERT(g2.is_valid());

	nxgroup g3;
	CPPUNIT_ASSERT_NO_THROW(g3 = std::move(g2));
	CPPUNIT_ASSERT(g3.is_valid());
	CPPUNIT_ASSERT(!g2.is_valid());
}

//------------------------------------------------------------------------------
void NXGroupTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxgroup g1 = _f.create_group("hello/world");
    nxgroup g2 = _f["/hello/world"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = _f["/hello"];
    CPPUNIT_ASSERT(g1 != g2);

    g1.link("/link");
    g2 = _f["/link"];
    CPPUNIT_ASSERT(g1 == g2);

}

//-----------------------------------------------------------------------------
void NXGroupTest::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxgroup g = _f.create_group("data");
    g.create_group("dir1");
    g.create_group("dir2");
    g.create_group("dir3");

#ifdef NOFOREACH
    for(auto iter = g.begin(); iter!=g.end(); iter++){
        auto &sg = *iter;
#else
    for(auto &sg: g){
#endif
        std::cout<<sg.path()<<std::endl;
    }
}

