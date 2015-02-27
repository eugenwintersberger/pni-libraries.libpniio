//
// Declaration of Nexus object template.
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
//
//  Created on: Aug 4, 2011
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

using pni::io::invalid_object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(NXGroupTest);

//------------------------------------------------------------------------------
void NXGroupTest::setUp()
{
	_fname = "test.group.h5";
    _f = nxfile::create_file("NXGroupTest.h5",true);
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

    nxgroup g = _f.root().create_group("scan_1").create_group("detector")
                         .create_group("data");
    _f.root().create_group("collection").create_group("detector");
    CPPUNIT_ASSERT_NO_THROW(pni::io::nx::link(g,_f.root(),"/collection/detector/data"));
    nxgroup o;
    CPPUNIT_ASSERT_NO_THROW(o=get_object(_f.root(),nxpath::from_string("/collection/detector/data")));
    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(o.name() == "data");

    nxgroup ref = _f.root().at("scan_1");
    CPPUNIT_ASSERT_NO_THROW(pni::io::nx::link(g,ref,"a_link"));
    CPPUNIT_ASSERT_NO_THROW(get_object(_f.root(),nxpath::from_string("/scan_1/a_link")));

    //create some group in an external file
    nxfile file = nxfile::create_file("NXGroupTest2.h5",true);
    file.root().create_group("test").create_group("data");

    //linke the external group
    g = _f.root().create_group("external");
    //pni::io::nx::link("NXGroupTest2.h5://test/data",g,"data");
    CPPUNIT_ASSERT_NO_THROW(pni::io::nx::link("NXGroupTest2.h5://test/data",g,"data"));
    CPPUNIT_ASSERT_NO_THROW(get_object(_f.root(),nxpath::from_string("/external/data")));
}

//------------------------------------------------------------------------------
void NXGroupTest::test_creation()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g;
    CPPUNIT_ASSERT(!g.is_valid());
    CPPUNIT_ASSERT_THROW(g.at("hello"),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g["hello"],invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.size(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.parent(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.at(0),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g[0],invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.filename(),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.has_child("hello"),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.remove("hello"),invalid_object_error);
    CPPUNIT_ASSERT_THROW(g.name(),invalid_object_error);

	g = _f.root().create_group("hello").create_group("world");
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.filename() == "NXGroupTest.h5");
	g.close();
    CPPUNIT_ASSERT(!g.is_valid());
	g = _f.root().create_group("directory_1");
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.name() == "directory_1");


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

    nxgroup g = _f.root().create_group("detector").create_group("modules");
    nxgroup p = g.parent();
    CPPUNIT_ASSERT(p.name() == "detector");
    CPPUNIT_ASSERT(nxgroup(p.parent()).name() == "/");
}

//------------------------------------------------------------------------------
void NXGroupTest::test_open()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g1,g2;

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.root().create_group("directory1")
                                          .create_group("data"));

	CPPUNIT_ASSERT_NO_THROW(g2 = _f.root().at("directory1"));
	nxgroup g = g2.at("data");
	nxgroup g3;
	g3 = g2.at("data");


	CPPUNIT_ASSERT_THROW(_f.root().at("directory2"),key_error);
}


//------------------------------------------------------------------------------
void NXGroupTest::test_existance()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	nxgroup g1,g2;
	nxfield f;

	g1 = _f.root().create_group("scan_1").create_group("instrument");
	g1 = _f.root().create_group("scan_2").create_group("instrument").
                  create_group("detector");

	g1 = _f.root().at("scan_1");
	CPPUNIT_ASSERT(g1.has_child("instrument"));
	CPPUNIT_ASSERT(!g1.has_child("/scan_2"));
	CPPUNIT_ASSERT(!g1.has_child("/instrument"));
	g2 = _f.root().at("scan_2");
	CPPUNIT_ASSERT(nxgroup(g2["instrument"]).has_child("detector"));
	CPPUNIT_ASSERT(!g2.has_child("/instrument/detector/data"));

	CPPUNIT_ASSERT(_f.root().has_child("scan_1"));
	CPPUNIT_ASSERT(_f.root().has_child("scan_2"));
	CPPUNIT_ASSERT(!_f.root().has_child("scan_2/instrument/detector"));
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

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.root().create_group("test1"));
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

    nxgroup g1 = _f.root().create_group("hello").create_group("world");
    nxgroup g2 = _f.root()["hello"];
    g2 = g2["world"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = _f.root()["hello"];
    CPPUNIT_ASSERT(g1 != g2);

}

//-----------------------------------------------------------------------------
void NXGroupTest::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxgroup g = _f.root().create_group("data");
    g.create_group("dir1");
    g.create_group("dir2");
    g.create_group("dir3");

    for(nxgroup sg: g)
        std::cout<<get_path(sg)<<std::endl;
}

