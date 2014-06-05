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
// Created on: Jan 13, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <pni/core/arrays.hpp>
#include "H5GroupTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5GroupTest);


//-----------------------------------------------------------------------------
void H5GroupTest::setUp()
{
    file = H5File::create_file("H5GroupTest.h5",true,0);
}

//-----------------------------------------------------------------------------
void H5GroupTest::tearDown()
{
    file.close();
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    H5Group g; //default constructor

    CPPUNIT_ASSERT(!g.is_valid());

    //create directly using the constructor
    H5Group g1("group1",file);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g1.filename() == "H5GroupTest.h5");
    CPPUNIT_ASSERT(g1.name()=="group1");
    CPPUNIT_ASSERT(g1.path()=="/group1");
    CPPUNIT_ASSERT(g1.base()=="/");

    //create a group from another group
    H5Group g2("group12",g1);
    CPPUNIT_ASSERT(g2.is_valid());

    //using the copy constructor
    H5Group g3 = g2;
    CPPUNIT_ASSERT(g3.is_valid());
    CPPUNIT_ASSERT(g2.is_valid());

    //using the move constructor
    H5Group g4 = std::move(g2);
    CPPUNIT_ASSERT(g4.is_valid());
    CPPUNIT_ASSERT(!g2.is_valid());
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group g("group1",file);
    H5Group g1,g2;
    
    //test copy assignment
    CPPUNIT_ASSERT_NO_THROW(g1 = g);
    CPPUNIT_ASSERT(g1.is_valid());
    CPPUNIT_ASSERT(g.is_valid());

    //test move assignment
    CPPUNIT_ASSERT_NO_THROW(g2 = std::move(g));
    CPPUNIT_ASSERT(g2.is_valid());
    CPPUNIT_ASSERT(!g.is_valid());

    g.close();
    g1.close();
    g2.close();
}


//------------------------------------------------------------------------------
void H5GroupTest::test_openobjects()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    H5Group g("test",file);

    H5Group det;

    CPPUNIT_ASSERT_NO_THROW(det = file.open("test"));
    CPPUNIT_ASSERT(det.is_valid());
    CPPUNIT_ASSERT(det.name() == "test");

    H5Group p;
    CPPUNIT_ASSERT_NO_THROW(p = det.parent());
    CPPUNIT_ASSERT(p.name() == "/");

    H5Group test;
    CPPUNIT_ASSERT_NO_THROW(test = file["test"]);
    CPPUNIT_ASSERT(test.is_valid());
}


//-----------------------------------------------------------------------------
void H5GroupTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group("group1",file);
    H5Group("group2",file);

    H5Group g1 = file["group1"];
    H5Group g2 = file["group1"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = file["group2"];
    CPPUNIT_ASSERT(g2 != g1);
}

//-----------------------------------------------------------------------------
void H5GroupTest::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Group g1("group1",file);
    CPPUNIT_ASSERT(H5Group(g1.parent()).name() == "/");
}
