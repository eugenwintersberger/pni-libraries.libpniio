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
// Created on: Sep 13, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "H5AttributeTest.hpp"
#include <pni/io/nx/nxdate_time.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(H5AttributeTest);

//-----------------------------------------------------------------------------
void H5AttributeTest::setUp()
{
    file = H5File::create_file("H5AttributeTest.h5",true,0);
    group = H5Group("group",file);
}

//-----------------------------------------------------------------------------
void H5AttributeTest::tearDown()
{
    group.close();
    file.close();
}

//-----------------------------------------------------------------------------
void H5AttributeTest::test_creation()
{
    using pni::io::nx::nxdate_time;
    PRINT_TEST_FUNCTION_SIG;

    //default constructor
    H5Attribute a;
    CPPUNIT_ASSERT(!a.is_valid());
  
    //test constructor from new object
    H5Attribute a1 = group.attr<string>("a1");
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");

    
    //test construction from copy constructor
    H5Attribute a2(a1);
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == a1.name());
    
    //test move construction
    H5Attribute a3(std::move(a2));
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(!a2.is_valid());

}

//-----------------------------------------------------------------------------
void H5AttributeTest::test_assignment()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a1 = group.attr<string>("a1");
    CPPUNIT_ASSERT(a1.is_valid());

    H5Attribute a2;
    a2 = a1;
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a2.is_valid());

    H5Attribute a3;
    a3= std::move(a2);
    CPPUNIT_ASSERT(!a2.is_valid());
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a3.is_valid());
}



//-----------------------------------------------------------------------------
void H5AttributeTest::test_inquery()
{
    PRINT_TEST_FUNCTION_SIG;

    H5Attribute a1 = group.attr<float32>("a1");
    shape_t shape{10,2};
    H5Attribute a2 = group.attr<float32>("a2",shape);

    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");
    std::cout<<a1.filename()<<std::endl;
    CPPUNIT_ASSERT(a1.filename() == string("H5AttributeTest.h5"));
    CPPUNIT_ASSERT(a1.size() == 1);
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.type_id() == type_id_t::FLOAT32);
    CPPUNIT_ASSERT(a1.shape<shape_t>().size() == 0);


    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == "a2");
    CPPUNIT_ASSERT(a2.filename() == "H5AttributeTest.h5");
    CPPUNIT_ASSERT(a2.size() == 20);
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.type_id() == type_id_t::FLOAT32);
    auto ashape = a2.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),ashape.begin()));

    H5Group parent = a1.parent();
    CPPUNIT_ASSERT(parent.is_valid());
    CPPUNIT_ASSERT(parent.name() == "group");
}


